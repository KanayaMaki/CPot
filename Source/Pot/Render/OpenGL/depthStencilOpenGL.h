//
//	content	:	OpenGL�ł�DepthStencil
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/depthStencil.h"
#include "./Pot/Render/OpenGL/Platform/depthOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/stencilOpenGLPlatform.h"

namespace cpot {

namespace openGL {

class DepthStencil : public DepthStencilBase {

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		//�����́A���O����f�[�^���������āA���[�h�ł���悤�ɂ�����
	};
	void Load(CDepthMode aMode) CPOT_OR {

		switch (aMode) {
			case cTest:
				mDepth.Load(platform::Depth::cTest);
				break;
			case cNoWrite:
				mDepth.Load(platform::Depth::cNoWrite);
				break;
			case cNoTest:
				mDepth.Load(platform::Depth::cNoTest);
				break;
		}

		//�X�e���V���@�\�͖����ɂ���
		mStencil.Load();
	}

public:
	void Release() CPOT_OR {
		mDepth.Release();
		mStencil.Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mDepth.IsLoaded() && mStencil.IsLoaded();
	}

public:
	platform::Depth mDepth;
	platform::Stencil mStencil;
};

}

using DepthStencil = openGL::DepthStencil;

}