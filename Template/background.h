#pragma once
#include "GameFund.h"
#include "stars.h"
using namespace std;
//struct star
//{
//	SDL_Texture* bigStar;
//	SDL_Rect  dst, src;
//	float speed;
//};
class background
{
public:
	background();
	~background();
	

	void drawStar();
	void loadMap();
	void update();
	void draw();


private:
	int map[32][28];

	float deltaTime = 1.0f / 60.0f;
	int backgroundStarSpeed = 100 * deltaTime;
	float foregroundStarSpeed = 175 * deltaTime;
////	star Star;
	vector<Stars> stars1;
	vector<Stars> stars2;
//	vector<star> stars3;

	SDL_Texture* littleStar;
	SDL_Texture* lines;
	SDL_Texture* nebula;
	SDL_Texture* backGround;




};

