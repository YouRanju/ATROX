#include "Background.h"


Background::Background(LPDIRECT3DDEVICE9 pDevice, const char* filename, float screen, float speed)
	: m_speed(speed), m_Screen(screen)
{
	for (int i = 0; i < MAX; i++) {
		m_Spr[i] = new CSprite(pDevice, filename);
		m_Spr[i]->SetCenter(D3DXVECTOR3(0, 0, 0));
	}

	m_Scroll.x = 0.f;
}

Background::~Background()
{
	for (int i = 0; i < MAX; i++) {
		delete m_Spr[i];
		m_Spr[i] = NULL;
	}
}

void Background::Update(float dt)
{
	m_Scroll.x -= (m_speed * dt);

	if (m_Scroll.x < -m_Screen) {
		m_Scroll.x += m_Screen;
	}

	D3DXVECTOR3 pos1 = D3DXVECTOR3(m_Scroll.x, 0.f, 0.f);
	D3DXVECTOR3 pos2 = pos1 + D3DXVECTOR3(m_Screen - 1, 0.f, 0.f);
	D3DXVECTOR3 pos3 = pos2 + D3DXVECTOR3(m_Screen - 1, 0.f, 0.f);

	m_Spr[0]->SetPosition(pos1);
	m_Spr[1]->SetPosition(pos2);
	m_Spr[2]->SetPosition(pos3);
}

void Background::Render()
{
	m_Spr[0]->Draw();
	m_Spr[1]->Draw();
	m_Spr[2]->Draw();
}