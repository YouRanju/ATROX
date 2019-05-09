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
	speed = 600;
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

	if ((int)frame >= level*2 && !m_Jump)
	{
		frame = (level == 1) ? 0 : (level == 2) ? 2 : 4;
	}

	pcPos += pcDir * eTime * speed;

	if (JumpKey) {
		this->Jump(eTime);
	}
}

void Player::Render()
{
//	D3DXMatrixScaling(&mat, 3.f, 3.f, 0.f);
//	animate[(int)frame]->SetTrans(mat);

	if (!m_Jump) {
		animate[(int)frame]->SetPosition(pcPos);
		animate[(int)frame]->Draw();
	}

	if (m_Jump) {
		animate[(int)frame]->Draw();
	}
	
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

void Player::Jump(float eTime)
{
	if (!m_Jump) {
		m_Jump = true;
		m_2ndJump = false;
		Is2ndJumpKey = false;
		m_JumpPower = 13.f;
		m_OrHeight = pcPos.y;
		m_PrHeight = pcPos.y;
		m_JumpTime = 0.f;
	}
	else if (m_Jump && !m_2ndJump && isFalling && Is2ndJumpKey) {
		m_JumpPower = 16.f;
		m_JumpTime = 0.f;
		m_2ndJump = true;
	}

	if (m_Jump) {
		m_JumpTime += (eTime * 4.f);
		float height = m_JumpPower + (-4.9 * m_JumpTime * m_JumpTime);

		pcPos.y -= height;
		isFalling = (pcPos.y - m_PrHeight) < 0 ? false : true;

		if (isFalling && Is2ndJumpKey) {
			frame = 1;
			Is2ndJumpKey = false;
		}
		else frame = 0;

		if (pcPos.y > m_OrHeight) {
			pcPos.y = m_OrHeight;
			m_Jump = false;

			frame = 1;
			animate[(int)frame]->SetPosition(pcPos);

			JumpKey = false;
		}

		m_PrHeight = pcPos.y;
		animate[(int)frame]->SetPosition(pcPos);
	}
}
