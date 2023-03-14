#pragma once
#include "textFund.h"
class Bullet
{
public:

	Bullet(const char* filepath,int x,int y);
	~Bullet() {}


	void update();
	void draw(int rotation);
	void clean();

private:

	SDL_Texture* bulletTexture;
	SDL_Rect srcRect, dstRect;


	const float deltaTime = 1.0f / 60.0f;
	const float bulletMoveSpeed = 1024 * deltaTime;








};

