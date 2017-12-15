#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"
#include "./Pot/Usefull/path.h"

namespace cpot {

struct TextureCPU {
	PathString name;
};

struct MaterialCPU {
	TextureCPU texture;
	TextureCPU toonTexture;
	Color diffuse;
	Vector3 specular;
	f32 specularPower;
	Vector3 ambient;
};


}
