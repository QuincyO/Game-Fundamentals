#pragma once
#include "SDL.h"
class gameRenderer
{
public:

	static gameRenderer& getInstance() {
		static gameRenderer instance;
		return instance;
	}

	static SDL_Renderer* pRenderer;
};

