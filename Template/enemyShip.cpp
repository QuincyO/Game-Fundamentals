#include "enemyShip.h"

void enemyShip::input()
{
}

void enemyShip::update()
{
	enemyBullet.updateBullet();
}

void enemyShip::shoot(Vec2 Velo)
{
	if (canShoot()) {
		enemyBullet.createBullet("../Assets/PNG/laserGreen.png", dst, Velo);
	}
}

void enemyShip::draw()
{
	enemyBullet.drawBullet();
}

bool enemyShip::canShoot()
{
	if (shootingTimer <= 0.0f) {
		shootingTimer = fireRate;
		return true;
	}
	shootingTimer -= deltaTime;
	return false;
}
