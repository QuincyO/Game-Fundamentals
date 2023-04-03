#pragma once

#include "stars.h"
using namespace std;
class Stars;
class background
{
public:
	background();
	~background() {};
	

	void drawStar();
	void loadMap();
	void update();
	void draw()


private:
	int map[32][28];

	float deltaTime = 1.0f / 60.0f;
	int backgroundStarSpeed = 100 * deltaTime;;
	float foregroundStarSpeed = 200 * deltaTime;

	vector<Stars> stars1;
	vector<Stars> stars2;

	SDL_Texture* littleStar;
	SDL_Texture* lines;
	SDL_Texture* nebula;
	SDL_Texture* backGround;




};

