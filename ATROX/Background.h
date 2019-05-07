#pragma once

#include "CTexture.h"
#include "CSprite.h"

#define MAX 3

class Background
{
protected:
	CSprite* m_Spr[MAX];
	D3DXVECTOR3 m_Scroll;
	float m_Screen;
	float m_speed;

public:
	explicit Background(LPDIRECT3DDEVICE9 pDevice, const char* filename, float screen, float speed);
	virtual ~Background();

	void Update(float dt);
	void Render();

	void SetScroll(float point) {
		m_Scroll.x = point;
		if (m_Scroll.x < -m_Screen) {
			m_Scroll.x += m_Screen;
		}
	}
};
