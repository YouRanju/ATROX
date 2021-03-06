#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Background.h"

#include "CInput.h"
#include "CSound.h"

class GameScene
{
protected:
	float time;
	float bulletTime;
	float delay;

public:
	GameScene(HWND hwnd, HINSTANCE hinstance, LPDIRECT3DDEVICE9 device);
	virtual ~GameScene();

	Player* m_pPlayer;
	Enemy* m_Enemy;
	Background* m_BG1[6];
	Background* m_BG2[6];
	Background* m_BG3[5];

	CInput* m_Input;
	CSound* m_Sound;

	float JumpTime;
	float EnemyHowlingTime;
	
	int index;

	void Input(float eTime);
	void Update(float eTime);
	void Render();

	void SoundManage();

	void PlayerManage();
	void EnemyManage();
};
