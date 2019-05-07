#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "windows.h"
#include "atlstr.h"

#include "CTexture.h"
#include "CText.h"
#include "CInput.h"

#include "GameScene.h"

class WinApp
{
protected:
	HWND hWnd;
	HINSTANCE hInst;
	CString Title;

	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DPRESENT_PARAMETERS m_d3dpp;
	D3DCOLOR m_ClearColor;

	DWORD m_dwPrevTime;

	CText* m_Font;
	CInput* m_Input;
	GameScene* m_GameScene;

public:
	static const int WIDTH = 800;
	static const int HEIGHT = 600;

public:
	WinApp();
	~WinApp();

	void				Initialize(HINSTANCE, int, CString);
	int					Loop();
	void				Destroy();
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int, HWND&);
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

	bool				InitD3D(HWND, HINSTANCE);

	float				GetTime();
};