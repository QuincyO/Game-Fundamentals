#pragma once
#include "textFund.h"
class Bullet
{
public:

	Bullet(const char* filepath,int xPos,int yPos,int width,int height);
	~Bullet() {}


	void update();
	void draw(int rotation);
	void clean();
	
private:
	SDL_Rect srcRect, dstRect;

	SDL_Texture* bulletTexture;



	

	const float deltaTime = 1.0f / 60.0f;
	const float bulletMoveSpeed = 1024 * deltaTime;








};

