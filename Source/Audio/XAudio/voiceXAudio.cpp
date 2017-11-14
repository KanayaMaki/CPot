#include "./voice.h"
#include "./clip.h"

namespace cyc {

namespace pot {

namespace xaudio {


void Voice::Load(Clip* aAudioClip) {
	if (IsLoaded()) {
		Release();
	}
	Device::S().mXAudio2->CreateSourceVoice(&mSourceVoice, &(aAudioClip->mWfx.Format));
	mSourceVoice->SubmitSourceBuffer(&(aAudioClip->mBuffer));	// �{�C�X�L���[�ɐV�����I�[�f�B�I�o�b�t�@�[��ǉ�
}
void Voice::Release() {
	if (IsLoaded()) {

		Stop();	//�{�C�X���~�߂�

				//�{�C�X���폜����
		mSourceVoice->FlushSourceBuffers();
		mSourceVoice->DestroyVoice();			// �I�[�f�B�I�O���t����\�[�X�{�C�X���폜

		Init();
	}
}


}

}

}