
#include "./Pot/Atom/atom.h"
#include "./Pot/ModelLoader/PmxLoader.h"

#include "./Pot/ModelLoader/PmxToMesh.h"

using namespace cpot;

void main() {

	PmxLoader lPmx;
	lPmx.Load("./Miku/miku.pmx");

	StaticMeshModelCPU lStaticModel;
	PmxToMesh::Load(lStaticModel, lPmx.Get());

	int i = 0;
	i++;
}