#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/ModelLoader/SubMesh.h"

namespace cpot {

struct StaticMeshVertex {
	Vector3 position;
	Vector3 normal;
	TexCoord texCoord;
};

struct StaticMeshModelCPU {
public:
	VectorSimple<StaticMeshVertex> vertex;
	VectorSimple<u32> index;
	VectorSimple<SubMeshCPU> submesh;
};

}
