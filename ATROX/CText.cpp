#include "CText.h"

CText::CText(LPDIRECT3DDEVICE9 pDevice, int width, int height)
{
	D3DXFONT_DESC desc;
	ZeroMemory(&desc, sizeof(LPD3DXFONT_DESC));

	desc.CharSet = DEFAULT_CHARSET;
	desc.Height = height;
	desc.MipLevels = 0;
	desc.Quality = DEFAULT_QUALITY;
	desc.Weight = FW_BOLD;
	desc.Width = width;
	desc.Italic = FALSE;
	wcscpy_s(desc.FaceName, TEXT("°íµñ"));

	auto hr = D3DXCreateFontIndirect(pDevice, &desc, &m_pFont);

	if (FAILED(hr)) throw 2L;
}


CText::~CText()
{
	if (m_pFont != NULL) {
		m_pFont->Release();
		m_pFont = NULL;
	}
}

void CText::Draw(int x, int y, int width, int height, const TCHAR* text, D3DCOLOR color)
{
	RECT rc;
	SetRect(&rc, x, y, x + width, y + height);

	m_pFont->DrawTextW(NULL, text, -1, &rc, DT_LEFT | DT_TOP, color);
}
