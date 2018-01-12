//
//	content	:	OpenGL�ł�Rasterizer
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/rasterizer.h"
#include "./Pot/Render/OpenGL/Platform/cullOpenGLPlatform.h"

namespace cpot {

namespace openGL {

class Rasterizer : public RasterizerBase {

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		//�����́A���O����f�[�^���������āA���[�h�ł���悤�ɂ�����
	};
	void Load(CFillMode aFillMode, CCullMode aCullMode) CPOT_OR {
		BOOL lIsSolid = aFillMode == cSolid;


		//�J�����O�̐ݒ�
		BOOL lCullFace = aCullMode != cCullNone;
		GLenum lFrontFace = GL_CW;
		if (aCullMode == cCullCW) {
			lFrontFace = GL_CCW;
		}

		mCull.Load(lCullFace, lFrontFace);
	}

public:
	void Release() CPOT_OR {
		mCull.Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mCull.IsLoaded();
	}

public:
	platform::Cull mCull;

};

}

using Rasterizer = openGL::Rasterizer;

}