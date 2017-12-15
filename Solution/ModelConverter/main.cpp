
#include "./Pot/Atom/atom.h"
#include "./Pot/ModelLoader/PmxLoader.h"

#include "./Pot/ModelLoader/PmxToMesh.h"
#include "./Pot/ModelLoader/ConvertBufferMesh.h"

#include "./Pot/File/file.h"

using namespace cpot;

void main() {

	PmxLoader lPmx;
	lPmx.Load("./Miku/miku.pmx");

	StaticMeshModelCPU lStaticModel;
	PmxToMesh::Load(lStaticModel, lPmx.Get());

	Buffer b;
	BufferToMesh::Save(lStaticModel, b);
	
	FileOut lOutFile;
	lOutFile.Open("./Miku/miku.pmo", false, true);
	lOutFile.Write(b);
	lOutFile.Close();


	Buffer lLoadBuffer;

	FileIn lInFile;
	lInFile.Open("./Miku/miku.pmo", true);
	lInFile.Read(lLoadBuffer);

	StaticMeshModelCPU lLoadStaticModel;
	BufferToMesh::Load(lLoadStaticModel, lLoadBuffer);

	int i = 0;
	i++;
}