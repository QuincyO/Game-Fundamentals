#include "Bullet.h"




void Bullet::draw(int rotation) {
	update();
	//SDL_RenderCopyEx(GameFund::pRenderer, bulletTexture, &srcRect, &dstRect, rotation, NULL, SDL_FLIP_NONE);
	SDL_RenderCopy(GameFund::pRenderer, bulletTexture, &srcRect, &dstRect);
}

void Bullet::GetandSetInfo(const char* filepath, SDL_Rect objectDST, Vec2 Velo)
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
	dstRect.x = objectDST.x + (objectDST.w / 2) - (dstRect.w / 2);
	dstRect.y = objectDST.y;
	velocity = Velo;
}

void Bullet::update() {
	
}