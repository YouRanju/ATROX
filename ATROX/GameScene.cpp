#include <d3d9.h>
#include <d3dx9.h>

#include "WinApp.h"
#include "GameScene.h"

bool anyKeyinput;
GameScene::GameScene(HWND hwnd, HINSTANCE hinstance, LPDIRECT3DDEVICE9 device)
{
	anyKeyinput = false;
	m_Input = new CInput(hwnd, hinstance);

	m_pPlayer = new Player(device);
	m_Enemy = new Enemy(device, "alien1_1");

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

	m_Sound = new CSound(hwnd);
	m_Sound->DirectSoundInit();
	m_Sound->AddSoundBuffer(m_Sound->LoadWav((TCHAR*)_T("Resource/music/Background.wav")));
	m_Sound->AddSoundBuffer(m_Sound->LoadWav((TCHAR*)_T("Resource/music/BackgroundAdd.wav")));
	m_Sound->AddSoundBuffer(m_Sound->LoadWav((TCHAR*)_T("Resource/music/SE/playerJump.wav")));
	m_Sound->AddSoundBuffer(m_Sound->LoadWav((TCHAR*)_T("Resource/music/SE/playerJump.wav")));
	m_Sound->AddSoundBuffer(m_Sound->LoadWav((TCHAR*)_T("Resource/music/SE/playerJump.wav")));
	m_Sound->AddSoundBuffer(m_Sound->LoadWav((TCHAR*)_T("Resource/music/SE/player2ndJump.wav")));
	m_Sound->Play(0, TRUE);
	m_Sound->Play(1, TRUE);
}

GameScene::~GameScene()
{
	delete m_pPlayer;
	delete m_Input;
	delete m_Sound;
	for (int i = 0; i < 6; i++) {
		delete m_BG1[i];
		delete m_BG2[i];
	}

	for (int i = 0; i < 5; i++) {
		delete m_BG3[i];
	}
}

void GameScene::Input(float eTime)
{
	m_Input->ReadKey();

	index = 2;
	
	if (JumpTime > 0.5f) {
		anyKeyinput = true;

		if (m_Input->IsKeyPress(DIK_UPARROW)) {
			m_pPlayer->JumpKey = true;
			index = index == 4 ? 2 : ++index;
		}

		if (m_pPlayer->JumpKey == true && m_Input->IsKeyPress(DIK_UPARROW)) {
			m_pPlayer->Is2ndJumpKey = true;
		}

		JumpTime = 0;
	}

	if (m_pPlayer->m_Jump && !m_pPlayer->m_2ndJump) {
		m_Sound->Stop(index);
		m_Sound->Play(5);
	}
	if (!m_pPlayer->Is2ndJumpKey) m_Sound->Stop(5);
	if (anyKeyinput && m_pPlayer->pcPos.y >= (m_pPlayer->m_OrHeight)-100) m_Sound->Play(index);
	
	m_pPlayer->pcDir.x = 0;
	m_pPlayer->pcDir.x -= m_Input->IsKeyPress(DIK_LEFTARROW) * 2.2;
	m_pPlayer->pcDir.x += m_Input->IsKeyPress(DIK_RIGHTARROW);

	m_pPlayer->ArrangePos(100, 1300);
		
}

void GameScene::Update(float eTime)
{
	m_pPlayer->Update(eTime);
	m_Enemy->Update(eTime);

	JumpTime += eTime;

	for (int i = 0; i < 6; i++) { m_BG1[i]->Update(eTime); }

	this->Input(eTime);
}

void GameScene::Render()
{
	for (int i = 0; i < 6; i++) { m_BG1[i]->Render(); }

	m_pPlayer->Render();
	m_Enemy->Render();
}