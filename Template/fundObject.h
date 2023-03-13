#pragma once
#include"textFund.h"
#include<SDL.h>

class fundObject
{
public:

	fundObject(const char* filename,int x,int y);
	~fundObject();

	void update();
	void render();

private:

	int yPos;
	int xPos;
	int rotation;

	SDL_Texture* objectTexture;
	SDL_Rect srcRect, dstRect;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	

	


};

