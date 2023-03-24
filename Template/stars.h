#pragma once
#include <SDL.h>
#include "textFund.h"
class Stars
{
public:

	Stars(const char* filepath) ;
	~Stars() {};

	void generateStars();
	void drawStars();


	SDL_Rect src, dst;
private:
	SDL_Texture* starTex;

	float deltaTime = 1.0f / 60.0f;

	float smallStarSpeed = 10 * deltaTime;
	float medStarSpeed = 30 * deltaTime;
	float bigStarSpeed = 100 * deltaTime;

};

