#include "playerShip.h"

playerShip::playerShip(const char* texture) : fundObject(texture)
{
}



void playerShip::setSpriteSheetInfo(int width_of_frame, int height_of_frame, int amount_of_frames)
{

}

void playerShip::input()
{

	while (SDL_PollEvent(&pEvent)) {
		SDL_Scancode key = pEvent.key.keysym.scancode;
		switch (pEvent.type)
		{
		case (SDL_KEYDOWN):
			switch (key)
			{
			case(SDL_SCANCODE_W):
				upMove = true;
				break;
			case(SDL_SCANCODE_S):
				downMove = true;
				break;
			case(SDL_SCANCODE_A):
				leftMove = true;
				break;
			case(SDL_SCANCODE_D):
				rightMove = true;
				break;
			case(SDL_SCANCODE_SPACE):
				shooting = true;
				break;
			}
			break;
		case (SDL_KEYUP):
			switch (key)
			{
			case(SDL_SCANCODE_W):
				upMove = false;
				break;
			case(SDL_SCANCODE_S):
				downMove = false;
				break;
			case(SDL_SCANCODE_A):
				leftMove = false;
				break;
			case(SDL_SCANCODE_D):
				rightMove = false;
				break;
			case(SDL_SCANCODE_SPACE):
				shooting = false;
				break;
			}
		}
	}

}

void playerShip::move(Vec2 inputVector1)
{
	dst.y += inputVector1.y * (playerMoveSpeedPerSec * deltaTime);
	dst.x += inputVector1.x * (playerMoveSpeedPerSec * deltaTime);
	inputVector.y = 0;
	inputVector.x = 0;
}

void playerShip::update()
{
	//Movement
	if (upMove) {inputVector.y = -1;}
	if (downMove) {inputVector.y = 1;}
	if (leftMove) {inputVector.x = -1;}
	if (rightMove) {inputVector.x = 1;}
	move(inputVector);
	
	//Preventing From exiting Box
	if (dst.x >= 896 - getSize().x - 10)	{ dst.x = 896 - dst.w - 10; }
	if (dst.x <= 0 + 10)					{dst.x = 10;}
	if (dst.y >= 1024 - getSize().y - 10)	{ dst.y = 1024 - dst.h - 10; }
	if (dst.y <= 0 + 10)					{dst.y = 0 + 10;}
	//Shooting Mechanic
	shoot();
	bullet.updateBullet();
}

void playerShip::shoot()
{
	if (shooting && fireTimer <= 0.0f) {
		
		bullet.createBullet("../Assets/PNG/laserRed.png",dst, bulletVelocity);
		fireTimer = fireRate;
	}
	fireTimer -= deltaTime;

}

void playerShip::draw()
{
	bullet.drawBullet();
}
