#pragma once

class InputManager
{
public:
	char key[256];
	int prevKey[256];
	
	void Update()
	{
		for (int i = 0; i < 256; i++)
		{
			prevKey[i] = key[i];
		}

	} };
