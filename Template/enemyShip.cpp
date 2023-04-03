#include "enemyShip.h"

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
	drawBullets();
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






