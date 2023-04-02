#pragma once
#include "textFund.h"
class Bullet
{
public:

	Bullet(const char* filepath,SDL_Rect objectDST,Vec2 velocity);
	~Bullet() {}


	void update();
	void draw(int rotation);
	
private:
	SDL_Rect srcRect, dstRect;

	Vec2 velocity;
	SDL_Texture* bulletTexture;




	float deltaTime = 1.0f / 60.0f;
	 float bulletMoveSpeed = 1024 * deltaTime;








};

