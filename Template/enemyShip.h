#pragma once
#include "fundObject.h"
class enemyShip :public fundObject
{
	enemyShip(const char* texture) :fundObject(texture){};




private:
	float deltaTime = 1.0f / 60.0f;


	int moveSpeed = 100 * deltaTime;

	float fireRate = 0.8f;
	float shootingTimer = 0;

};

