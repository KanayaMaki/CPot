//
//	content	:	���f����`�悷�郌���_���[
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/renderer.h"
#include "./Pot/Game/cameraComponent.h"
#include "./Pot/Game/lightComponent.h"
#include "./Pot/Render/constantBuffer.h"
#include "./Pot/ModelLoader/ModelCPU.h"

namespace cpot {

class StaticTangentModelRenderer : public Renderer {
	CPOT_TYPE(StaticTangentModelRenderer, Renderer)

	//�Ăяo�����֐�
	#pragma region Event
public:
	//�`�揈��
	virtual void OnStart() {
		if (blend == nullptr) {
			blend = ResourceList<Blend>::S().Find("Normal");
		}
		if (rasterizer == nullptr) {
			rasterizer = ResourceList<Rasterizer>::S().Find("CullCCW");
		}
		if (depthStencil == nullptr) {
			depthStencil = ResourceList<DepthStencil>::S().Find("Test");
		}
		if (renderTarget == nullptr) {
			renderTarget = ResourceList<Texture2D>::S().Find("RenderTarget");
		}
		if (renderTargetDepth == nullptr) {
			renderTargetDepth = ResourceList<Texture2D>::S().Find("RenderTargetDepth");
		}

		if (sampler == nullptr) {
			sampler = ResourceList<Sampler>::S().Find("Diffuse");
		}
		if (bampSampler == nullptr) {
			bampSampler = ResourceList<Sampler>::S().Find("Diffuse");
		}
		if (shader == nullptr) {
			shader = ResourceList<Shader>::S().Find("Bamp");
		}
		
	}

	//�`�揈��
	virtual void OnRender() {

		//���f�����ݒ肳��Ă��Ȃ���
		if (model == nullptr) return;

		//���O�Ɏ擾���Ă���
		std::shared_ptr<ConstantBuffer> wvpBuffer = ResourceList<ConstantBuffer>::S().Find("WVP");
		std::shared_ptr<ConstantBuffer> materialBuffer = ResourceList<ConstantBuffer>::S().Find("Material");
		std::shared_ptr<ConstantBuffer> otherBuffer = ResourceList<ConstantBuffer>::S().Find("Other");
		std::shared_ptr<ConstantBuffer> toonLineBuffer = ResourceList<ConstantBuffer>::S().Find("ToonLine");


		//�J�����s��̐ݒ�
		auto lCamera = CameraManager::S().GetCamera();
		if (lCamera) {
			wvpBuffer->GetCPUBuffer<WVPBuffer>()->mProjection = lCamera->GetProjectionMatrix();
			wvpBuffer->GetCPUBuffer<WVPBuffer>()->mView = lCamera->GetViewMatrix();
			otherBuffer->GetCPUBuffer<OtherBuffer>()->mCameraPosition = lCamera->GetLocation();
		}

		//���C�g�s��̐ݒ�
		auto lLight = LightManager::S().GetDirectionalLight();
		if (lLight) {
			otherBuffer->GetCPUBuffer<OtherBuffer>()->mLightDirection = lLight->GetDirection().Normal();
		}
		otherBuffer->Write();
		
		//���[���h�s��̐ݒ�
		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mWorld = Matrix4x4(GetTransform().mRotation, GetTransform().mPosition);
		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mNormalWorld = Matrix4x4(GetTransform().mRotation);
		wvpBuffer->Write();

		//�}�e���A���̐ݒ�
		materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::White();
		materialBuffer->Write();


		Render::S().SetBlend(blend);
		Render::S().SetRasterizer(rasterizer);
		Render::S().SetDepthStencil(depthStencil);
		Render::S().SetVertexBuffer(model->mesh.vertex);
		Render::S().SetIndexBuffer(model->mesh.index);
		Render::S().SetRenderTexture(renderTarget, 0);
		Render::S().SetDepthTexture(renderTargetDepth);
		Render::S().SetSampler(sampler, 0);
		Render::S().SetSampler(bampSampler, 1);
		Render::S().SetConstantBuffer(wvpBuffer, 0);
		Render::S().SetConstantBuffer(materialBuffer, 1);
		Render::S().SetConstantBuffer(otherBuffer, 2);
		Render::S().SetShader(shader);

		//�}�e���A�����Ƃɕ`��
		for (u32 i = 0; i < model->submeshNum; i++) {
			Render::S().SetTexture2D(model->submesh[i].material.texture, 0);
			if (model->submesh[i].material.bampTexture->IsLoad()) {
				Render::S().SetTexture2D(model->submesh[i].material.bampTexture, 1);
			}
			else {
				Render::S().SetTexture2D(ResourceList<Texture2D>::S().Find("White"), 1);
			}
			Render::S().SetToDevice();
			Render::S().DrawIndexed(model->submesh[i].indexCount, model->submesh[i].indexStartCount);
		}
	}

	#pragma endregion


	//�D��x
	#pragma region Priority
public:
	virtual s32 GetPriority() {
		return 0;
	}

	#pragma endregion


public:
	std::shared_ptr<StaticTangentMeshModel> model;
	std::shared_ptr<Blend> blend;
	std::shared_ptr<Rasterizer> rasterizer;
	std::shared_ptr<DepthStencil> depthStencil;
	std::shared_ptr<Texture2D> renderTarget;
	std::shared_ptr<Texture2D> renderTargetDepth;
	std::shared_ptr<Sampler> sampler;
	std::shared_ptr<Sampler> bampSampler;
	std::shared_ptr<Shader> shader;
};

}