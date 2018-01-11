
#include "./Pot/Atom/atom.h"
#include "./Pot/ModelLoader/PmxLoader.h"

#include "./Pot/ModelLoader/PmxToMesh.h"
#include "AssimpLoader.h"
#include "./Pot/ModelLoader/ConvertBufferMesh.h"

#include "./Pot/File/file.h"

#include <string>
#include <iostream>

using namespace cpot;

void Convert(const char* aFileName);

void main(int aArgNum, const char** aArgs) {

	for (int i = 1; i < aArgNum; i++) {
		Convert(aArgs[i]);
	}

	Convert("./BoneModel/boneModel.fbx");

	while (true) {
		std::cout << "変換するファイル名を入力してください（Eで終了）\n　：";

		std::string lFileName;
		std::cin >> lFileName;

		if (lFileName == "E" || lFileName == "e") {
			break;
		}

		std::string from = "\"";
		std::string to = "";
		std::string::size_type pos = lFileName.find(from);
		while (pos != std::string::npos) {
			lFileName.replace(pos, from.size(), to);
			pos = lFileName.find(from, pos + to.size());
		}

		Convert(lFileName.c_str());
	}
}

void Convert(const char* aFileName) {

	PathString lInFilePath = aFileName;

	StaticMeshModelCPU lStaticModel;

	if (Path::GetEx(lInFilePath) == "pmx") {

		PmxLoader lPmx;
		lPmx.Load(lInFilePath.Get());

		PmxToMesh::Load(lStaticModel, lPmx.Get());

	}
	else {
		AssimpLoader::Load(lStaticModel, lInFilePath.Get());
	}

	Buffer b;
	BufferToMesh::Save(lStaticModel, b);

	PathString lOutFilePath = Path::ChangeEx(lInFilePath, "pmo");

	FileOut lOutFile;
	lOutFile.Open(lOutFilePath.Get(), false, true);
	lOutFile.Write(b);
	lOutFile.Close();
}