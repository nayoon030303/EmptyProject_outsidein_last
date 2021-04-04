
#include "DXUT.h"

#include "global.h"
#include "enemySpeed.h"

EnemySpeed::EnemySpeed()
{
	x = 100;
	y = 100;
	vx = 2;
	vy = 2;
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
	
	enemyTexture = new LPDIRECT3DTEXTURE9();
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
		enemyTexture
	);
}

void EnemySpeed::Update()
{
	x += vx;
	y += vy;

	if (binaryMap[y * WIDTH + x] == MAP_PROPERTY_VISIT)
	{
		//аб©Л 
		bool above = (map[(y + 1) * 640 + x] == MAP_PROPERTY_VISIT);
		bool below = (map[(y - 1) * 640 + x] == MAP_PROPERTY_VISIT);

		x -= vx;
		y -= vy;

		if (above && below)
		{
			vx *= -1;
		}
		else
		{
			vy *= -1;
		}
		return;
	}

	if (x < 0)
	{
		x = 0;
		vx *= -1;
	}
	if (x >= (WIDTH))
	{
		x = WIDTH - 10;
		vx *= -1;
	}
	if (y < 0)
	{
		y = 0;
		vy *= -1;
	}
	if (y >= (HEIGHT))
	{
		y = HEIGHT - 10;
		vy *= -1;
	}

	
}

D3DXVECTOR2 EnemySpeed::getPos()
{
	return D3DXVECTOR2(x, y);
}

void EnemySpeed::Render()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 pos(STARTX_POINT + x, STARTY_POINT+ y , 0);
	sprite->Draw(*enemyTexture, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 0, 255, 0));
	sprite->End();
}

EnemySpeed::~EnemySpeed()
{
	sprite->Release();
	(*enemyTexture)->Release();
}
