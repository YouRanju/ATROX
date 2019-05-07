#include "CTexture.h"

CTexture::CTexture(LPDIRECT3DDEVICE9 pDevice) : m_pDevice(pDevice) { }

CTexture::~CTexture()
{
	for (auto iter = textures.begin(); iter != textures.end(); iter++)
	{
		(iter->second->Release());
	}
	textures.clear();
}

LPDIRECT3DTEXTURE9 CTexture::LoadTexture(const char* filename)
{
	if (textures[filename] != NULL) return textures[filename];

	auto hr = D3DXCreateTextureFromFileExA(m_pDevice, filename,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0,
		D3DFMT_A8B8G8R8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		NULL, NULL, NULL, &textures[filename]);

	if (FAILED(hr)) return NULL;

	return textures[filename];
}

void CTexture::UnloadTexture(const char* filename)
{
	if (textures[filename] != NULL)
	{
		textures[filename]->Release();
		auto iter = textures.find(filename);
		textures.erase(iter);
	}
}