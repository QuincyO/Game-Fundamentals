#pragma once
#include "GameFund.h"
class background
{


public:
	background();
	~background();
	

	void drawStar();
	void loadMap();
	void drawMap();


private:
	int map[32][28];

	float deltaTime = 1.0f / 60.0f;
	int backgroundStarSpeed = 100 * deltaTime;
	float foregroundStarSpeed = 350 * deltaTime;

	SDL_Rect src, dst;

	SDL_Texture* bigStar;
	SDL_Texture* littleStar;
	SDL_Texture* lines;
	SDL_Texture* nebula;
	SDL_Texture* backGround;




};

