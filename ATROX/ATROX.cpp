#include <iostream>
#include <Windows.h>

#include "WinApp.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dsound.lib")

using namespace std;

WinApp* app = new WinApp();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	app->Initialize(hInstance, nCmdShow, "ATROX");
	app->Loop();
	app->Destroy();

	return 0;
}