#pragma once

class CSprite
{
protected:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXSPRITE		m_pSpr;

	D3DXVECTOR3			m_Pos;
	D3DXVECTOR3			m_Center;
	D3DCOLOR			m_Color;

	RECT rect;

	float width;
	float height;

public:
	CSprite(LPDIRECT3DDEVICE9 device, const char* filename);
	virtual ~CSprite();

	void Init();
	void Draw();
	void Release();

	void SetTrans(D3DXMATRIX mat) { 
		m_pSpr->SetTransform(&mat); 
	}
	
	void SetCenter(D3DXVECTOR3 cen) { m_Center = cen; }
	D3DXVECTOR3 GetCenter() { return m_Center; }

	void SetPosition(D3DXVECTOR3 pos) {	m_Pos = pos; }
	D3DXVECTOR3 GetPosition() { return m_Pos; }

	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }

	void SetColor(D3DCOLOR color) { m_Color = color; }
	D3DCOLOR GetColor() { return m_Color; }

	float GetWidth() { return width; }
	float GetHeight() { return height; }
};