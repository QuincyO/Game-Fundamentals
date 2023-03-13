#pragma once
#include "GameFund.h"
class background
{


public:
	background();
	~background();
	


	void loadMap(int array[32][28]);
	void drawMap();


private:
	int map[32][28];


	SDL_Rect src, dst;

	SDL_Texture* star1;
	SDL_Texture* star2;
	SDL_Texture* lines;
	SDL_Texture* nebula;
	SDL_Texture* backGround;




};

