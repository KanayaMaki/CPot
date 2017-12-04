#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/ModelLoader/SubMesh.h"

namespace cpot {


struct SkinMeshVertex {
	Vector3 position;
	Vector3 normal;
	Vector2 texCoord;
	Vector3 weight;
	u16 weightIndex[4];
};

struct SkinMeshModelCPU {
public:
	VectorSimple<SkinMeshVertex> vertex;
	VectorSimple<u32> index;
	VectorSimple<SubMeshCPU> submesh;
};

}
