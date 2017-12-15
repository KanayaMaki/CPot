#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/Usefull/buffer.h"

#include "./Pot/ModelLoader/ModelCPU.h"

#include "./Pot/Usefull/path.h"


namespace cpot {

class BufferToMesh {

public:
	static void Load(StaticMeshModelCPU& aMesh, Buffer& aData) {
		LoadVertex(aMesh.vertex, aData);
		LoadIndex(aMesh.index, aData);
		LoadSubMesh(aMesh.submesh, aData);
	}
	static void Load(SkinMeshModelCPU& aMesh, Buffer& aData) {
		LoadVertex(aMesh.vertex, aData);
		LoadIndex(aMesh.index, aData);
		LoadSubMesh(aMesh.submesh, aData);
	}

private:
	static void LoadVertex(VectorSimple<StaticMeshVertex>& aVertex, Buffer& aData) {

		//頂点フォーマットの確認
		u32 lVertexType = aData.Read<u32>();
		if (lVertexType != 0) return;

		//頂点データの読み込み
		u32 lVertexNum = aData.Read<u32>();
		aVertex.SetSize(lVertexNum);

		u32 lVertexSize = sizeof(StaticMeshVertex);

		aData.Read(&aVertex[0], lVertexSize * lVertexNum);
	}
	static void LoadVertex(VectorSimple<SkinMeshVertex>& aVertex, Buffer& aData) {

		//頂点フォーマットの確認
		u32 lVertexType = aData.Read<u32>();
		if (lVertexType != 1) return;

		//頂点データの読み込み
		u32 lVertexNum = aData.Read<u32>();
		aVertex.SetSize(lVertexNum);

		u32 lVertexSize = sizeof(SkinMeshVertex);
		SkinMeshVertex* lVertexData = (SkinMeshVertex*)(&(aData[aData.GetPosition()]));

		CopyMem(&aVertex[0], lVertexData, lVertexSize * lVertexNum);
	}
	static void LoadIndex(VectorSimple<u32>& aIndex, Buffer& aData) {

		//インデックスフォーマットの確認
		u32 lIndexType = aData.Read<u32>();

		//頂点データの読み込み
		u32 lIndexNum = aData.Read<u32>();
		aIndex.SetSize(lIndexNum);

		u32 lIndexSize = sizeof(u32);
		u32* lIndexData = (u32*)(&(aData[aData.GetPosition()]));

		aData.Read(&aIndex[0], lIndexSize * lIndexNum);
	}
	static void LoadSubMesh(VectorSimple<SubMeshCPU>& aSubMesh, Buffer& aData) {

		//頂点データの読み込み
		u32 lSubMeshNum = aData.Read<u32>();
		aSubMesh.SetSize(lSubMeshNum);

		//マテリアルデータの読み込み
		for (u32 i = 0; i < lSubMeshNum; i++) {

			//テクスチャ名の読み込み
			u32 lTextureNameLen = aData.Read<u32>();
			aData.Read(&(aSubMesh[i].material.texture.name), lTextureNameLen);

			u32 lToonTextureNameLen = aData.Read<u32>();
			aData.Read(&(aSubMesh[i].material.toonTexture.name), lToonTextureNameLen);


			//インデックスカウントの読み込み
			aSubMesh[i].indexCount = aData.Read<u32>();

			//色などの取得
			aSubMesh[i].material.diffuse = aData.Read<Color>();
			aSubMesh[i].material.ambient = aData.Read<Vector3>();
			aSubMesh[i].material.specular = aData.Read<Vector3>();
			aSubMesh[i].material.specularPower = aData.Read<f32>();
		}
	}


public:
	static void Save(const StaticMeshModelCPU& aMesh, Buffer& aData) {
		aData.Release();
		SaveVertex(aMesh.vertex, aData);
		SaveIndex(aMesh.index, aData);
		SaveSubMesh(aMesh.submesh, aData);
	}
	static void Save(const SkinMeshModelCPU& aMesh, Buffer& aData) {
		aData.Release();
		SaveVertex(aMesh.vertex, aData);
		SaveIndex(aMesh.index, aData);
		SaveSubMesh(aMesh.submesh, aData);
	}

private:
	static void SaveVertex(const VectorSimple<StaticMeshVertex>& aVertex, Buffer& aData) {

		//頂点フォーマットの書き込み
		u32 lVertexFormat = 0;
		aData.Add(&lVertexFormat);

		//インデックスデータの書き込み
		u32 lVertexNum = aVertex.GetSize();
		aData.Add(&lVertexNum);

		aData.Add((const BYTE*)(&aVertex[0]), lVertexNum * sizeof(StaticMeshVertex));
	}
	static void SaveVertex(const VectorSimple<SkinMeshVertex>& aVertex, Buffer& aData) {

		//頂点フォーマットの書き込み
		u32 lVertexFormat = 1;
		aData.Add(&lVertexFormat);

		//インデックスデータの書き込み
		u32 lVertexNum = aVertex.GetSize();
		aData.Add(&lVertexNum);

		aData.Add((const BYTE*)(&aVertex[0]), lVertexNum * sizeof(SkinMeshVertex));
	}
	static void SaveIndex(const VectorSimple<u32>& aIndex, Buffer& aData) {

		//インデックスフォーマットの書き込み
		u32 lIndexSize = 4;
		aData.Add(&lIndexSize);

		//インデックスデータの書き込み
		u32 lIndexNum = aIndex.GetSize();
		aData.Add(&lIndexNum);

		aData.Add((const BYTE*)(&aIndex[0]), lIndexNum * lIndexSize);

	}
	static void SaveSubMesh(const VectorSimple<SubMeshCPU>& aSubMesh, Buffer& aData) {

		//サブメッシュデータの書き込み
		u32 lSubMeshNum = aSubMesh.GetSize();
		aData.Add(&lSubMeshNum);

		for (u32 i = 0; i < lSubMeshNum; i++) {

			//テクスチャ名の書き込み
			u32 lTextureNameLen = aSubMesh[i].material.texture.name.GetLength() + 1;	//終端文字も書き込む
			aData.Add(&lTextureNameLen);

			aData.Add((const BYTE*)(aSubMesh[i].material.texture.name.Get()), lTextureNameLen);

	
			//トゥーンテクスチャ名の書き込み
			u32 lToonTextureNameLen = aSubMesh[i].material.toonTexture.name.GetLength() + 1;
			aData.Add(&lToonTextureNameLen);

			aData.Add((const BYTE*)(aSubMesh[i].material.toonTexture.name.Get()), lToonTextureNameLen);


			//インデックスカウントの書き込み
			aData.Add(&aSubMesh[i].indexCount);

			//色などの書き込み
			aData.Add(&aSubMesh[i].material.diffuse);
			aData.Add(&aSubMesh[i].material.ambient);
			aData.Add(&aSubMesh[i].material.specular);
			aData.Add(&aSubMesh[i].material.specularPower);
		}
	}

};


}
