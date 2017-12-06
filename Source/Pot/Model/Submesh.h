#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Model/Material.h"

namespace cpot {

struct Submesh {
	u32 indexCount;
	u32 indexStartCount;
	Material material;
};

}
