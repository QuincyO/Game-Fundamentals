#include "enemyShip.h"

void enemyShip::input()
{
}

void enemyShip::update()
{
	dst.y += 150 * deltaTime;
	enemyBullet.updateBullet();
}

void enemyShip::shoot()
{
	if (canShoot()) {
		enemyBullet.createBullet("../Assets/PNG/laserGreen.png", dst, bulletVelocity);
	}
}

void enemyShip::draw()
{
	enemyBullet.drawBullet();
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

void enemyShip::createBullet(const char* filepath, SDL_Rect dst, Vec2 Velo)
{
	Bullet b(filepath, dst, Velo);
	enemyBullets.push_back(b);
}

void enemyShip::updateBullets()
{
	for (Bullet& b : enemyBullets) {
		b.update();
	}
}

void enemyShip::drawBullets()
{
	for (Bullet& b : enemyBullets)
	{
		b.draw(NULL);
	}
}
