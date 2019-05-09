#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "CSprite.h"

using namespace std;

class Player
{
private:
	//D3DXMATRIX mat;
	float frame, frameSpeed;

	float speed;
	int level;

	//มกวม
	bool isFalling;
	float m_PrHeight;
	float m_JumpPower;
	float m_JumpTime;
	int m_life;

public:
	CSprite *normalAni, *moveAni;
	vector<CSprite*> animate;
	
	D3DXVECTOR3 pcPos;
	D3DXVECTOR3 pcDir;

	float m_OrHeight;

	bool m_Jump;
	bool m_2ndJump;
	bool JumpKey;
	bool Is2ndJumpKey;

public:
	Player(LPDIRECT3DDEVICE9 device);
	virtual ~Player();

	void Update(float eTime);
	void Render();

	void Jump(float eTime);
	
	void ArrangePos(float sx, float ex);
};

