#pragma once
#include "DXUT.h"

class Enemy
{
public:
	virtual ~Enemy() {};
	virtual void Render() =0;
	virtual void Update() =0;

	
	virtual D3DXVECTOR2 getPos()
	{
		return D3DXVECTOR2(0, 0);
	}
};