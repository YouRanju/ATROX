#include <d3d9.h>
#include <d3dx9.h>

#include "WinApp.h"
#include "GameScene.h"

GameScene::GameScene(HWND hwnd, HINSTANCE hinstance, LPDIRECT3DDEVICE9 device)
{
	m_Input = new CInput(hwnd, hinstance);

	m_pPlayer = new Player(device);

	int speed = 10;
	for (int i = 0; i < 6; i++)
	{
		char path[6][100];
		sprintf_s(path[i], 100, "Resource/Stage1/stage1_%d.png", i + 1);
		m_BG1[i] = new Background(device, path[i], 2000, speed);

		speed += 200;
	}

	speed = 10;
	for (int i = 0; i < 6; i++)
	{
		char path[6][100];
		sprintf_s(path[i], 100, "Resource/Stage2/stage2_%d.png", i + 1);
		m_BG2[i] = new Background(device, path[i], 2000, speed);

		speed += 200;
	}

	speed = 10;
	for (int i = 0; i < 5; i++)
	{
		char path[6][100];
		sprintf_s(path[i], 100, "Resource/Stage3/stage3_%d.png", i + 1);
		m_BG3[i] = new Background(device, path[i], 2000, speed);

		speed += 200;
	}
}

GameScene::~GameScene()
{
	delete m_pPlayer;
	for (int i = 0; i < 6; i++) {
		delete m_BG1[i];
		delete m_BG2[i];
		delete m_BG3[i];
	}
}

void GameScene::Input()
{
	m_Input->ReadKey();

	m_pPlayer->pcDir.x = 0;

	m_pPlayer->ArrangePos(100, 1300);

	m_pPlayer->pcDir.x -= m_Input->IsKeyPress(DIK_LEFTARROW) * 2.2;
	m_pPlayer->pcDir.x += m_Input->IsKeyPress(DIK_RIGHTARROW);
}

void GameScene::Update(float eTime)
{
	m_pPlayer->Update(eTime);

	for (int i = 0; i < 6; i++) { m_BG1[i]->Update(eTime); }
}

void GameScene::Render()
{
	for (int i = 0; i < 6; i++) { m_BG1[i]->Render(); }

	m_pPlayer->Render();
}