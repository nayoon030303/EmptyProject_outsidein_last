#pragma once
#include "DXUT.h"
#include "enemy.h"

class EnemySpeed :public Enemy
{
public:

	EnemySpeed();
	~EnemySpeed();
	
	void Render();
	void Update();
	D3DXVECTOR2 getPos();

	int x, y;
	int vx;
	int vy;
	int speed;

	LPDIRECT3DTEXTURE9* enemyTexture;
	LPD3DXSPRITE sprite;

};