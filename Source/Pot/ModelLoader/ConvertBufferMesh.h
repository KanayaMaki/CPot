#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/Usefull/buffer.h"

#include "./Pot/ModelLoader/ModelCPU.h"

#include "./Pot/Usefull/path.h"


namespace cpot {

class BufferToMesh {

public:
	template<typename VertexType, typename MaterialType>
	static void Load(ModelCPU<VertexType, MaterialType>& aMesh, Buffer& aData, PathString& aFilePath) {
		LoadVertex(aMesh.vertex, aData);
		LoadIndex(aMesh.index, aData);
		LoadSubMesh(aMesh.submesh, aData);
		aMesh.filePath = aFilePath;
	}

	template<typename VertexType, typename MaterialType>
	static void Load(ModelCPU<VertexType, MaterialType>& aMesh, PathString& aFilePath) {
		FileIn lFile;
		lFile.Open(aFilePath.Get(), true);

		Buffer lData;
		lFile.Read(lData);

		Load(aMesh, lData, aFilePath);
	}


private:
	template <typename VertexType>
	static void LoadVertex(VectorSimple<VertexType>& aVertex, Buffer& aData) {

		//���_�t�H�[�}�b�g�̊m�F
		u32 lVertexType = aData.Read<u32>();
		if (lVertexType != VertexType::cVertexType) return;

		//���_�f�[�^�̓ǂݍ���
		u32 lVertexNum = aData.Read<u32>();
		aVertex.SetSize(lVertexNum);

		u32 lVertexSize = sizeof(VertexType);

		aData.Read(&aVertex[0], lVertexSize * lVertexNum);
	}

	static void LoadIndex(VectorSimple<u32>& aIndex, Buffer& aData) {

		//�C���f�b�N�X�t�H�[�}�b�g�̊m�F
		u32 lIndexType = aData.Read<u32>();

		//���_�f�[�^�̓ǂݍ���
		u32 lIndexNum = aData.Read<u32>();
		aIndex.SetSize(lIndexNum);

		u32 lIndexSize = sizeof(u32);
		u32* lIndexData = (u32*)(&(aData[aData.GetPosition()]));

		aData.Read(&aIndex[0], lIndexSize * lIndexNum);
	}


	static void LoadMaterial(MaterialCPU& aMaterial, Buffer& aData) {

		//�e�N�X�`�����̓ǂݍ���
		u32 lTextureNameLen = aData.Read<u32>();
		aData.Read(&(aMaterial.texture.name), lTextureNameLen);

		u32 lToonTextureNameLen = aData.Read<u32>();
		aData.Read(&(aMaterial.toonTexture.name), lToonTextureNameLen);


		//�F�Ȃǂ̎擾
		aMaterial.diffuse = aData.Read<Color>();
		aMaterial.ambient = aData.Read<Vector3>();
		aMaterial.specular = aData.Read<Vector3>();
		aMaterial.specularPower = aData.Read<f32>();
	}
	static void LoadMaterial(BampMaterialCPU& aMaterial, Buffer& aData) {

		//�e�N�X�`�����̓ǂݍ���
		u32 lTextureNameLen = aData.Read<u32>();
		aData.Read(&(aMaterial.texture.name), lTextureNameLen);

		u32 lBampTextureNameLen = aData.Read<u32>();
		aData.Read(&(aMaterial.bampTexture.name), lBampTextureNameLen);


		//�F�Ȃǂ̎擾
		aMaterial.diffuse = aData.Read<Color>();
		aMaterial.ambient = aData.Read<Vector3>();
		aMaterial.specular = aData.Read<Vector3>();
		aMaterial.specularPower = aData.Read<f32>();
	}

	template <typename MaterialType>
	static void LoadSubMesh(VectorSimple<SubMeshCPU<MaterialType>>& aSubMesh, Buffer& aData) {

		//���_�f�[�^�̓ǂݍ���
		u32 lSubMeshNum = aData.Read<u32>();
		aSubMesh.SetSize(lSubMeshNum);

		//�}�e���A���f�[�^�̓ǂݍ���
		for (u32 i = 0; i < lSubMeshNum; i++) {

			//�C���f�b�N�X�J�E���g�̓ǂݍ���
			aSubMesh[i].indexCount = aData.Read<u32>();
			
			//�}�e���A���̓ǂݍ���
			LoadMaterial(aSubMesh[i].material, aData);
		}
	}


public:
	template<typename VertexType, typename MaterialType>
	static void Save(const ModelCPU<VertexType, MaterialType>& aMesh, Buffer& aData) {
		aData.Release();
		SaveVertex(aMesh.vertex, aData);
		SaveIndex(aMesh.index, aData);
		SaveSubMesh(aMesh.submesh, aData);
	}
	
private:
	template <typename VertexType>
	static void SaveVertex(const VectorSimple<VertexType>& aVertex, Buffer& aData) {

		//���_�t�H�[�}�b�g�̏�������
		u32 lVertexFormat = VertexType::cVertexType;
		aData.Add(&lVertexFormat);

		//�C���f�b�N�X�f�[�^�̏�������
		u32 lVertexNum = aVertex.GetSize();
		aData.Add(&lVertexNum);

		aData.Add((const BYTE*)(&aVertex[0]), lVertexNum * sizeof(VertexType));
	}

	static void SaveIndex(const VectorSimple<u32>& aIndex, Buffer& aData) {

		//�C���f�b�N�X�t�H�[�}�b�g�̏�������
		u32 lIndexSize = 4;
		aData.Add(&lIndexSize);

		//�C���f�b�N�X�f�[�^�̏�������
		u32 lIndexNum = aIndex.GetSize();
		aData.Add(&lIndexNum);

		aData.Add((const BYTE*)(&aIndex[0]), lIndexNum * lIndexSize);

	}

	static void SaveMaterial(const MaterialCPU& aMaterial, Buffer& aData) {

		//�e�N�X�`�����̏�������
		u32 lTextureNameLen = aMaterial.texture.name.GetLength() + 1;	//�I�[��������������
		aData.Add(&lTextureNameLen);

		aData.Add((const BYTE*)(aMaterial.texture.name.Get()), lTextureNameLen);


		//�g�D�[���e�N�X�`�����̏�������
		u32 lToonTextureNameLen = aMaterial.toonTexture.name.GetLength() + 1;
		aData.Add(&lToonTextureNameLen);

		aData.Add((const BYTE*)(aMaterial.toonTexture.name.Get()), lToonTextureNameLen);


		//�F�Ȃǂ̏�������
		aData.Add(&aMaterial.diffuse);
		aData.Add(&aMaterial.ambient);
		aData.Add(&aMaterial.specular);
		aData.Add(&aMaterial.specularPower);
	}
	static void SaveMaterial(const BampMaterialCPU& aMaterial, Buffer& aData) {

		//�e�N�X�`�����̏�������
		u32 lTextureNameLen = aMaterial.texture.name.GetLength() + 1;	//�I�[��������������
		aData.Add(&lTextureNameLen);

		aData.Add((const BYTE*)(aMaterial.texture.name.Get()), lTextureNameLen);


		//�m�[�}���e�N�X�`�����̏�������
		u32 lNormalTextureNameLen = aMaterial.bampTexture.name.GetLength() + 1;
		aData.Add(&lNormalTextureNameLen);

		aData.Add((const BYTE*)(aMaterial.bampTexture.name.Get()), lNormalTextureNameLen);


		//�F�Ȃǂ̏�������
		aData.Add(&aMaterial.diffuse);
		aData.Add(&aMaterial.ambient);
		aData.Add(&aMaterial.specular);
		aData.Add(&aMaterial.specularPower);
	}

	template <typename MaterialType>
	static void SaveSubMesh(const VectorSimple<SubMeshCPU<MaterialType>>& aSubMesh, Buffer& aData) {

		//�T�u���b�V���f�[�^�̏�������
		u32 lSubMeshNum = aSubMesh.GetSize();
		aData.Add(&lSubMeshNum);

		for (u32 i = 0; i < lSubMeshNum; i++) {

			//�C���f�b�N�X�J�E���g�̏�������
			aData.Add(&aSubMesh[i].indexCount);

			//�}�e���A���̏�������
			SaveMaterial(aSubMesh[i].material, aData);
		}
	}

};


}
