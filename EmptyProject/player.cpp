#include "DXUT.h"
#include "player.h"
#include "global.h"

Player::Player()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
	playerTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), "img/player.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr, nullptr, playerTex);
	
}

void Player:: Render()
{
	
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 pos(5, 5, 0);
	sprite->Draw(*playerTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();
}

void Player::Update()
{
	if (GetAsyncKeyState((VK_LEFT) * 0x8000) != 0)
	{
		px -= 1;
	}
}

Player::~Player()
{
	sprite->Release();
	(*playerTex)->Release();
}