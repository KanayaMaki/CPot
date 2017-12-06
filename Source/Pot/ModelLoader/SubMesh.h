#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"
#include "./Pot/ModelLoader/Material.h"

namespace cpot {

struct SubMeshCPU {
	u32 indexCount;
	MaterialCPU material;
};

}
