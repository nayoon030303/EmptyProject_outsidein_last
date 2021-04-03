#include "DXUT.h"
#include "player.h"
#include "global.h"

Player::Player()
{
	playerState = ON_EDGE;

	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
	playerTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(), 
		"img/player.png", 
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2, 
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		playerTex);
	
}

void Player:: Render()
{
	
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 pos(STARTX_POINT+px-5, STARTY_POINT+py-5, 0);
	sprite->Draw(*playerTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 0, 255, 0));
	sprite->End();
}

void Player::Update()
{
	if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0)
	{
		press = true;
	}

	if (playerState == ON_EDGE)
	{
		
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
		{
			nextMap = map[py * WIDTH + (px+1)];
			CanGo();
		}
		else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
		{
			nextMap = map[py * WIDTH + (px - 1)];
			CanGo();
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
		{
			nextMap = map[(py-1) * WIDTH + px];
			CanGo();
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
		{
			nextMap = map[(py+1) * WIDTH + px];
			CanGo();
		}
	}
	else if (playerState == VISITING)
	{
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
		{
			nextMap = map[py * WIDTH + (px + 1)];
			CanGo();
		}
		else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
		{
			nextMap = map[py * WIDTH + (px - 1)];
			CanGo();
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
		{
			nextMap = map[(py - 1) * WIDTH + px];
			CanGo();
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
		{
			nextMap = map[(py + 1) * WIDTH + px];
			CanGo();
		}
	}

	press = false;
}
void Player::CanGo()
{
	if ((nextMap == MAP_PROPERTY_EMPTY) && press)
	{
		playerState = VISITING;
		pos.x = px;
		pos.y = py;
	}
	else if (nextMap == MAP_PROPERTY_EDGE)
	{
		px += 1;
	}
}

Player::~Player()
{
	sprite->Release();
	(*playerTex)->Release();
}