#include "Player.h"
#include "WinApp.h"

Player::Player(LPDIRECT3DDEVICE9 device)
{
	//1
	normalAni = new CSprite(device, "Resource/player/tank.png");
	normalAni->SetPosition(
		D3DXVECTOR3(WinApp::WIDTH / 2 - normalAni->GetWidth() / 2, 
			1000 - (normalAni->GetHeight() + 100),
			0
		)
	);
	animate.push_back(normalAni);

	moveAni = new CSprite(device, "Resource/player/tank_down.png");
	moveAni->SetPosition(normalAni->GetPosition());
	animate.push_back(moveAni);

	// 2
	normalAni = new CSprite(device, "Resource/player/tank2.png");
	normalAni->SetPosition(
		D3DXVECTOR3(WinApp::WIDTH / 2 - normalAni->GetWidth() / 2,
			1000 - (normalAni->GetHeight() + 100),
			0
		)
	);
	animate.push_back(normalAni);

	moveAni = new CSprite(device, "Resource/player/tank2_down.png");
	moveAni->SetPosition(normalAni->GetPosition());
	animate.push_back(moveAni);

	// 3
	normalAni = new CSprite(device, "Resource/player/tank3.png");
	normalAni->SetPosition(
		D3DXVECTOR3(WinApp::WIDTH / 2 - normalAni->GetWidth() / 2,
			1000 - (normalAni->GetHeight() + 100),
			0
		)
	);
	animate.push_back(normalAni);

	moveAni = new CSprite(device, "Resource/player/tank3_down.png");
	moveAni->SetPosition(normalAni->GetPosition());
	animate.push_back(moveAni);

	level = 1;
	frame = (level == 1) ? 0 : (level == 2) ? 2 : 4;
	frameSpeed = 5.0f;

	pcPos = animate[(int)frame]->GetPosition();
	speed = 300;
}

Player::~Player()
{
	for (auto iter = animate.begin(); iter != animate.end(); iter++)
	{
		delete(*iter);
	}
	animate.clear();
}

void Player::Update(float eTime)
{
	frame += eTime * frameSpeed;

	if ((int)frame >= level*2)
	{
		frame = (level == 1) ? 0 : (level == 2) ? 2 : 4;
	}

	pcPos += pcDir * eTime * speed;
}

void Player::Render()
{
//	D3DXMatrixScaling(&mat, 3.f, 3.f, 0.f);
//	animate[(int)frame]->SetTrans(mat);

	animate[(int)frame]->SetPosition(pcPos);
	animate[(int)frame]->Draw();
}

void Player::ArrangePos(float sx, float ex)
{
	if (pcPos.x < sx) {
		pcPos.x = sx;
	}
	if (pcPos.x > ex) {
		pcPos.x = ex;
	}
}
