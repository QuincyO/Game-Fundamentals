#include "bulletManager.h"




void bulletManager::createBullet(int xPos, int yPos, int width,int height)
{
	Bullet b("../Assets/PNG/laserRed.png", xPos, yPos,width,height);
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