#pragma once
#include <vector>
#include "Bullet.h"
class bulletManager
{

public:
	bulletManager() {};
	~bulletManager() {};

	//void createBullet(const char* filepath,int xPos, int yPos,int width,int height);
	void createBullet(const char* filepath,SDL_Rect sourceDst,Vec2 velocity);

	void updateBullet();

	void drawBullet();



private:
	std::vector<Bullet> bullets;




};

