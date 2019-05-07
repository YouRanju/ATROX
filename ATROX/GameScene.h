#pragma once

#include "Player.h"
#include "Background.h"

#include "CInput.h"

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
	Background* m_BG1[6];
	Background* m_BG2[6];
	Background* m_BG3[5];

	CInput* m_Input;

	void Input();
	void Update(float eTime);
	void Render();
};
