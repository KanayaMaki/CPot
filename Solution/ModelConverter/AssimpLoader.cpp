#pragma once

#include "AssimpLoader.h"

#ifdef CPOT_ON_DEBUG
#pragma comment(lib, "./Assimp/Debug/assimp-vc140-mt.lib")
#pragma comment(lib, "./Assimp/Debug/zlibstaticd.lib")
#pragma comment(lib, "./Assimp/Debug/IrrXML.lib")
#else
#pragma comment(lib, "./Assimp/Release/assimp-vc140-mt.lib")
#pragma comment(lib, "./Assimp/Release/zlibstatic.lib")
#pragma comment(lib, "./Assimp/Release/IrrXML.lib")
#endif


#include <vector>


namespace cpot {






}
