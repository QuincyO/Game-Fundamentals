#include "bulletManager.h"




//void bulletManager::createBullet(const char* filepath,int xPos, int yPos, int width,int height)
void bulletManager::createBullet(const char* filepath,SDL_Rect dst,Vec2 velocity)
{
	Bullet b(filepath, dst,velocity);
	bullets.push_back(b);

	

}

void bulletManager::updateBullet()
{
	for (Bullet& b : bullets) {
		b.update();
	}
}

void bulletManager::drawBullet()
{
	for (Bullet& b : bullets) {
		b.draw(NULL);
	}
}