#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

class CInput
{
protected:
	LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pKeyboard;
	unsigned char m_KeyboardState[256];

public:
	explicit CInput(HWND hWnd, HINSTANCE hInstance);
	virtual ~CInput();

	void InitInput(HWND hWnd, HINSTANCE hInstance);
	void ShutDown();
	bool ReadKey();

	bool IsActionKey(int key, int time);

	float IsKeyPress(int key) {
		return (m_KeyboardState[key] & 0x80) ? 1.0f : 0.0f;
	}

	void ClearKeyBuffer() {
		ZeroMemory(m_KeyboardState, sizeof(m_KeyboardState));
	}


};

