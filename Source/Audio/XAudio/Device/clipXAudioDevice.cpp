//
//	content	:	XAudioにおけるデバイスでのClipの実装
//	author	:	SaitoYoshiki
//

#include "./Audio/XAudio/Device/clipXAudioDevice.h"
#include "./Audio/XAudio/Device/voiceXAudioDevice.h"


#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'soundData'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif



namespace cpot {

namespace xaudio {

namespace device {


void VoiceObservers::Release() {
	//オブザーバーにリリースを送ると、そのオブザーバがRemoveを呼んでしまうので、
	//リリースしているときにはRemoveを無効にする
	mReleasing = true;
	for (u32 i = 0; i < mObserver.GetSize(); i++) {
		mObserver[i]->Release();
	}
	mObserver.Clear();
	mReleasing = false;
}


HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition) {
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, nullptr, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, nullptr))
			hr = HRESULT_FROM_WIN32(GetLastError());
		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, nullptr))
			hr = HRESULT_FROM_WIN32(GetLastError());
		switch (dwChunkType)
		{
			case fourccRIFF:
				dwRIFFDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;
				if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, nullptr))
					hr = HRESULT_FROM_WIN32(GetLastError());
				break;
			default:
				if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, nullptr, FILE_CURRENT))
					return HRESULT_FROM_WIN32(GetLastError());
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT ReadChunkData(HANDLE hFile, void * mBuffer, DWORD mBuffersize, DWORD mBufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, mBufferoffset, nullptr, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, mBuffer, mBuffersize, &dwRead, nullptr))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}


void Clip::Load(const CHAR* aFileName) {
	if (IsLoaded()) {
		Release();
	}

	HANDLE               hFile;
	DWORD                dwChunkSize;
	DWORD                dwChunkPosition;
	DWORD                filetype;

	memset(&(mWfx), 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&(mBuffer), 0, sizeof(XAUDIO2_BUFFER));

	hFile = CreateFileA(aFileName, GENERIC_READ, FILE_SHARE_READ, nullptr,
		OPEN_EXISTING, 0, nullptr);
	if (hFile == INVALID_HANDLE_VALUE) {
		abort();
		return;	HRESULT_FROM_WIN32(GetLastError());
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
		abort();
		return;	HRESULT_FROM_WIN32(GetLastError());
	}

	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE)		return; S_FALSE;

	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &(mWfx), dwChunkSize, dwChunkPosition);

	//fill out the audio soundData mBuffer with the contents of the fourccDATA chunk
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	mDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, mDataBuffer, dwChunkSize, dwChunkPosition);

	CloseHandle(hFile);

	// 	サブミットボイスで利用するサブミットバッファの設定
	mBuffer.AudioBytes = dwChunkSize;
	mBuffer.pAudioData = mDataBuffer;
	mBuffer.Flags = XAUDIO2_END_OF_STREAM;
	if (mIsLoop) {
		mBuffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else {
		mBuffer.LoopCount = 0;
	}
}


}

}

}