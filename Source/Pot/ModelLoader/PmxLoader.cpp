#include "./Pot/ModelLoader/PmxLoader.h"
#include "./Pot/File/file.h"
#include "./Pot/Out/out.h"

#include "./Pot/ModelLoader/CharCode.h"

namespace cpot {


BOOL PmxLoader::Load(const CHAR* aFileName) {

	//�t�@�C�����J��
	FileIn lFile;
	lFile.Open(aFileName, true);

	//�J���̂Ɏ��s������
	if (!lFile.IsOpen()) {
		CPOT_LOG("�t�@�C���F", aFileName, "�̃I�[�v���Ɏ��s���܂���");
		return false;
	}


	//�t�@�C������ǂݍ���
	Buffer lBuffer;
	lFile.Read(lBuffer);

	//�t�@�C�����̐ݒ�
	mData.fileName = aFileName;


	//�ǂݍ��񂾃o�C�i�����烍�[�h����
	return Load(lBuffer);
}
BOOL PmxLoader::Load(Buffer& aData) {

	//�w�b�_�̓ǂݍ���
	aData.Read(&mData.header, sizeof(mData.header));

	//���f���f�[�^�̓ǂݍ���
	ReadTextBuf(aData, mData.modelData.name);
	ReadTextBuf(aData, mData.modelData.nameEng);
	ReadTextBuf(aData, mData.modelData.comment);
	ReadTextBuf(aData, mData.modelData.commentEng);


	//���_�f�[�^�̓ǂݍ���
	s32 lVertexNum;
	aData.Read(&lVertexNum, sizeof(s32));
	mData.vertexs.SetSize(lVertexNum);

	s32 addUvNum = AddUvNum();

	for (s32 i = 0; i < lVertexNum; i++) {
		//�ꏊ�A�@���AUV���W�̎擾
		aData.Read(&mData.vertexs[i], sizeof(f32) * 8);

		//�ǉ�UV�̎擾
		if (addUvNum > 0) {
			mData.vertexs[i].addUV.SetSize(4 * addUvNum);
			aData.Read(&mData.vertexs[i].addUV[0], sizeof(f32) * 4 * addUvNum);
		}
		else {
			mData.vertexs[i].addUV.Clear();
		}

		//�E�F�C�g�ό`�����̎擾
		aData.Read(&mData.vertexs[i].weightType, sizeof(u8));

		//�E�F�C�g�f�[�^�̎擾
		s32 tWeightType = mData.vertexs[i].weightType;

		if (tWeightType == 0) {
			s32 i1 = ReadChangeValue(aData, BoneIndexByteNum());
			mData.vertexs[i].weight.index[0] = i1;
			mData.vertexs[i].weight.index[1] = 0;
			mData.vertexs[i].weight.index[2] = 0;
			mData.vertexs[i].weight.index[3] = 0;
			mData.vertexs[i].weight.weight[0] = 1.0f;
			mData.vertexs[i].weight.weight[1] = 0.0f;
			mData.vertexs[i].weight.weight[2] = 0.0f;
		}
		else if (tWeightType == 1) {
			s32 i1 = ReadChangeValue(aData, BoneIndexByteNum());
			s32 i2 = ReadChangeValue(aData, BoneIndexByteNum());
			mData.vertexs[i].weight.index[0] = i1;
			mData.vertexs[i].weight.index[1] = i2;
			mData.vertexs[i].weight.index[2] = 0;
			mData.vertexs[i].weight.index[3] = 0;

			f32 w1;
			aData.Read(&w1, sizeof(f32));
			mData.vertexs[i].weight.weight[0] = w1;
			mData.vertexs[i].weight.weight[1] = 1.0f - w1;
			mData.vertexs[i].weight.weight[2] = 0.0f;
		}
		else if (tWeightType == 2) {
			s32 i1 = ReadChangeValue(aData, BoneIndexByteNum());
			s32 i2 = ReadChangeValue(aData, BoneIndexByteNum());
			s32 i3 = ReadChangeValue(aData, BoneIndexByteNum());
			s32 i4 = ReadChangeValue(aData, BoneIndexByteNum());
			mData.vertexs[i].weight.index[0] = i1;
			mData.vertexs[i].weight.index[1] = i2;
			mData.vertexs[i].weight.index[2] = i3;
			mData.vertexs[i].weight.index[3] = i4;

			f32 w1, w2, w3, w4;
			aData.Read(&w1, sizeof(f32));
			aData.Read(&w2, sizeof(f32));
			aData.Read(&w3, sizeof(f32));
			aData.Read(&w4, sizeof(f32));
			mData.vertexs[i].weight.weight[0] = w1;
			mData.vertexs[i].weight.weight[1] = w2;
			mData.vertexs[i].weight.weight[2] = w3;
		}
		else if (tWeightType == 3) {
			s32 i1 = ReadChangeValue(aData, BoneIndexByteNum());
			s32 i2 = ReadChangeValue(aData, BoneIndexByteNum());
			mData.vertexs[i].weight.index[0] = i1;
			mData.vertexs[i].weight.index[1] = i2;
			mData.vertexs[i].weight.index[2] = 0;
			mData.vertexs[i].weight.index[3] = 0;

			f32 w1;
			aData.Read(&w1, sizeof(f32));
			mData.vertexs[i].weight.weight[0] = w1;
			mData.vertexs[i].weight.weight[1] = 1.0f - w1;
			mData.vertexs[i].weight.weight[2] = 0.0f;

			float tB[100];
			aData.Read(&tB[0], 36);
		}

		//�G�b�W�{���̎擾
		aData.Read(&mData.vertexs[i].edgeTimes, sizeof(f32));
	}


	//�C���f�b�N�X�f�[�^�̎擾
	s32 lIndexNum;
	aData.Read(&lIndexNum, sizeof(s32));
	mData.indexs.SetSize(lIndexNum);

	s32 lIndexByteNum = VertexIndexByteNum();
	Vector<u8> lIndexBuffer;
	lIndexBuffer.SetSize(lIndexNum * lIndexByteNum);
	aData.Read(&lIndexBuffer[0], sizeof(u8) * lIndexNum * lIndexByteNum);

	switch (lIndexByteNum) {
		case 1:
			for (s32 i = 0; i < lIndexNum; i++) {
				mData.indexs[i] = ( (u8*)(&(lIndexBuffer[0])) )[i];
			}
			break;
		case 2:
			for (s32 i = 0; i < lIndexNum; i++) {
				mData.indexs[i] = ( (u16*)(&(lIndexBuffer[0])) )[i];
			}
			break;
		case 4:
			for (s32 i = 0; i < lIndexNum; i++) {
				mData.indexs[i] = ( (s32*)(&(lIndexBuffer[0])) )[i];
			}
			break;
		default:
			CPOT_ERROR("�C���f�b�N�X�o�C�g����1,2,4�ȊO�ł���");
			break;
	}

	//�e�N�X�`���p�X�̎擾
	s32 lTextureNum;
	aData.Read(&lTextureNum, sizeof(s32));
	mData.textures.SetSize(lTextureNum);

	for (s32 i = 0; i < lTextureNum; i++) {
		ReadTextBuf(aData, mData.textures[i].fileName);
	}


	//�}�e���A���̎擾
	s32 lMaterialNum;
	aData.Read(&lMaterialNum, sizeof(s32));
	mData.materials.SetSize(lMaterialNum);

	for (s32 i = 0; i < lMaterialNum; i++) {
		ReadTextBuf(aData, mData.materials[i].name);
		ReadTextBuf(aData, mData.materials[i].nameEng);

		aData.Read(&mData.materials[i].diffuse[0], sizeof(f32) * 4);
		aData.Read(&mData.materials[i].specular[0], sizeof(f32) * 3);
		aData.Read(&mData.materials[i].specularPow, sizeof(f32));
		aData.Read(&mData.materials[i].ambient[0], sizeof(f32) * 3);

		aData.Read(&mData.materials[i].drawFlag, sizeof(u8));
		aData.Read(&mData.materials[i].edgeColor[0], sizeof(f32) * 4);
		aData.Read(&mData.materials[i].edgeSize, sizeof(f32));

		mData.materials[i].textureRef = ReadChangeValue(aData, TextureIndexByteNum());
		mData.materials[i].sphereRef = ReadChangeValue(aData, TextureIndexByteNum());

		aData.Read(&mData.materials[i].sphereMode, sizeof(u8));
		aData.Read(&mData.materials[i].unionToonFlag, sizeof(u8));

		if (mData.materials[i].unionToonFlag == 0) {
			aData.Read(&mData.materials[i].toonTexture, TextureIndexByteNum());
		}
		else if (mData.materials[i].unionToonFlag == 1) {
			aData.Read(&mData.materials[i].toonTexture, sizeof(u8));
		}

		ReadTextBuf(aData, mData.materials[i].memo);
		aData.Read(&mData.materials[i].indexNum, sizeof(s32));
	}


	//�{�[���̓ǂݍ���
	s32 lBoneNum;
	aData.Read(&lBoneNum, sizeof(s32));
	mData.bones.SetSize(lBoneNum);

	for (s32 i = 0; i < lBoneNum; i++) {
		ReadTextBuf(aData, mData.bones[i].name);
		ReadTextBuf(aData, mData.bones[i].nameEng);

		aData.Read(&mData.bones[i].location[0], sizeof(f32) * 3);
		mData.bones[i].parentIndex = ReadChangeValue(aData, BoneIndexByteNum());
		aData.Read(&mData.bones[i].transe, sizeof(s32));
		aData.Read(&mData.bones[i].boneFlag, sizeof(u16));


		//�ǉ��f�[�^�̒����̌v�Z

		s32 addDataLen = 0;
		//���݂̃t�@�C���ʒu���擾
		s32 nowFileLoc = aData.GetPosition();
		
		if (mData.bones[i].boneFlag & 0x0001) {
			addDataLen += BoneIndexByteNum();
		}
		else {
			addDataLen += sizeof(f32) * 3;
		}

		if (mData.bones[i].boneFlag & 0x0100) {
			addDataLen += BoneIndexByteNum();
			addDataLen += sizeof(f32);
		}
		if (mData.bones[i].boneFlag & 0x0200) {
			addDataLen += BoneIndexByteNum();
			addDataLen += sizeof(f32);
		}

		if (mData.bones[i].boneFlag & 0x0400) {
			addDataLen += sizeof(f32) * 3;
		}

		if (mData.bones[i].boneFlag & 0x0800) {
			addDataLen += sizeof(f32) * 3;
			addDataLen += sizeof(f32) * 3;
		}

		if (mData.bones[i].boneFlag & 0x2000) {
			addDataLen += sizeof(s32);
		}

		if (mData.bones[i].boneFlag & 0x0020) {
			addDataLen += BoneIndexByteNum();
			addDataLen += sizeof(s32);
			addDataLen += sizeof(f32);

			//��֐i�߂�
			aData.SetPosition(aData.GetPosition() + addDataLen);

			s32 ikLinkNum;
			aData.Read(&ikLinkNum, sizeof(s32));
			addDataLen += sizeof(s32);

			for (s32 j = 0; j < ikLinkNum; j++) {
				aData.SetPosition(aData.GetPosition() + BoneIndexByteNum());
				addDataLen += BoneIndexByteNum();

				u8 limitAngle;
				aData.Read(&limitAngle, sizeof(u8));
				addDataLen += sizeof(u8);

				if (limitAngle == 1) {
					addDataLen += sizeof(f32) * 3;
					addDataLen += sizeof(f32) * 3;
				}
			}
		}

		//�t�@�C���̏ꏊ��߂�
		aData.SetPosition(nowFileLoc);

		mData.bones[i].addData.SetSize(addDataLen);
		aData.Read(&mData.bones[i].addData[0], addDataLen);
	}


	//���[�t�̓ǂݍ���
	s32 lMorphNum;
	aData.Read(&lMorphNum, sizeof(s32));
	mData.morphs.SetSize(lMorphNum);

	for (s32 i = 0; i < lMorphNum; i++) {
		ReadTextBuf(aData, mData.morphs[i].name);
		ReadTextBuf(aData, mData.morphs[i].nameEng);

		aData.Read(&mData.morphs[i].panel, sizeof(u8));
		aData.Read(&mData.morphs[i].morphType, sizeof(u8));

		aData.Read(&mData.morphs[i].offsetNum, sizeof(s32));

		s32 lMorphByteNum = MorphTypeByteNum(mData.morphs[i].morphType) * mData.morphs[i].offsetNum;
		mData.morphs[i].offsetData.SetSize(lMorphByteNum);
		aData.Read(&(mData.morphs[i].offsetData[0]), lMorphByteNum);
	}


	//�\���g�̓ǂݍ���
	s32 lShowFrameNum;
	aData.Read(&lShowFrameNum, sizeof(s32));
	mData.showFrames.SetSize(lShowFrameNum);

	for (s32 i = 0; i < lShowFrameNum; i++) {
		ReadTextBuf(aData, mData.showFrames[i].name);
		ReadTextBuf(aData, mData.showFrames[i].nameEng);

		aData.Read(&mData.showFrames[i].flag, sizeof(u8));

		s32 lElementNum;
		aData.Read(&lElementNum, sizeof(s32));
		mData.showFrames[i].elements.SetSize(lElementNum);

		for (s32 j = 0; j < lElementNum; j++) {
			aData.Read(&mData.showFrames[i].elements[j].type, sizeof(u8));

			if (mData.showFrames[i].elements[j].type == 0) {
				mData.showFrames[i].elements[j].data = ReadChangeValue(aData, BoneIndexByteNum());
			}
			else if (mData.showFrames[i].elements[j].type == 1) {
				mData.showFrames[i].elements[j].data = ReadChangeValue(aData, MorphIndexByteNum());
			}
			else {
				CPOT_ERROR("�\���g��ElementType���s���ł�");
			}
		}
	}


	//���̂̓ǂݍ���
	s32 lPhysicsNum;
	aData.Read(&lPhysicsNum, sizeof(s32));
	mData.physicses.SetSize(lPhysicsNum);

	for (s32 i = 0; i < lPhysicsNum; i++) {
		ReadTextBuf(aData, mData.physicses[i].name);
		ReadTextBuf(aData, mData.physicses[i].nameEng);

		mData.physicses[i].boneIndex = ReadChangeValue(aData, BoneIndexByteNum());

		aData.Read(&mData.physicses[i].group, sizeof(u8) + sizeof(u16) + sizeof(u8) + sizeof(f32) * 3 +
			sizeof(f32) * 3 + sizeof(f32) * 3 + sizeof(f32) * 5 + sizeof(u8));
	}

	//�W���C���g�̓ǂݍ���
	s32 lJointNum;
	aData.Read(&lJointNum, sizeof(s32));
	mData.joints.SetSize(lJointNum);

	for (s32 i = 0; i < lJointNum; i++) {
		ReadTextBuf(aData, mData.joints[i].name);
		ReadTextBuf(aData, mData.joints[i].nameEng);

		aData.Read(&mData.joints[i].type, sizeof(u8));

		mData.joints[i].aIndex = ReadChangeValue(aData, PhysicsIndexByteNum());
		mData.joints[i].bIndex = ReadChangeValue(aData, PhysicsIndexByteNum());

		aData.Read(&mData.joints[i].location[0], sizeof(f32) * 3);
		aData.Read(&mData.joints[i].rotate[0], sizeof(f32) * 3);

		aData.Read(&mData.joints[i].moveLimitMin[0], sizeof(f32) * 3);
		aData.Read(&mData.joints[i].moveLimitMax[0], sizeof(f32) * 3);
		aData.Read(&mData.joints[i].rotateLimitMin[0], sizeof(f32) * 3);
		aData.Read(&mData.joints[i].rotateLimitMax[0], sizeof(f32) * 3);

		aData.Read(&mData.joints[i].springConstantMove[0], sizeof(f32) * 3);
		aData.Read(&mData.joints[i].springConstantRotate[0], sizeof(f32) * 3);
	}

	return true;
}

void PmxLoader::Release() {

}

BOOL PmxLoader::IsLoaded() const {
	return false;
}

void PmxLoader::ReadTextBuf(Buffer& aData, PmxData::TextBuf& aTextBuf) {

	//�����̃o�b�t�@���̎擾
	s32 lBufLen;
	aData.Read(&lBufLen, sizeof(s32));
	
	//�t�@�C������ǂݍ���
	Buffer lTmpText;
	aData.Read(lTmpText, lBufLen);

	//�I�[�����������Ă��Ȃ���������Ȃ��̂ŁA�����
	Buffer lText;
	lText.Create(lBufLen + 2);

	CopyMem(lText.Get(), lTmpText.Get(), lTmpText.GetSize());
	lText[lBufLen] = '\0';
	lText[lBufLen + 1] = '\0';


	Buffer lRes;

	if (IsUtf8()) {
		CharCode::Utf8ToShiftJis(lText.Get(), lRes);
	}
	else if (IsUtf16()) {
		CharCode::Utf16ToShiftJis(lText.Get(), lRes);
	}
	else {
		CPOT_ERROR("PMX�̕����R�[�h���s���ł�");
	}

	aTextBuf.buf.SetSize(lRes.GetSize());
	CopyMem(&aTextBuf.buf[0], lRes.Get(), aTextBuf.buf.GetSize());
}

s32 PmxLoader::ReadChangeValue(Buffer& aData, s32 aReadByteNum) {

	u8 t[4];
	aData.Read(&t[0], sizeof(u8) * aReadByteNum);

	s32 lRes;
	switch (aReadByteNum) {
		case 1:
			lRes = *((s8*)t);
			break;
		case 2:
			lRes = *((s16*)t);
			break;
		case 4:
			lRes = *((s32*)t);
			break;
		default:
			CPOT_ERROR("");
			break;
	}
	return lRes;
}

}