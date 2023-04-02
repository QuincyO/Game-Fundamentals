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
