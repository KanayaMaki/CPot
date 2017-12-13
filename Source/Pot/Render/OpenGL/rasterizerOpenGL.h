//
//	content	:	OpenGLÇ≈ÇÃRasterizer
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
	void Load(CFillMode aFillMode, CCullMode aCullMode) CPOT_OR {
		BOOL lIsSolid = aFillMode == cSolid;


		//ÉJÉäÉìÉOÇÃê›íË
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