#include "DXUT.h"
#include "player.h"
#include "global.h"
#include <vector>

Player::Player()
{

	playerState = ON_EDGE;
	makeVisit = false;
	speed = 3;
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
	if (px < 0)
	{
		px = 0;
	}
	if (px >= WIDTH)
	{
		px = WIDTH-1;
	}
	if (py < 0)
	{
		py = 0;
	}
	if (py >= HEIGHT)
	{
		py = HEIGHT-1;
	}


	if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0)
	{
		press = true;
	}

	if (playerState == ON_EDGE)
	{

		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
		{
			nextMap = map[py * WIDTH + (px + 1)];
			CanVisiting();
			if (nextMap == MAP_PROPERTY_EDGE)
			{
				px += speed;
			}
			
		}
		else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
		{
			nextMap = map[py * WIDTH + (px - 1)];
			CanVisiting();
			if (nextMap == MAP_PROPERTY_EDGE)
			{
				px -= speed;
			}
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
		{
			nextMap = map[(py - 1) * WIDTH + px];
			CanVisiting();
			if (nextMap == MAP_PROPERTY_EDGE)
			{
				py -= speed;
			}
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
		{
			nextMap = map[(py + 1) * WIDTH + px];
			CanVisiting();
			if (nextMap == MAP_PROPERTY_EDGE)
			{
				py += speed;
			}
		}
	}
	else if (playerState == VISITING)
	{

		if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) == 0)
		{
			press = false;

			px = startPos.x;
			py = startPos.y;
			playerState = ON_EDGE;
			for (int i = 0; i < visitingPos.size(); ++i)
			{
				int nx = visitingPos[i].x;
				int ny = visitingPos[i].y;
				//map[ny * WIDTH + nx] = MAP_PROPERTY_EMPTY;
			}
			//visitingPos.clear();
		}

		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
		{
			nextMap = map[py * WIDTH + (px + 1)];
			if (nextMap == MAP_PROPERTY_EMPTY)
			{
				for (int i = px+1; i <=px + speed; ++i)
				{
					map[py * WIDTH + i] = MAP_PROPERTY_VISITING;
					visitingPos.push_back(D3DXVECTOR2(i, py));
				}
				px += speed;
			}
			
			CanEdge();
		}
		else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
		{
			nextMap = map[py * WIDTH + (px - 1)];
			if (nextMap == MAP_PROPERTY_EMPTY)
			{
				px -= speed;
			}
			CanEdge();
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
		{
			nextMap = map[(py - 1) * WIDTH + px];
			if (nextMap == MAP_PROPERTY_EMPTY)
			{
				for (int i = py; i >= py - speed; --i)
				{
					map[i * WIDTH + px] = MAP_PROPERTY_VISITING;
					visitingPos.push_back(D3DXVECTOR2(px, i));
				}
				py -= speed;
			}
			
			CanEdge();
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
		{
			nextMap = map[(py + 1) * WIDTH + px];
			if (nextMap == MAP_PROPERTY_EMPTY)
			{
				py += speed;
			}
			CanEdge();
		}
	}
	press = false;
}

void Player::CanEdge()
{
	if (nextMap == MAP_PROPERTY_EDGE)
	{
		playerState = ON_EDGE;
		makeVisit = true;
		press = false;
	}
}

void Player::CanVisiting()
{
	if ((nextMap == MAP_PROPERTY_EMPTY) && press)
	{
		playerState = VISITING;
		startPos.x = px;
		startPos.y = py;
	}
	
}

Player::~Player()
{
	sprite->Release();
	(*playerTex)->Release();
}