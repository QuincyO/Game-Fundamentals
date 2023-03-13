#pragma once
#include "GameFund.h"
#include<SDL_image.h>
#include<SDL.h>

class textFund
{


public:

	 static SDL_Texture* loadTexture(const char* filename, int rotation);
	 static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst);

};

