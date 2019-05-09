#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "CSprite.h"

using namespace std;

class Enemy
{
private:
	//D3DXMATRIX mat;
	//D3DXVECTOR3 pcPos;
	float frame, frameSpeed;

	float speed;

public:
	CSprite *normalAni, *moveAni;
	vector<CSprite*> animate;

	//D3DXVECTOR3 pcDir;

public:
	Enemy(LPDIRECT3DDEVICE9 device, const char* filename);
	virtual ~Enemy();

	void Update(float eTime);
	void Render();
};