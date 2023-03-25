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

void playerShip::update()
{
	if (upMove) {
		dst.y -= playerMoveSpeedPerSec;

	}
	if (downMove) {
		dst.y += playerMoveSpeedPerSec + 1;

	}
	if (leftMove) {
		dst.x -= playerMoveSpeedPerSec;

	}
	if (rightMove) {
		dst.x += playerMoveSpeedPerSec + 1;

	}

	//Preventing From exiting Box
	if (dst.x >= 896 - dst.w - 10) {
		dst.x = 896 - dst.w - 10;
	}
	if (dst.x <= 0 + 10) {
		dst.x = 10;
	}
	if (dst.y >= 1024 - dst.h - 10) {
		dst.y = 1024 - dst.h - 10;
	}
	if (dst.y <= 0 + 10) {
		dst.y = 0 + 10;
	}
	//Shooting Mechanic
	shoot();
	bullet.updateBullet();
}

void playerShip::shoot()
{
	if (shooting && fireTimer <= 0.0f) {
		currentFrame += 1;
		bullet.createBullet(dst.x, dst.y, dst.w, dst.h);
		fireTimer = fireRate;
	}
	fireTimer -= deltaTime;

}

void playerShip::draw()
{
	bullet.drawBullet();
}
