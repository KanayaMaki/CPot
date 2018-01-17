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


struct VectorKey {
	f32 time;
	Vector3 value;
};

struct QuaternionKey {
	f32 time;
	Quaternion value;
};

struct NodeAnimation {
	String<32> nodeName;
	std::vector<VectorKey> translate;
	std::vector<VectorKey> scale;
	std::vector<QuaternionKey> rotation;
};

struct Animation {
	f32 duration;
	std::vector<NodeAnimation> body;
};

inline Vector3 FromAssimp(const aiVector3D& value) {
	return Vector3(value.x, value.y, value.z);
}

inline VectorKey FromAssimp(const aiVectorKey& key) {

	VectorKey v;
	v.time = key.mTime;
	v.value = FromAssimp(key.mValue);
	return v;
}

inline QuaternionKey FromAssimp(const aiQuatKey& key) {

	QuaternionKey v;
	v.time = key.mTime;
	v.value = Quaternion(key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w);
	return v;
}

class AssimpLoader {
private:
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
			v.position = Vector3(lVertices[lPosCur.Position()].x, lVertices[lPosCur.Position()].y, lVertices[lPosCur.Position()].z);
			v.normal = Vector3(lNormal[lNorCur.Position()].x, lNormal[lNorCur.Position()].y, lNormal[lNorCur.Position()].z).Normal();
			v.texCoord = TexCoord(lTex[lUVCur.Position()].x, 1.0f - lTex[lUVCur.Position()].y);
			aVertex.push_back(v);

			lPosCur++;
			lNorCur++;
			lUVCur++;
		}
	}

	static void LoadVertex(std::vector<StaticTangentMeshVertex>& aVertex, const aiMesh* aMesh) {

		BOOL lHasPosition = aMesh->HasPositions();
		VectorCursor lPosCur;
		aiVector3D* lVertices = aMesh->mVertices;


		BOOL lHasNormal = aMesh->HasNormals();
		VectorCursor lNorCur;
		aiVector3D* lNormal = aMesh->mNormals;
		aiVector3D* lTangent = aMesh->mTangents;
		aiVector3D* lBiTangent = aMesh->mBitangents;


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
			StaticTangentMeshVertex v;
			v.position = Vector3(lVertices[lPosCur.Position()].x, lVertices[lPosCur.Position()].y, lVertices[lPosCur.Position()].z);
			v.normal = Vector3(lNormal[lNorCur.Position()].x, lNormal[lNorCur.Position()].y, lNormal[lNorCur.Position()].z).Normal();
			v.tangent = Vector3(lTangent[lNorCur.Position()].x, lTangent[lNorCur.Position()].y, lTangent[lNorCur.Position()].z).Normal();
			v.biNormal = Vector3(lBiTangent[lNorCur.Position()].x, lBiTangent[lNorCur.Position()].y, lBiTangent[lNorCur.Position()].z).Normal();
			v.texCoord = TexCoord(lTex[lUVCur.Position()].x, 1.0f - lTex[lUVCur.Position()].y);
			aVertex.push_back(v);

			lPosCur++;
			lNorCur++;
			lUVCur++;
		}
	}

	//
	//	マテリアルの読み込み
	//
	#pragma region Material

	//ディフューズの取得
	static Color LoadDiffuse(const aiMaterial* aAiMat) {
		aiColor4D lColor;

		aAiMat->Get(AI_MATKEY_COLOR_DIFFUSE, lColor);
		return Color(lColor.r, lColor.g, lColor.b, lColor.a);
	}

	//スペキュラーの取得
	static Vector3 LoadSpecular(const aiMaterial* aAiMat) {
		aiColor4D lColor;

		aAiMat->Get(AI_MATKEY_COLOR_SPECULAR, lColor);
		return Vector3(lColor.r, lColor.g, lColor.b);
	}

	//スペキュラーパワーの取得
	static float LoadSpecularPower(const aiMaterial* aAiMat) {
		float lSpecularPow;
		aAiMat->Get(AI_MATKEY_SHININESS, lSpecularPow);
		return lSpecularPow;
	}

	//アンビエントの取得
	static Vector3 LoadAmbient(const aiMaterial* aAiMat) {
		aiColor4D lColor;

		aAiMat->Get(AI_MATKEY_COLOR_AMBIENT, lColor);
		return Vector3(lColor.r, lColor.g, lColor.b);
	}

	//ディフューズテクスチャの取得
	static void LoadDiffuseTexture(TextureCPU& aTexture, const aiMaterial* aAiMat) {
		aiString tex_name;

		if (aAiMat->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), tex_name) == AI_SUCCESS) {
			aTexture.name = tex_name.C_Str();
		}
	}

	//ノーマルテクスチャの取得
	static void LoadNormalTexture(TextureCPU& aTexture, const aiMaterial* aAiMat) {
		aiString tex_name;

		if (aAiMat->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), tex_name) == AI_SUCCESS) {
			aTexture.name = tex_name.C_Str();
		}
	}

	//
	//通常マテリアル
	static void LoadMaterial(MaterialCPU& aMaterial, const aiMaterial* aAiMat) {

		//色などの取得
		aMaterial.diffuse = LoadDiffuse(aAiMat);
		aMaterial.specular = LoadSpecular(aAiMat);
		aMaterial.specularPower = LoadSpecularPower(aAiMat);
		aMaterial.ambient = LoadAmbient(aAiMat);

		//テクスチャの取得
		LoadDiffuseTexture(aMaterial.texture, aAiMat);	//ディフューズテクスチャの取得
	}

	//
	//バンプのマテリアル
	static void LoadMaterial(BampMaterialCPU& aMaterial, const aiMaterial* aAiMat) {

		//色などの取得
		aMaterial.diffuse = LoadDiffuse(aAiMat);
		aMaterial.specular = LoadSpecular(aAiMat);
		aMaterial.specularPower = LoadSpecularPower(aAiMat);
		aMaterial.ambient = LoadAmbient(aAiMat);

		//テクスチャの取得
		LoadDiffuseTexture(aMaterial.texture, aAiMat);	//ディフューズテクスチャの取得
		LoadNormalTexture(aMaterial.bampTexture, aAiMat);	//ノーマルテクスチャの取得
	}

	#pragma endregion


	static void LoadNodeAnimation(Animation& aAnimation, const aiNodeAnim* aNode) {

		//
		//ノード情報の取得
		//
		NodeAnimation lNodeAnim;

		//ノード名の取得
		lNodeAnim.nodeName = aNode->mNodeName.C_Str();

		//ポジションのキーの取得
		for (unsigned int i = 0; i < aNode->mNumPositionKeys; i++) {
			lNodeAnim.translate.push_back(FromAssimp(aNode->mPositionKeys[i]));
		}

		//スケールのキーの取得
		for (unsigned int i = 0; i < aNode->mNumScalingKeys; i++) {
			lNodeAnim.scale.push_back(FromAssimp(aNode->mScalingKeys[i]));
		}

		//回転のキーの取得
		for (unsigned int i = 0; i < aNode->mNumRotationKeys; i++) {
			lNodeAnim.rotation.push_back(FromAssimp(aNode->mRotationKeys[i]));
		}

		aAnimation.body.push_back(lNodeAnim);
	}

	static void LoadAnimation(Animation& aAnimation, const aiAnimation* aAnim) {

		//
		//ノード情報の取得
		//
		for (unsigned int i = 0; i < aAnim->mNumChannels; i++) {
			LoadNodeAnimation(aAnimation, aAnim->mChannels[i]);
		}
		aAnimation.duration = aAnim->mDuration;
	}

public:
	template<typename VertexType, typename MaterialType>
	static BOOL Load(ModelCPU<VertexType, MaterialType>& aMesh, const CHAR* aFileName) {

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
						s32 index = k;	//面の回る方向を時計回りにする
						u32 v = lFace[j].mIndices[index] + lIndexBase;
						lIndex[lMesh->mMaterialIndex].push_back(v);
					}
				}
			}

			LoadVertex(lVertex, lMesh);

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
			SubMeshCPU<MaterialType>& lSubMesh = aMesh.submesh[i];

			LoadMaterial(aMesh.submesh[i].material, lMaterial);

			//サブメッシュの対象となるインデックスの範囲の設定
			lSubMesh.indexCount = lIndex[i].size();
		}

		aMesh.filePath = aFileName;


		Animation lAnimation[16];
		for (unsigned int i = 0; i < scene->mNumAnimations; i++) {
			LoadAnimation(lAnimation[i], scene->mAnimations[i]);
		}

		return true;

	}
};

}
