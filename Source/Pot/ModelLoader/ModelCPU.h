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

public:
	void LoadVertex(VectorSimple<VertexType>& lVertex) {
		lVertex.SetSize(vertex.GetSize());
		for (u32 i = 0; i < vertex.GetSize(); i++) {
			lVertex[i] = vertex[i];
		}
	}
};

struct StaticMeshVertex {
	Vector3 position;
	Vector3 normal;
	TexCoord texCoord;
};

struct SkinMeshVertex {
	Vector3 position;
	Vector3 normal;
	TexCoord texCoord;
	Vector3 weight;
	u16 weightIndex[4];
};

using SkinMeshModelCPU = ModelCPU<SkinMeshVertex>;
using StaticMeshModelCPU = ModelCPU<StaticMeshVertex>;

}
