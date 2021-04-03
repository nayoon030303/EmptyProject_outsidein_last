#include "DXUT.h"
#include "firstPage.h"
#include "global.h"

void FirstPage::Render()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);

	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), "img/background.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0,
		nullptr, nullptr, backgroundTex);

	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), "img/mask.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0,
		nullptr, nullptr, maskTex);

	RECT tdr = { 0,0,640,480 };
	D3DLOCKED_RECT tlr;
	if (SUCCEEDED((*backgroundTex)->LockRect(0, &tlr, &tdr, 0)))
	{
		DWORD* p = (DWORD*)tlr.pBits;
		memcpy(mapData, p, WIDTH * HEIGHT * 4);
		(*backgroundTex)->UnlockRect(0);
	}

}

void FirstPage::Update()
{

}

FirstPage::~FirstPage()
{

}