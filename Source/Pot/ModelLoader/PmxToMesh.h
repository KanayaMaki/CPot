#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/ModelLoader/PmxData.h"
#include "./Pot/ModelLoader/StaticMeshModel.h"
#include "./Pot/ModelLoader/SkinMeshModel.h"

#include "./Pot/Usefull/path.h"


namespace cpot {

class PmxToMesh {

public:
	static void Load(StaticMeshModelCPU& aMesh, const PmxData& aPmx) {
		LoadVertex(aMesh.vertex, aPmx);
		LoadIndex(aMesh.index, aPmx);
		LoadSubMesh(aMesh.submesh, aPmx);
	}
	static void LoadVertex(VectorSimple<StaticMeshVertex>& aVertex, const PmxData& aPmx) {

		//頂点データの読み込み
		aVertex.SetSize(aPmx.vertexs.GetSize());
		for (u32 i = 0; i < aPmx.vertexs.GetSize(); i++) {
			aVertex[i].position = Vector3::FromFloat3(aPmx.vertexs[i].location);
			aVertex[i].normal = Vector3::FromFloat3(aPmx.vertexs[i].normal);
			aVertex[i].texCoord = Vector2::FromFloat2(aPmx.vertexs[i].uv);
		}
	}
	static void LoadIndex(VectorSimple<u32>& aIndex, const PmxData& aPmx) {

		//インデックスデータの読み込み
		aIndex.SetSize(aPmx.indexs.GetSize());
		for (u32 i = 0; i < aPmx.indexs.GetSize(); i++) {
			aIndex[i] = aPmx.indexs[i];
		}
	}
	static void LoadSubMesh(VectorSimple<SubMeshCPU>& aSubMesh, const PmxData& aPmx) {

		//マテリアルデータの読み込み
		aSubMesh.SetSize(aPmx.materials.GetSize());
		for (u32 i = 0; i < aPmx.materials.GetSize(); i++) {

			//テクスチャ名の読み込み
			s32 lTextureIndex = aPmx.materials[i].textureRef;
			if (lTextureIndex != -1) {
				const CHAR* lTextureFileName = &(aPmx.textures[lTextureIndex].fileName.buf[0]);
				PathString lPath = Path::FromRelative(aPmx.fileName, lTextureFileName);
				if (Path::GetEx(lPath) == "tga") {
					lPath = Path::ChangeEx(lPath, "png");
				}
				aSubMesh[i].material.texture.name = lPath.Get();
			}

			//トゥーンテクスチャ名の読み込み
			s32 lToonTextureIndex = aPmx.materials[i].toonTexture;
			if (lToonTextureIndex != -1) {
				const CHAR* lToonTextureFileName = &(aPmx.textures[lToonTextureIndex].fileName.buf[0]);
				PathString lPath = Path::FromRelative(aPmx.fileName, lToonTextureFileName);
				if (Path::GetEx(lPath) == "tga") {
					lPath = Path::ChangeEx(lPath, "png");
				}
				aSubMesh[i].material.toonTexture.name = lPath.Get();
			}


			//インデックスカウントの読み込み
			aSubMesh[i].indexCount = aPmx.materials[i].indexNum;

			//色などの取得
			aSubMesh[i].material.diffuse = Color::FromVector4(Vector4::FromFloat4(aPmx.materials[i].diffuse));
			aSubMesh[i].material.ambient = Vector3::FromFloat3(aPmx.materials[i].ambient);
			aSubMesh[i].material.specular = Vector3::FromFloat3(aPmx.materials[i].specular);
			aSubMesh[i].material.specularPower = aPmx.materials[i].specularPow;
		}
	}

	static void Load(SkinMeshModelCPU& aMesh, const PmxData& aPmx) {
		LoadVertex(aMesh.vertex, aPmx);
		LoadIndex(aMesh.index, aPmx);
		LoadSubMesh(aMesh.submesh, aPmx);
	}

	static void LoadVertex(VectorSimple<SkinMeshVertex>& aVertex, const PmxData& aPmx) {

		//頂点データの読み込み
		aVertex.SetSize(aPmx.vertexs.GetSize());
		for (u32 i = 0; i < aPmx.vertexs.GetSize(); i++) {
			aVertex[i].position = Vector3::FromFloat3(aPmx.vertexs[i].location);
			aVertex[i].normal = Vector3::FromFloat3(aPmx.vertexs[i].normal);
			aVertex[i].texCoord = Vector2::FromFloat2(aPmx.vertexs[i].uv);
			aVertex[i].weight = Vector3::FromFloat3(aPmx.vertexs[i].weight.weight);
			for (u32 j = 0; j < 4; j++) {
				aVertex[i].weightIndex[j] = aPmx.vertexs[i].weight.index[j];
			}
		}
	}
	
};


}
