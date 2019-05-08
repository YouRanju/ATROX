#include "WinApp.h"                           

WinApp::WinApp()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_ClearColor = D3DCOLOR_XRGB(0, 0, 0);

	m_dwPrevTime = 0;
}

WinApp:: ~WinApp()
{
	Destroy();
}

void WinApp::Initialize(HINSTANCE hInstance, int nCmdShow, CString str)
{
	hInst = hInstance;
	Title = str;

	MyRegisterClass(hInstance);
	InitInstance(hInstance, nCmdShow, hWnd);
	InitD3D(hWnd, hInstance);

	m_Font = new CText(m_pD3DDevice, 24, 30);
	m_Input = new CInput(hWnd, hInstance);
	m_GameScene = new GameScene(hWnd, hInstance, m_pD3DDevice);

	GetTime();
}

int WinApp::Loop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (FAILED(m_pD3DDevice->TestCooperativeLevel()))
				m_pD3DDevice->Reset(&m_d3dpp);

			m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, m_ClearColor, 1.0f, 0);

			float dt = GetTime();
			//업데이트

			m_Input->ReadKey();

			if (m_Input->IsActionKey(DIK_ESCAPE)) {
				msg.message = WM_QUIT;
			}

			m_GameScene->Update(dt);
			m_GameScene->Input();

			if (SUCCEEDED(m_pD3DDevice->BeginScene())) {
				//렌더

				m_Font->Draw((int)WIDTH / 2 - 70, (int)HEIGHT / 2 - 10, (int)WIDTH, (int)HEIGHT,
					_T("Ready"), D3DCOLOR_XRGB(255, 255, 0));

				m_GameScene->Render();

				m_pD3DDevice->EndScene();
			}

			m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
		}
	}

	return (int)msg.wParam;
}

void WinApp::Destroy()
{
	delete m_Font;
	delete m_Input;
	delete m_GameScene;

	if (m_pD3DDevice != NULL) m_pD3DDevice->Release();
	if (m_pD3D != NULL) m_pD3D->Release();

	m_pD3DDevice = NULL;
	m_pD3D = NULL;
}

ATOM WinApp::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = Title;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	return RegisterClassExW(&wcex);
}

BOOL WinApp::InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& rhWnd)
{
	hInst = hInstance;

	HWND hWnd;
	if (true) {
		hWnd = CreateWindowW(Title, Title, WS_OVERLAPPEDWINDOW,
			0, 0, WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);
	}
	else {
		hWnd = CreateWindowW(Title, Title, WS_EX_TOPMOST | WS_POPUP,
			0, 0, WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);
	}

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	rhWnd = hWnd;

	return TRUE;
}

LRESULT CALLBACK WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);

}

bool WinApp::InitD3D(HWND hWnd, HINSTANCE hInstance)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL) return false;

	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));

	m_d3dpp.Windowed = TRUE;
	m_d3dpp.hDeviceWindow = hWnd;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.BackBufferWidth = 2000;
	m_d3dpp.BackBufferHeight = 1000;

	if (m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_pD3DDevice)
		== E_FAIL)
		return false;

	return true;
}

float WinApp::GetTime()
{
	DWORD dwCurtime = GetTickCount();
	DWORD dwDt = dwCurtime - m_dwPrevTime;
	float fDt = (float)(dwDt) * 0.001f;
	m_dwPrevTime = dwCurtime;

	return fDt;
}