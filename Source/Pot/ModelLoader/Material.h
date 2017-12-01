#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

namespace cpot {

struct Texture {
	String<256> name;
};

struct Material {
	Texture texture;
	Color diffuse;
	Vector3 specular;
	f32 specularPower;
	Vector3 ambient;
};


}
