#include "Enemy.h"
#include "WinApp.h"

Enemy::Enemy(LPDIRECT3DDEVICE9 device, const char* filename)
{
	char source[1][100];
	sprintf_s(source[0], 100, "Resource/enemy/%s.png",filename);
	normalAni = new CSprite(device, source[0]);
	normalAni->SetPosition(D3DXVECTOR3(1600, normalAni->GetHeight()+50, 0));
	animate.push_back(normalAni);
	
	sprintf_s(source[0], 100, "Resource/enemy/%s_down.png", filename);
	moveAni = new CSprite(device, source[0]);
	moveAni->SetPosition(normalAni->GetPosition());
	animate.push_back(moveAni);

	frame = 0;
	frameSpeed = 5.0f;

	//pcPos = animate[(int)frame]->GetPosition();
	speed = 400;
}

Enemy::~Enemy()
{
	for (auto iter = animate.begin(); iter != animate.end(); iter++)
	{
		delete(*iter);
	}
	animate.clear();
}

void Enemy::Update(float eTime)
{
	frame += eTime * frameSpeed;

	if ((int)frame >= 2)
	{
		frame = 0;
	}

	//pcPos += pcDir * eTime * speed;
}

void Enemy::Render()
{
	//	D3DXMatrixScaling(&mat, 3.f, 3.f, 0.f);
	//	animate[(int)frame]->SetTrans(mat);

	//animate[(int)frame]->SetPosition(pcPos);
	animate[(int)frame]->Draw();
}
