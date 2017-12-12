//
//	content	:	�R���|�[�l���g
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/component.h"

namespace cpot {

class Renderer : public Component {
	CPOT_TYPE(Renderer, Component)

public:
	Renderer();
	~Renderer() override;


	//�Ăяo�����֐�
	#pragma region Event
public:
	//�`�揈��
	virtual void OnRender() {}

	#pragma endregion


	//�D��x
	#pragma region Priority
public:
	virtual u32 GetPriority() {
		return 0;
	}

	#pragma endregion

};

class RendererManager : public Singleton<RendererManager> {

	friend class Renderer;

	//�o�^&�����BUpdater���Ăяo��
	#pragma region Regist&Remove

private:
	void Regist(Renderer* aRenderer) {
		mRendererNowFrame.PushBack(aRenderer);
	}
	void Remove(Renderer* aRenderer) {
		mRendererNowFrame.Remove(aRenderer);
		mRenderer.Remove(aRenderer);
	}
	void Clear() {
		mRenderer.Clear();
		mRendererNowFrame.Clear();
	}

	#pragma endregion


	void Update() {
		Merge();	//�O�̃t���[���ɒǉ����ꂽ�����_���𓝍�����
		Sort();	//�D��x���ɕ��ёւ���
		RenderRenderer();	//�����_����`�悷��
	}

private:
	void Merge() {
		//����
		while(mRendererNowFrame.GetSize() != 0) {
			mRenderer.PushBack(mRendererNowFrame.PopBack());
		}
	}

	void Sort() {
		//mRenderer.Sort();
	}

	void RenderRenderer() {
		for (u32 i = 0; i < mRenderer.GetSize(); i++) {
			mRenderer[i]->OnRender();
		}
	}


private:
	Vector<Renderer*> mRendererNowFrame;	//�V�����ǉ����ꂽ�A�b�v�f�[�^�[
	Vector<Renderer*> mRenderer;
};


}