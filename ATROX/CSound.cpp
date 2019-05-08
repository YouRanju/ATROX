#include "CSound.h"

CSound::CSound(HWND hWnd)
	: m_SoundBufferIndex(0)
{
	m_hWnd = hWnd;
	ZeroMemory(m_pSoundBuffers, sizeof(m_pSoundBuffers));
}

CSound::~CSound(void)
{
	AllStop();
	for (int i = 0; i < SOUNDBUFFER_SIZE; i++)
	{
		if (m_pSoundBuffers[i] != NULL)
		{
			m_pSoundBuffers[i]->Release();
			m_pSoundBuffers[i] = NULL;
		}
	}
}

void CSound::DirectSoundInit()
{
	try {
		auto hr = DirectSoundCreate(NULL, &m_pSound, NULL);
		if (hr != DS_OK) throw 0L;

		hr = m_pSound->SetCooperativeLevel(m_hWnd, DSSCL_PRIORITY);
		if (hr != DS_OK) throw 1L;
	}
	catch (DWORD dwErr) {
		LPTSTR errMsg = 0;

		switch (dwErr)
		{
		case 0L:
			errMsg = (LPTSTR)_T("객체 생성 실패");
			break;
		case 1L:
			errMsg = (LPTSTR)_T("모드 설정 실패");
			break;
		}

		SoundError(errMsg);
	}
}

void CSound::SoundError(TCHAR *errorString)
{
	MessageBox(m_hWnd, errorString, _T("Error"), MB_OK);
}

int  CSound::AddSoundBuffer(LPDIRECTSOUNDBUFFER buffer)
{
	if (m_SoundBufferIndex < SOUNDBUFFER_SIZE - 1)
	{
		m_pSoundBuffers[m_SoundBufferIndex] = buffer;
	}
	return m_SoundBufferIndex++;
}

void CSound::DeleteSoundBuffer(int iDel_index)
{
	if (m_pSoundBuffers[iDel_index] == NULL)  return;

	m_pSoundBuffers[iDel_index]->Release();
	m_SoundBufferIndex--;

	for (int i = iDel_index; i < m_SoundBufferIndex; i++)
	{
		m_pSoundBuffers[i] = m_pSoundBuffers[i + 1];
	}
	m_pSoundBuffers[m_SoundBufferIndex] = NULL;
}

BOOL CSound::IsBufIndex(int index)
{
	if (m_pSoundBuffers[index] == NULL)
		return FALSE;
	return TRUE;
}

LPDIRECTSOUNDBUFFER CSound::LoadWav(TCHAR * wav)
{
	HMMIO hmmioIn = mmioOpen(wav, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (!hmmioIn) SoundError((TCHAR*)_T("파일을 읽을 수 없음"));

	//
	MMCKINFO ckInfoRIFF, ckInfoFMT;
	ckInfoRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (mmioDescend(hmmioIn, &ckInfoRIFF, NULL, MMIO_FINDRIFF) != 0)
		SoundError((TCHAR*)_T("RIFF WAVE 파일이 아님"));

	//
	ckInfoFMT.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(hmmioIn, &ckInfoFMT, &ckInfoRIFF, MMIO_FINDCHUNK) != 0)
		SoundError((TCHAR*)_T("fmt Chunk 아님"));

	//
	PCMWAVEFORMAT pcmWaveFMT;
	auto result = mmioRead(hmmioIn, (HPSTR)&pcmWaveFMT, (long) sizeof(pcmWaveFMT));
	if (result != (long) sizeof(pcmWaveFMT))
		SoundError((TCHAR*)_T("파일 읽기 실패"));

	WORD wExtraAlloc;
	if (pcmWaveFMT.wf.wFormatTag == WAVE_FORMAT_PCM)
		wExtraAlloc = 0;
	else {
		result = mmioRead(hmmioIn, (LPSTR)&wExtraAlloc, (long) sizeof(wExtraAlloc));
		if (result != (long) sizeof(wExtraAlloc))
			SoundError((TCHAR*)_T("파일 읽기 실패"));
	}

	LPWAVEFORMATEX pWaveFMT = (LPWAVEFORMATEX)malloc(sizeof(WAVEFORMATEX) + wExtraAlloc);
	memcpy(pWaveFMT, &pcmWaveFMT, sizeof(pcmWaveFMT));
	pWaveFMT->cbSize = wExtraAlloc;
	if (wExtraAlloc != 0) {
		result = mmioRead(hmmioIn,
			(LPSTR)(((BYTE*)&(pWaveFMT->cbSize)) + sizeof(wExtraAlloc)),
			(long)(wExtraAlloc));
		if (result != (long) sizeof(wExtraAlloc))
			SoundError((TCHAR*)_T("파일 읽기 실패"));
	}

	//
	if (mmioAscend(hmmioIn, &ckInfoFMT, 0) != MMSYSERR_NOERROR ||
		mmioSeek(hmmioIn, ckInfoRIFF.dwDataOffset + sizeof(FOURCC), SEEK_SET) == -1)
		SoundError((TCHAR*)_T("오류"));

	//
	MMCKINFO ckData;
	ckData.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hmmioIn, &ckData, &ckInfoRIFF, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
		SoundError((TCHAR*)_T("Data Chunk가아닙니다"));
	DWORD dwDataSize = ckData.cksize;

	//
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));

	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;
	dsbd.dwBufferBytes = dwDataSize;

	DWORD dwWavSize = pWaveFMT->cbSize + sizeof(WAVEFORMATEX);

	dsbd.lpwfxFormat = (LPWAVEFORMATEX)malloc(dwWavSize);
	memcpy(dsbd.lpwfxFormat, pWaveFMT, dwWavSize);
	free(pWaveFMT);

	LPDIRECTSOUNDBUFFER lpDSTemp;
	if (m_pSound->CreateSoundBuffer(&dsbd, &lpDSTemp, NULL) != DS_OK)
		SoundError((TCHAR*)_T("사운드버퍼생성실패"));
	free(dsbd.lpwfxFormat);

	//
	DWORD dwBSize, dwWrapBSize;
	LPVOID pWrapPtr;
	LPBYTE pData = NULL;
	result = lpDSTemp->Lock(0, dwDataSize, (void**)&pData, &dwBSize,
		&pWrapPtr, &dwWrapBSize, 0L);
	if (result != DS_OK) SoundError((TCHAR*)_T("오류"));
	dwDataSize = dwBSize;

	//
	UINT DataInSize = dwDataSize;
	if (DataInSize > ckData.cksize) DataInSize = ckData.cksize;
	ckData.cksize -= DataInSize;

	MMIOINFO mmioinfoIn;
	if (mmioGetInfo(hmmioIn, &mmioinfoIn, 0) != MMSYSERR_NOERROR)
		SoundError((TCHAR*)_T("오류"));

	for (int i = 0; i < DataInSize; i++)
	{
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			result = mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ);
			if (result != MMSYSERR_NOERROR) SoundError((TCHAR*)_T("오류"));
		}
		*((BYTE*)pData + i) = *((BYTE*)mmioinfoIn.pchNext++);
	}
	if (mmioSetInfo(hmmioIn, &mmioinfoIn, 0) != MMSYSERR_NOERROR)
		SoundError((TCHAR*)_T("오류"));

	lpDSTemp->Unlock(pData, dwBSize, pWrapPtr, dwWrapBSize);

	return lpDSTemp;
}

void CSound::Play(int index, BOOL Loop)
{
	if (IsBufIndex(index)) {
		if (IsPlaying(index)) Stop(index);

		m_pSoundBuffers[index]->SetCurrentPosition(0);
		m_pSoundBuffers[index]->Play(0, 0, (Loop == TRUE) ? 1 : 0);
	}
}

void CSound::Stop(int index)
{
	m_pSoundBuffers[index]->Stop();
}

void CSound::AllStop()
{
	for (int i = 0; i < GetBufferSize(); i++)
	{
		m_pSoundBuffers[i]->Stop();
	}
}

BOOL CSound::IsPlaying(int index)
{
	DWORD   dwPlayCursol;
	DWORD   dwWriteCursol;

	m_pSoundBuffers[index]->GetCurrentPosition(&dwPlayCursol, &dwWriteCursol);

	if (dwPlayCursol != 0) return TRUE;

	return FALSE;
}
