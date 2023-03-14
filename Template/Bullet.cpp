#include "Bullet.h"


Bullet::Bullet(const char* filepath, int x,int y)
{
	bulletTexture = textFund::loadTexture(filepath, NULL);

	if (bulletTexture) {
		std::cout << "Bullet Image Loaded\n";
	}
	else std::cout << "Bullet Failed to load: " << SDL_GetError << std::endl;
	SDL_QueryTexture(bulletTexture, NULL, NULL, &srcRect.w, &srcRect.h);

	srcRect.x = srcRect.y = 0;
	dstRect.h = srcRect.h;
	dstRect.w = srcRect.w;
	dstRect.x = x;
	dstRect.y = y;
	
}

void Bullet::draw(int rotation) {
	SDL_RenderCopyEx(GameFund::pRenderer, bulletTexture, &srcRect, &dstRect,rotation,NULL, SDL_FLIP_NONE);
}