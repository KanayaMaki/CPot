//
//	content	:	XAudio�ɂ�����f�o�C�X�ł�Voice�̎���
//	author	:	SaitoYoshiki
//


#include "./Audio/XAudio/Device/clipXAudioDevice.h"
#include "./Audio/XAudio/Device/voiceXAudioDevice.h"

namespace cpot {

namespace xaudio {

namespace device {


void Voice::Load(Clip& aAudioClip) {
	if (IsLoaded()) {
		Release();
	}
	Device::S().mXAudio2->CreateSourceVoice(&mSourceVoice, &(aAudioClip.mWfx.Format));
	mSourceVoice->SubmitSourceBuffer(&(aAudioClip.mBuffer));	// �{�C�X�L���[�ɐV�����I�[�f�B�I�o�b�t�@�[��ǉ�

	mClip = &aAudioClip;

	mClip->mVoices.Add(this);
}
void Voice::Release() {
	if (IsLoaded()) {

		Stop();	//�{�C�X���~�߂�

		//�{�C�X���폜����
		mSourceVoice->FlushSourceBuffers();
		mSourceVoice->DestroyVoice();			// �I�[�f�B�I�O���t����\�[�X�{�C�X���폜

		Init();
	}

	mClip->mVoices.Remove(this);
}


}

}

}