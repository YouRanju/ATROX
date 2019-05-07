#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class CText
{
protected:
	LPD3DXFONT m_pFont;

public:
	explicit CText(LPDIRECT3DDEVICE9 pDevice, int width, int height);
	virtual ~CText();

	void Draw(int x, int y, int width, int height, const TCHAR* text, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
};

