#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/Usefull/buffer.h"

#include "./Pot/ModelLoader/StaticMeshModel.h"
#include "./Pot/ModelLoader/SkinMeshModel.h"

#include "./Pot/Usefull/path.h"


namespace cpot {

class BufferToMesh {

public:
	static void Load(StaticMeshModelCPU& aMesh, Buffer& aData) {
		LoadVertex(aMesh.vertex, aData);
		LoadIndex(aMesh.index, aData);
		LoadSubMesh(aMesh.submesh, aData);
	}
	
	static void Load(SkinMeshModelCPU& aMesh, Buffer& aData) {
		LoadVertex(aMesh.vertex, aData);
		LoadIndex(aMesh.index, aData);
		LoadSubMesh(aMesh.submesh, aData);
	}

private:
	static void LoadVertex(VectorSimple<StaticMeshVertex>& aVertex, Buffer& aData) {

		//���_�t�H�[�}�b�g�̊m�F
		u32 lVertexType = aData.Read<u32>();
		if (lVertexType != 0) return;

		//���_�f�[�^�̓ǂݍ���
		u32 lVertexNum = aData.Read<u32>();
		aVertex.SetSize(lVertexNum);

		u32 lVertexSize = sizeof(StaticMeshVertex);
		StaticMeshVertex* lVertexData = (StaticMeshVertex*)(&(aData[aData.GetPosition()]));

		CopyMem(&aVertex[0], lVertexData, lVertexSize * lVertexNum);
	}
	static void LoadVertex(VectorSimple<SkinMeshVertex>& aVertex, Buffer& aData) {

		//���_�t�H�[�}�b�g�̊m�F
		u32 lVertexType = aData.Read<u32>();
		if (lVertexType != 1) return;

		//���_�f�[�^�̓ǂݍ���
		u32 lVertexNum = aData.Read<u32>();
		aVertex.SetSize(lVertexNum);

		u32 lVertexSize = sizeof(SkinMeshVertex);
		SkinMeshVertex* lVertexData = (SkinMeshVertex*)(&(aData[aData.GetPosition()]));

		CopyMem(&aVertex[0], lVertexData, lVertexSize * lVertexNum);
	}
	static void LoadIndex(VectorSimple<u32>& aIndex, Buffer& aData) {

		//�C���f�b�N�X�t�H�[�}�b�g�̊m�F
		u32 lIndexType = aData.Read<u32>();
		if (lIndexType != 1) return;

		//���_�f�[�^�̓ǂݍ���
		u32 lIndexNum = aData.Read<u32>();
		aIndex.SetSize(lIndexNum);

		u32 lIndexSize = sizeof(u32);
		u32* lIndexData = (u32*)(&(aData[aData.GetPosition()]));

		CopyMem(&aIndex[0], lIndexData, lIndexSize * lIndexNum);
	}
	static void LoadSubMesh(VectorSimple<SubMeshCPU>& aSubMesh, Buffer& aData) {

		//���_�f�[�^�̓ǂݍ���
		u32 lSubMeshNum = aData.Read<u32>();
		aSubMesh.SetSize(lSubMeshNum);

		//�}�e���A���f�[�^�̓ǂݍ���
		for (u32 i = 0; i < lSubMeshNum; i++) {

			//�e�N�X�`�����̓ǂݍ���
			u32 lTextureNameLen = aData.Read<u32>();

			s32 lTextureIndex = aPmx.materials[i].textureRef;
			if (lTextureIndex != -1) {
				const CHAR* lTextureFileName = &(aPmx.textures[lTextureIndex].fileName.buf[0]);
				PathString lPath = Path::FromRelative(aPmx.fileName, lTextureFileName);
				if (Path::GetEx(lPath) == "tga") {
					lPath = Path::ChangeEx(lPath, "png");
				}
				aSubMesh[i].material.texture.name = lPath.Get();
			}

			//�g�D�[���e�N�X�`�����̓ǂݍ���
			s32 lToonTextureIndex = aPmx.materials[i].toonTexture;
			if (lToonTextureIndex != -1) {
				const CHAR* lToonTextureFileName = &(aPmx.textures[lToonTextureIndex].fileName.buf[0]);
				PathString lPath = Path::FromRelative(aPmx.fileName, lToonTextureFileName);
				if (Path::GetEx(lPath) == "tga") {
					lPath = Path::ChangeEx(lPath, "png");
				}
				aSubMesh[i].material.toonTexture.name = lPath.Get();
			}


			//�C���f�b�N�X�J�E���g�̓ǂݍ���
			aSubMesh[i].indexCount = aPmx.materials[i].indexNum;

			//�F�Ȃǂ̎擾
			aSubMesh[i].material.diffuse = Color::FromVector4(Vector4::FromFloat4(aPmx.materials[i].diffuse));
			aSubMesh[i].material.ambient = Vector3::FromFloat3(aPmx.materials[i].ambient);
			aSubMesh[i].material.specular = Vector3::FromFloat3(aPmx.materials[i].specular);
			aSubMesh[i].material.specularPower = aPmx.materials[i].specularPow;
		}
	}

};


}
