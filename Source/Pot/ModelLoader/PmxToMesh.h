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
	static void Load(StaticMeshModel& aMesh, const PmxData& aPmx) {

		//頂点データの読み込み
		aMesh.vertex.SetSize(aPmx.vertexs.GetSize());
		for (u32 i = 0; i < aPmx.vertexs.GetSize(); i++) {
			aMesh.vertex[i].position = Vector3::FromFloat3(aPmx.vertexs[i].location);
			aMesh.vertex[i].normal = Vector3::FromFloat3(aPmx.vertexs[i].normal);
			aMesh.vertex[i].texCoord = Vector2::FromFloat2(aPmx.vertexs[i].uv);
		}

		//インデックスデータの読み込み
		aMesh.index.SetSize(aPmx.indexs.GetSize());
		for (u32 i = 0; i < aPmx.indexs.GetSize(); i++) {
			aMesh.index[i] = aPmx.indexs[i];
		}

		//マテリアルデータの読み込み
		aMesh.submesh.SetSize(aPmx.materials.GetSize());
		for (u32 i = 0; i < aPmx.materials.GetSize(); i++) {
			
			//テクスチャ名の読み込み
			s32 lTextureIndex = aPmx.materials[i].textureRef;
			if (lTextureIndex != -1) {
				const CHAR* lTextureFileName = &(aPmx.textures[lTextureIndex].fileName.buf[0]);
				PathString lPath = Path::FromRelative(aPmx.fileName, lTextureFileName);
				aMesh.submesh[i].material.texture.name = lPath.Get();
			}
			
			//インデックスカウントの読み込み
			aMesh.submesh[i].indexCount = aPmx.materials[i].indexNum;

			//色などの取得
			aMesh.submesh[i].material.diffuse = Color::FromVector4(Vector4::FromFloat4(aPmx.materials[i].diffuse));
			aMesh.submesh[i].material.ambient = Vector3::FromFloat3(aPmx.materials[i].ambient);
			aMesh.submesh[i].material.specular = Vector3::FromFloat3(aPmx.materials[i].specular);
			aMesh.submesh[i].material.specularPower = aPmx.materials[i].specularPow;
		}
	}

	static void Load(SkinMeshModel& aMesh, const PmxData& aPmx) {
		
		//頂点データの読み込み
		aMesh.vertex.SetSize(aPmx.vertexs.GetSize());
		for (u32 i = 0; i < aPmx.vertexs.GetSize(); i++) {
			aMesh.vertex[i].position = Vector3::FromFloat3(aPmx.vertexs[i].location);
			aMesh.vertex[i].normal = Vector3::FromFloat3(aPmx.vertexs[i].normal);
			aMesh.vertex[i].texCoord = Vector2::FromFloat2(aPmx.vertexs[i].uv);
			aMesh.vertex[i].weight = Vector3::FromFloat3(aPmx.vertexs[i].weight.weight);
			for (u32 j = 0; j < 4; j++) {
				aMesh.vertex[i].weightIndex[j] = aPmx.vertexs[i].weight.index[j];
			}
		}

		//インデックスデータの読み込み
		aMesh.index.SetSize(aPmx.indexs.GetSize());
		for (u32 i = 0; i < aPmx.indexs.GetSize(); i++) {
			aMesh.index[i] = aPmx.indexs[i];
		}

		//マテリアルデータの読み込み
		aMesh.submesh.SetSize(aPmx.materials.GetSize());
		for (u32 i = 0; i < aPmx.materials.GetSize(); i++) {

			//テクスチャ名の読み込み
			s32 lTextureIndex = aPmx.materials[i].textureRef;
			if (lTextureIndex != -1) {
				const CHAR* lTextureFileName = &(aPmx.textures[lTextureIndex].fileName.buf[0]);
				PathString lPath = Path::FromRelative(aPmx.fileName, lTextureFileName);
				aMesh.submesh[i].material.texture.name = lPath.Get();
			}

			//インデックスカウントの読み込み
			aMesh.submesh[i].indexCount = aPmx.materials[i].indexNum;

			//色などの取得
			aMesh.submesh[i].material.diffuse = Color::FromVector4(Vector4::FromFloat4(aPmx.materials[i].diffuse));
			aMesh.submesh[i].material.ambient = Vector3::FromFloat3(aPmx.materials[i].ambient);
			aMesh.submesh[i].material.specular = Vector3::FromFloat3(aPmx.materials[i].specular);
			aMesh.submesh[i].material.specularPower = aPmx.materials[i].specularPow;
		}
	}
	
};


}
