#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <map>

using namespace std;

class CTexture
{
protected:
	LPDIRECT3DDEVICE9 m_pDevice;
	map<const char*, LPDIRECT3DTEXTURE9> textures;

public:
	explicit CTexture(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CTexture();

	LPDIRECT3DTEXTURE9 LoadTexture(const char* filename);
	void UnloadTexture(const char* filename);
};
