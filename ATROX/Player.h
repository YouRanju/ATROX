#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "Player.h"
#include "CSprite.h"

using namespace std;

class Player
{
private:
	//D3DXMATRIX mat;
	D3DXVECTOR3 pcPos;
	float frame, frameSpeed;

	float speed;
	int level;

public:
	CSprite *normalAni, *moveAni;
	vector<CSprite*> animate;
	
	D3DXVECTOR3 pcDir;

public:
	Player(LPDIRECT3DDEVICE9 device);
	virtual ~Player();

	void Update(float eTime);
	void Render();

	void ArrangePos(float sx, float ex);
};

