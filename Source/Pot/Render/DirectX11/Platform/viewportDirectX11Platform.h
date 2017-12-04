#pragma once

#include"./Pot/Render/DirectX11/Platform/deviceDirectX11Platform.h"


namespace cpot {

namespace directX11 {

namespace platform {


class Viewport {
public:
	Vector2 mLeftTop;
	Vector2 mSize;
	f32 mMinDepth;
	f32 mMaxDepth;
};


}

}

}