#pragma once
#include "textFund.h"
#include "GameFund.h"
class Bullet
{
public:

	Bullet(){};
	~Bullet(){}

	void GetandSetInfo(const char* filepath, SDL_Rect objectDst, Vec2 velocity);
	void update();
	void draw(int rotation);
	
private:

	Vec2 velocity;
	SDL_Rect dstRect, srcRect;
	SDL_Texture* bulletTexture;





};

