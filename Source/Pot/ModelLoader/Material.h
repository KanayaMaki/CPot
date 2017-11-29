#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

namespace cpot {

struct Texture {
	String<128> name;
};

struct Material {
	Texture texture;
	Color diffuse;
};


}
