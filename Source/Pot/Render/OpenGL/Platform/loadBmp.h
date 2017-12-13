#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/buffer.h"
#include "./Pot/File/file.h"

#include "./Pot/Render/OpenGL/Platform/bitmap.h"


namespace cpot {


class BmpLoader {
public:
	static BitmapData& Load(const CHAR* aFileName, BitmapData& aResult) {

		//�t�@�C�����J��
		FileIn lFile;
		lFile.Open(aFileName, true);

		//�t�@�C�����J���Ȃ�������
		if (!lFile.IsOpen()) {
			return aResult;
		}

		Buffer lBuffer;
		lFile.Read(lBuffer);
		return Load(lBuffer, aResult);
	}
	static BitmapData& Load(Buffer& aBMPData, BitmapData& aResult) {

		u8 lHeader[54];
		u32 lDataPos;
		u32 lWidth, lHeight;
		u32 lLineSize;
		u32 lBytePerPixel;
		u32 lImageSize;

		aBMPData.Read(lHeader, 54);
		if (lHeader[0] != 'B' || lHeader[1] != 'M') {
			return aResult;
		}

		// �o�C�g�z�񂩂琮����ǂݍ���
		lDataPos = *(int*)&(lHeader[0x0A]);
		lImageSize = *(int*)&(lHeader[0x22]);
		lWidth = *(int*)&(lHeader[0x12]);
		lHeight = *(int*)&(lHeader[0x16]);

		if (aBMPData.GetSize() <= lWidth * lHeight * 4) {
			lBytePerPixel = 3;
		}
		else {
			lBytePerPixel = 4;
		}

		lLineSize = Align(lWidth * lBytePerPixel, 4UL);
		lImageSize = lLineSize * lHeight;


		aResult.data.Create(lImageSize);
		
		
		//BMP�t�@�C���́A��������E��Ƀf�[�^���i�[����Ă���
		//���c�����ւ���K�v������
		//�܂��ABGR��BGRA�̏��ԂŃs�N�Z���̐F�f�[�^�������Ă���̂ŁA������ϊ�����K�v������
		
		//RGB�l��ϊ����ď�������
		for (s32 i = 0; i < lHeight; i++) {
			u32 lReadBase = lDataPos + (lHeight - i - 1) * lLineSize;	//�ǂݍ��ޑΏۃs�N�Z���́A�ŏ��̃o�C�g�̃C���f�b�N�X
			u32 lWriteBase = i * lWidth * lBytePerPixel;	//�������ޑΏۃs�N�Z���́A�ŏ��̃o�C�g�̃C���f�b�N�X
			for (u32 j = 0; j < lWidth; j++) {
				aResult.data[lWriteBase + 0] = aBMPData[lReadBase + 2]; //R
				aResult.data[lWriteBase + 1] = aBMPData[lReadBase + 1]; //G
				aResult.data[lWriteBase + 2] = aBMPData[lReadBase + 0]; //B
				lReadBase += lBytePerPixel;
				lWriteBase += lBytePerPixel;
			}
		}
		//�A���t�@�l�̏�������
		if (lBytePerPixel == 4) {
			for (s32 i = 0; i < lHeight; i++) {
				u32 lReadBase = lDataPos + (lHeight - i - 1) * lLineSize;	//�ǂݍ��ޑΏۃs�N�Z���́A�ŏ��̃o�C�g�̃C���f�b�N�X
				u32 lWriteBase = i * lWidth * lBytePerPixel;	//�������ޑΏۃs�N�Z���́A�ŏ��̃o�C�g�̃C���f�b�N�X
				for (u32 j = 0; j < lWidth; j++) {
					aResult.data[lWriteBase + 3] = aBMPData[lReadBase + 3]; //A
					lReadBase += lBytePerPixel;
					lWriteBase += lBytePerPixel;
				}
			}
		}

		aResult.height = lHeight;
		aResult.width = lWidth;
		aResult.depth = 8;
		aResult.pixelBytes = lBytePerPixel;

		return aResult;
	}

};


}
