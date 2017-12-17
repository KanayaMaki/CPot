#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/Usefull/buffer.h"

#include "./Pot/ModelLoader/ModelCPU.h"

#include "./assimp/Importer.hpp"	//OO version Header!
#include "./assimp/postprocess.h"
#include "./assimp/scene.h"
#include "./assimp/DefaultLogger.hpp"
#include "./assimp/LogStream.hpp"

#include <vector>


namespace cpot {

class VectorCursor {
public:
	VectorCursor() {
		mPosition = 0;
		mDelta = 1;
	}

	u32 Position() {
		return mPosition;
	}

	const VectorCursor& operator ++() {
		mPosition += mDelta;
		return *this;

	}
	VectorCursor operator ++(int) {
		VectorCursor t = *this;
		mPosition += mDelta;
		return t;
	}

public:
	u32 mPosition;
	u32 mDelta;
};

class AssimpLoader {
private:
	template<typename VertexType>
	static void LoadVertex(std::vector<VertexType>& aVertex, const aiMesh* aMesh) {
		
	}

	template<>
	static void LoadVertex(std::vector<StaticMeshVertex>& aVertex, const aiMesh* aMesh) {

		BOOL lHasPosition = aMesh->HasPositions();
		VectorCursor lPosCur;
		aiVector3D* lVertices = aMesh->mVertices;


		BOOL lHasNormal = aMesh->HasNormals();
		VectorCursor lNorCur;
		aiVector3D* lNormal = aMesh->mNormals;


		BOOL lHasTex = aMesh->HasTextureCoords(0);
		VectorCursor lUVCur;
		aiVector3D* lTex;
		aiVector3D tTex(0.0f, 0.0f, 0.0f);
		if (lHasTex) {
			lTex = aMesh->mTextureCoords[0];
		}
		else {
			lTex = &tTex;
			lUVCur.mDelta = 0;
		}


		for (s32 j = 0; j < aMesh->mNumVertices; j++) {
			StaticMeshVertex v;
			v.position = Vector3(lVertices[lPosCur.Position()].x, lVertices[lPosCur.Position()].y, lVertices[lPosCur.Position()].z) * 0.01f;
			v.normal = Vector3(lNormal[lNorCur.Position()].x, lNormal[lNorCur.Position()].y, lNormal[lNorCur.Position()].z).Normal();
			v.texCoord = TexCoord(lTex[lUVCur.Position()].x, 1.0f - lTex[lUVCur.Position()].y);
			aVertex.push_back(v);

			lPosCur++;
			lNorCur++;
			lUVCur++;
		}
	}


public:
	template<typename VertexType>
	static BOOL Load(ModelCPU<VertexType>& aMesh, const CHAR* aFileName) {

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(aFileName, aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		std::vector< std::vector<u32> > lIndex;
		std::vector<VertexType> lVertex;

		unsigned int lMaterialNum = scene->mNumMaterials;

		lIndex.resize(lMaterialNum);
		int tmp = 0;
		tmp++;

		u32 lIndexBase = 0;	//複数のメッシュをまとめるため、インデックス値をずらす必要がある

		//頂点情報とインデックス情報の取得
		for (s32 i = 0; i < scene->mNumMeshes; i++) {

			const aiMesh* lMesh = scene->mMeshes[i];

			if (lMesh->HasFaces()) {
				aiFace* lFace = lMesh->mFaces;
				for (s32 j = 0; j < lMesh->mNumFaces; j++) {
					for (s32 k = 0; k < lFace[j].mNumIndices; k++) {
						u32 v = lFace[j].mIndices[k] + lIndexBase;
						lIndex[lMesh->mMaterialIndex].push_back(v);
					}
				}
			}

			LoadVertex<VertexType>(lVertex, lMesh);

			lIndexBase += lMesh->mNumVertices;
		}


		//
		//取得した情報を、MeshCPUに変換する
		//

		//Vertex
		aMesh.vertex.SetSize(lVertex.size());
		for (int i = 0; i < lVertex.size(); i++) {
			aMesh.vertex[i] = lVertex[i];
		}

		//Index
		{
			int lIndexNum = 0;
			for (int i = 0; i < lIndex.size(); i++) {
				lIndexNum += lIndex[i].size();
			}

			aMesh.index.SetSize(lIndexNum);

			u32 tIndexBase = 0;
			for (int i = 0; i < lIndex.size(); i++) {
				for (int j = 0; j < lIndex[i].size(); j++) {
					aMesh.index[tIndexBase + j] = lIndex[i][j];
				}
				tIndexBase += lIndex[i].size();
			}
		}

		//
		//マテリアル情報の取得
		//

		aMesh.submesh.SetSize(lMaterialNum);

		int lIndexStart = 0;
		for (s32 i = 0; i < scene->mNumMaterials; i++) {
			aiMaterial* lMaterial = scene->mMaterials[i];
			SubMeshCPU& lSubMesh = aMesh.submesh[i];

			aiColor4D lColor;

			//ディフューズの取得
			lMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, lColor);
			lSubMesh.material.diffuse = Color(lColor.r, lColor.g, lColor.b, lColor.a);

			//スペキュラーの取得
			lMaterial->Get(AI_MATKEY_COLOR_SPECULAR, lColor);
			lSubMesh.material.specular = Vector3(lColor.r, lColor.g, lColor.b);

			//スペキュラーパワーの取得
			float lSpecularPow;
			lMaterial->Get(AI_MATKEY_SHININESS, lSpecularPow);
			lSubMesh.material.specularPower = lSpecularPow;

			//アンビエントの取得
			lMaterial->Get(AI_MATKEY_COLOR_AMBIENT, lColor);
			lSubMesh.material.ambient = Vector3(lColor.r, lColor.g, lColor.b);

			//テクスチャ名の取得
			aiString tex_name;

			if (lMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), tex_name) == AI_SUCCESS) {
				lSubMesh.material.texture.name = tex_name.C_Str();
			}

			//サブメッシュの対象となるインデックスの範囲の設定
			lSubMesh.indexCount = lIndex[i].size();
		}

		aMesh.filePath = aFileName;

		return true;
		
	}

};

}
