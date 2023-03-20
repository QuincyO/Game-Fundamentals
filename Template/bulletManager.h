#pragma once
#include <vector>
#include "bullet.h"
class bulletManager
{

public:
	bulletManager() {}

	void createBullet(int xPos, int yPos,int width,int height);

	void updateBullet();

	void drawBullet();



private:
	std::vector<Bullet> bullets;



};

