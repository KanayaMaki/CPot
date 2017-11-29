#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/ModelLoader/SubMesh.h"

namespace cpot {

struct StaticMeshVertex {
	Vector3 position;
	Vector3 normal;
	Vector2 texCoord;
};

class StaticMeshModel {
	Vector<StaticMeshVertex> vertex;
	Vector<u32> index;
	Vector<SubMesh> submesh;
};

}
