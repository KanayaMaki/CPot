#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/render.h"

#include "./Pot/Model/SkinMeshModel.h"
#include "./Pot/Model/StaticMeshModel.h"
#include "./Pot/ModelLoader/SkinMeshModel.h"
#include "./Pot/ModelLoader/StaticMeshModel.h"

namespace cpot {


class ModelCPUToModel {

public:
	static void Load(StaticMeshModel& aMesh, const StaticMeshModelCPU& aMeshCPU, BOOL aVertexBufferWritable) {

		//���_�f�[�^�̓ǂݍ���
		aMesh.mesh.vertex.reset(new VertexBuffer);
		aMesh.mesh.vertex->Load(sizeof(StaticMeshVertex), aMeshCPU.vertex.GetSize(), &(aMeshCPU.vertex[0]), aVertexBufferWritable);

		//�C���f�b�N�X�f�[�^�̓ǂݍ���
		aMesh.mesh.index.reset(new IndexBuffer);
		aMesh.mesh.index->Load(IndexBuffer::cU32, aMeshCPU.index.GetSize(), IndexBuffer::cTriangleList, &(aMeshCPU.index[0]));

		CPOT_ASSERT(aMeshCPU.submesh.GetSize() <= 32);
		aMesh.submeshNum = aMeshCPU.submesh.GetSize();

		u32 indexStartCount = 0;

		//�}�e���A���f�[�^�̓ǂݍ���
		for (u32 i = 0; i < aMeshCPU.submesh.GetSize(); i++) {

			//�e�N�X�`���̓ǂݍ���
			aMesh.submesh[i].material.texture.reset(new Texture2D);
			aMesh.submesh[i].material.texture->LoadFileName(aMeshCPU.submesh[i].material.texture.name.Get());
			CPOT_LOG(aMeshCPU.submesh[i].material.texture.name.Get(), "�̓ǂݍ��݂�����");

			//�C���f�b�N�X�J�E���g�̓ǂݍ���
			aMesh.submesh[i].indexStartCount = indexStartCount;
			aMesh.submesh[i].indexCount = aMeshCPU.submesh[i].indexCount;
			indexStartCount += aMesh.submesh[i].indexCount;


			//�F�Ȃǂ̎擾
			aMesh.submesh[i].material.diffuse = aMeshCPU.submesh[i].material.diffuse;
			aMesh.submesh[i].material.ambient = aMeshCPU.submesh[i].material.ambient;
			aMesh.submesh[i].material.specular = aMeshCPU.submesh[i].material.specular;
			aMesh.submesh[i].material.specularPower = aMeshCPU.submesh[i].material.specularPower;
		}
	}
	static void Load(StaticMeshModel& aMesh, const StaticMeshModelCPU& aMeshCPU) {
		Load(aMesh, aMeshCPU, false);
	}

	static void Load(StaticMeshModel& aMesh, const VectorSimple<StaticMeshVertex>& aVertex, const VectorSimple<u32>& aIndex, const VectorSimple<SubMeshCPU>& aSubMesh, BOOL aVertexBufferWritable) {

		//���_�f�[�^�̓ǂݍ���
		aMesh.mesh.vertex.reset(new VertexBuffer);
		aMesh.mesh.vertex->Load(sizeof(StaticMeshVertex), aVertex.GetSize(), &(aVertex[0]), aVertexBufferWritable);

		//�C���f�b�N�X�f�[�^�̓ǂݍ���
		aMesh.mesh.index.reset(new IndexBuffer);
		aMesh.mesh.index->Load(IndexBuffer::cU32, aIndex.GetSize(), IndexBuffer::cTriangleList, &(aIndex[0]));

		CPOT_ASSERT(aSubMesh.GetSize() <= 32);
		aMesh.submeshNum = aSubMesh.GetSize();

		u32 indexStartCount = 0;

		//�}�e���A���f�[�^�̓ǂݍ���
		for (u32 i = 0; i < aSubMesh.GetSize(); i++) {

			//�e�N�X�`���̓ǂݍ���
			aMesh.submesh[i].material.texture.reset(new Texture2D);
			aMesh.submesh[i].material.texture->LoadFileName(aSubMesh[i].material.texture.name.Get());
			CPOT_LOG(aSubMesh[i].material.texture.name.Get(), "�̓ǂݍ��݂�����");

			//�C���f�b�N�X�J�E���g�̓ǂݍ���
			aMesh.submesh[i].indexStartCount = indexStartCount;
			aMesh.submesh[i].indexCount = aSubMesh[i].indexCount;
			indexStartCount += aMesh.submesh[i].indexCount;


			//�F�Ȃǂ̎擾
			aMesh.submesh[i].material.diffuse = aSubMesh[i].material.diffuse;
			aMesh.submesh[i].material.ambient = aSubMesh[i].material.ambient;
			aMesh.submesh[i].material.specular = aSubMesh[i].material.specular;
			aMesh.submesh[i].material.specularPower = aSubMesh[i].material.specularPower;
		}
	}
	static void Load(StaticMeshModel& aMesh, const VectorSimple<StaticMeshVertex>& aVertex, const VectorSimple<u32>& aIndex, const VectorSimple<SubMeshCPU>& aSubMesh) {
		Load(aMesh, aVertex, aIndex, aSubMesh, false);
	}

	static void Load(SkinMeshModel& aMesh, const SkinMeshModelCPU& aMeshCPU) {

		//���_�f�[�^�̓ǂݍ���
		aMesh.mesh.vertex.reset(new VertexBuffer);
		aMesh.mesh.vertex->Load(sizeof(SkinMeshVertex), aMeshCPU.vertex.GetSize(), &(aMeshCPU.vertex[0]));

		//�C���f�b�N�X�f�[�^�̓ǂݍ���
		aMesh.mesh.index.reset(new IndexBuffer);
		aMesh.mesh.index->Load(IndexBuffer::cU32, aMeshCPU.index.GetSize(), IndexBuffer::cTriangleList, &(aMeshCPU.index[0]));

		CPOT_ASSERT(aMeshCPU.submesh.GetSize() <= 32);
		aMesh.submeshNum = aMeshCPU.submesh.GetSize();

		u32 indexStartCount = 0;

		//�}�e���A���f�[�^�̓ǂݍ���
		for (u32 i = 0; i < aMeshCPU.submesh.GetSize(); i++) {

			//�e�N�X�`���̓ǂݍ���
			aMesh.submesh[i].material.texture.reset(new Texture2D);
			aMesh.submesh[i].material.texture->LoadFileName(aMeshCPU.submesh[i].material.texture.name.Get());

			//�C���f�b�N�X�J�E���g�̓ǂݍ���
			aMesh.submesh[i].indexStartCount = indexStartCount;
			aMesh.submesh[i].indexCount = aMeshCPU.submesh[i].indexCount;
			indexStartCount += aMesh.submesh[i].indexCount;

			//�F�Ȃǂ̎擾
			aMesh.submesh[i].material.diffuse = aMeshCPU.submesh[i].material.diffuse;
			aMesh.submesh[i].material.ambient = aMeshCPU.submesh[i].material.ambient;
			aMesh.submesh[i].material.specular = aMeshCPU.submesh[i].material.specular;
			aMesh.submesh[i].material.specularPower = aMeshCPU.submesh[i].material.specularPower;
		}
	}
};


}
