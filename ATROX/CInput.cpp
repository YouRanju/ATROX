#include <tchar.h>
#include "CInput.h"

CInput::CInput(HWND hWnd, HINSTANCE hInstance)
{
	m_pInput = NULL;
	m_pKeyboard = NULL;

	InitInput(hWnd, hInstance);
}


CInput::~CInput()
{
	ShutDown();
}

void CInput::InitInput(HWND hWnd, HINSTANCE hInstance)
{
	try
	{
		auto hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_pInput, NULL);
		if (FAILED(hr)) throw 0L;

		hr = m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, 0);
		if (FAILED(hr)) throw 1L;

		hr = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr)) throw 0L;

		hr = m_pKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(hr)) throw 0L;

		hr = m_pKeyboard->Acquire();
		if (FAILED(hr)) throw 0L;
	}
	catch (DWORD dwErr)
	{
		LPTSTR errMsg = 0;

		switch (dwErr)
		{
		case 0L:
			errMsg = (LPTSTR)_T("디바이스 생성 실패");
			break;
		case 1L:
			errMsg = (LPTSTR)_T("키보드 생성 실패");
			break;
		}

		MessageBox(hWnd, errMsg, _T("Error"), MB_OK);
	}
}

void CInput::ShutDown()
{
	if (m_pKeyboard != NULL) {
		m_pKeyboard->Unacquire();
		m_pKeyboard->Release();
		m_pKeyboard = NULL;
	}

	if (m_pInput != NULL) {
		m_pInput->Release();
		m_pInput = NULL;
	}
}

bool CInput::ReadKey()
{
	auto hr = m_pKeyboard->GetDeviceState(sizeof(m_KeyboardState), (LPVOID)&m_KeyboardState);
	if (FAILED(hr)) {
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) {
			m_pKeyboard->Acquire();
		}
		else {
			return false;
		}
	}

	return true;
}

bool CInput::IsActionKey(int key, int time)
{
	static DWORD dwPrevTime = 0;
	DWORD dwCurTime = GetTickCount();
	int dt = dwCurTime - dwPrevTime;

	if ((dt > time) && (m_KeyboardState[key] & 0x80)) {
		m_KeyboardState[key] = 0;
		dwPrevTime = dwCurTime;

		return true;
	}
	else
		return false;
}
