#include "enemyShip.h"


Bullet eBullet;
std::vector<Bullet> eBullets;


enemyShip::enemyShip(const char* texture)
{
	eTex = textFund::loadTexture(texture, NULL);
	SDL_QueryTexture(eTex, NULL, NULL, &src.w, &src.h);
	src.x = src.y = 0;
	dst.w = src.w;
	dst.h = src.h;

		//This Code causes the console to stop working
	//if (eTex) {
	//	std::cout << "Image Created\n";
	//}
	//else {
	//	std::cout << "Image Failed to Load: " << SDL_GetError << std::endl;
	//}

}



void enemyShip::setPos(Vec2 pos)
{
	dst.x = pos.x;
	dst.y = pos.y;
}

void enemyShip::setPos(int x, int y)
{
	dst.x = x;
	dst.y = y;
}

void enemyShip::input()
{
}

void enemyShip::update()
{
	dst.y += 150 * deltaTime;
	updateBullets();
}

void enemyShip::shoot()
{
	if (canShoot()) {
		createBullet("../Assets/PNG/laserGreen.png", dst, bulletVelocity);
	}
}

void enemyShip::draw()
{
	textFund::draw(eTex, src, dst);
	drawBullets();
}

void enemyShip::createBullet(const char* filepath, SDL_Rect objectDST, Vec2 bulletVelo)
{
	eBullet.GetandSetInfo(filepath, objectDST, bulletVelo);
	eBullets.push_back(eBullet);
}

void enemyShip::updateBullets()
{
	for (Bullet& b : eBullets)
	{
		eBullet.update();
	}
}

void enemyShip::drawBullets()
{
	for (Bullet& b : eBullets)
	{
		eBullet.draw(NULL);
	}
}



bool enemyShip::canShoot()
{
	if (shootingTimer <= 0.0f&& dst.y>99) {
		shootingTimer = fireRate;
		return true;
	}
	shootingTimer -= deltaTime;
	return false;
}






