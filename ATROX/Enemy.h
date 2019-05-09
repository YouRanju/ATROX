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
	D3DXVECTOR3 Pos;
	float frame, frameSpeed;

	int hp;
	float speed;
	
public:
	CSprite *normalAni, *moveAni;
	vector<CSprite*> animate;

	D3DXVECTOR3 Dir;

	bool isLoad;

public:
	Enemy(LPDIRECT3DDEVICE9 device, const char* filename);
	virtual ~Enemy();

	void Update(float eTime);
	void Render();

	void SetHp(int hp) { 
		this->hp = hp; 
		isLoad = true; 
	}

	bool IsAlive()
	{
		if (hp > 0) return true;
		return false;
	}
};