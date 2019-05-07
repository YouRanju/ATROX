#include <d3d9.h>
#include <d3dx9.h>
#include <atltypes.h>

#include "WinApp.h"
#include "CTexture.h"

#include "CSprite.h"

CSprite::CSprite(LPDIRECT3DDEVICE9 device, const char* filename)
	: m_pDevice(device)
{
	CTexture* tmp = new CTexture(device);

	m_pTexture = tmp->LoadTexture(filename);
	m_Color = D3DCOLOR_XRGB(255, 255, 255);

	D3DSURFACE_DESC desc;
	m_pTexture->GetLevelDesc(0, &desc);

	width = (float)desc.Width;
	height = (float)desc.Height;

	rect = CRect(0, 0, (int)width, (int)height);

	m_Center = D3DXVECTOR3(width / 2, height / 2, 0);

	Init();
}

CSprite::~CSprite()
{
	Release();
}

void CSprite::Init()
{
	auto hr = D3DXCreateSprite(m_pDevice, &m_pSpr);

	if (FAILED(hr)) throw 3L;
}

void CSprite::Draw()
{
	m_pSpr->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSpr->Draw(m_pTexture, &rect, &m_Center, &m_Pos, m_Color);
	m_pSpr->End();
}

void CSprite::Release()
{
	if (m_pSpr != NULL) {
		m_pSpr->Release();
		m_pSpr = NULL;
	}
}