#pragma once
#include "fundObject.h"
#include "Bullet.h"
#include <vector>
class enemyShip :public fundObject
{
public:
	enemyShip(const char* texture) :fundObject(texture){};


	void input() ;
	void update() ;
	void shoot() ;
	void draw();
	


	bool canShoot();

	void createBullet(const char* filepath, SDL_Rect dst, Vec2 Velo);
	void updateBullets();
	void drawBullets();

	std::vector<Bullet> enemyBullets;
private:
	float deltaTime = 1.0f / 60.0f;
	Vec2 bulletVelocity = { 0,300 };

	int moveSpeed = 100 * deltaTime;

	float fireRate = 1.0f;
	float shootingTimer = 0;

};

