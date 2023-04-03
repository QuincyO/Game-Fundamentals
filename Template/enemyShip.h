#pragma once
#include "fundObject.h"
class fundObject;
class enemyShip :public fundObject
{
public:
	enemyShip();
	enemyShip(const char* texture) :fundObject(texture){};


	void input() ;
	void update() ;
	void shoot() ;
	void draw();
	


	bool canShoot();



private:
	float deltaTime = 1.0f / 60.0f;
	Vec2 bulletVelocity = { 0,300 };

	int moveSpeed = 100 * deltaTime;

	float fireRate = 1.0f;
	float shootingTimer = 0;

};

