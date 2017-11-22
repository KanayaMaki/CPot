//
//	content	:	Texture��DirectX11�ł̎���
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceLoadList.h"
#include "./Pot/Render/texture.h"
#include "./Pot/Render/DirectX11/Platform/textureDirectX11Platform.h"


namespace cpot {

namespace directX11 {


class Texture2DDirectX11Data : public ResourceLoadList<Texture2DDirectX11Data, String<128>> {

};

class Texture2D : public Texture2DBase {

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mTexture.Load(Texture2DDirectX11Data::S().Get(aUnionName).Get());
	};
	void Load(const CHAR* aUnionName) CPOT_OR {
		Load(HashTableKey(aUnionName));	//�Ϗ�
	};

	//�v���b�g�t�H�[������̓ǂݍ���
	void LoadDirectX11(const CHAR* aFileName) {
		mTexture.Load(aFileName);
	};

public:
	void Release() CPOT_OR {
		mTexture.Release();
	};

public:
	BOOL IsLoad() const CPOT_OR {
		return mTexture.IsLoaded();
	};


	//�t�B�[���h
	#pragma region Field

public:
	platform::Texture2D mTexture;

	#pragma endregion
};

}

using Texture2D = directX11::Texture2D;

}