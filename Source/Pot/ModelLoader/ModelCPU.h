#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/ModelLoader/SubMesh.h"

namespace cpot {


template <typename VertexType>
struct ModelCPU {
public:
	VectorSimple<VertexType> vertex;
	VectorSimple<u32> index;
	VectorSimple<SubMeshCPU> submesh;
	PathString filePath;
};

struct StaticMeshVertex {
	Vector3 position;
	Vector3 normal;
	Vector2 texCoord;
};

struct SkinMeshVertex {
	Vector3 position;
	Vector3 normal;
	Vector2 texCoord;
	Vector3 weight;
	u16 weightIndex[4];
};

using SkinMeshModelCPU = ModelCPU<SkinMeshVertex>;
using StaticMeshModelCPU = ModelCPU<StaticMeshVertex>;

}