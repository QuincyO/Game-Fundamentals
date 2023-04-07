#pragma once
#include <SDL.h>
#include"textFund.h"



class enemyShip 
{
public:
	enemyShip() {};
	enemyShip(const char* texture);

	void setPos(Vec2 pos);
	void setPos(int x, int y);

	void input() ;
	void update() ;
	void shoot() ;
	void draw();
	

	void updateBullets();
	void drawBullets();

	bool canShoot();



private:

	SDL_Rect src, dst;
	SDL_Texture* eTex;
	Vec2 bulletVelocity;

	int moveSpeed = 100 * deltaTime;

	float fireRate = 1.0f;
	float shootingTimer = 0;

};

