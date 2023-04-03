#pragma once
#include "textFund.h"
#include "GameFund.h"
class playerShip;
class Bullet
{
public:

	Bullet(){};
	~Bullet() {}

	void GetandSetInfo(const char* filepath, SDL_Rect objectDst, Vec2 velocity);
	void update();
	void draw(int rotation);
	
private:
	SDL_Rect srcRect, dstRect = { 0,0,0,0 };

	Vec2 velocity;
	SDL_Texture* bulletTexture;




	float deltaTime = 1.0f / 60.0f;
	float bulletMoveSpeed = 1024 * deltaTime;








};

