#pragma once

#include <windows.h>
#include <mmsystem.h>

#include <d3d9.h>
#include <dsound.h>
#include <tchar.h>

#define SOUNDBUFFER_SIZE        50

class CSound
{
private:
	HWND                    m_hWnd;
	LPDIRECTSOUND           m_pSound;
	LPDIRECTSOUNDBUFFER     m_pSoundBuffers[SOUNDBUFFER_SIZE];
	int m_SoundBufferIndex;

public:
	CSound(HWND hWnd = NULL);
	virtual ~CSound(void);

	void                SetHwnd(HWND hWnd) { this->m_hWnd = hWnd; }
	HWND                GetHwnd() { return m_hWnd; }
	int                 GetBufferSize() { return m_SoundBufferIndex; }

	void                DirectSoundInit();
	void                SoundError(TCHAR *errorString);

	LPDIRECTSOUNDBUFFER LoadWav(TCHAR* wav);

	void                Play(int index, BOOL Loop = FALSE);
	void                Stop(int index);
	void                AllStop();

	BOOL                IsPlaying(int index);

	BOOL                IsBufIndex(int index);
	int                 AddSoundBuffer(LPDIRECTSOUNDBUFFER buffer);
	void                DeleteSoundBuffer(int iDel_index);
};

