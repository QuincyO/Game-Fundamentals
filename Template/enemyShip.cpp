#include "enemyShip.h"



enemyShip::enemyShip(const char* texture)
{
	eTex = textFund::loadTexture(texture, NULL);
	SDL_QueryTexture(eTex, NULL, NULL, &src.w, &src.h);
	src.x = src.y = 0;
	dst.w = src.w;
	dst.h = src.h;
	bulletVelocity = { 0, 150 };

		//This Code causes the console to stop working
	//if (eTex) {
	//	std::cout << "Image Created\n";
	//}
	//else {
	//	std::cout << "Image Failed to Load: " << SDL_GetError << std::endl;
	//}

}



void enemyShip::setPos(Vec2 pos)
{
	dst.x = pos.x;
	dst.y = pos.y;
}

void enemyShip::setPos(int x, int y)
{
	dst.x = x;
	dst.y = y;
}

void enemyShip::input()
{
}

void enemyShip::update()
{
	dst.y += 150 * deltaTime;
}

void enemyShip::shoot()
{
	
		createBullet("../Assets/PNG/laserGreen.png",eBullets);

}

void enemyShip::draw()
{
	textFund::draw(eTex, src, dst);
	
}


void enemyShip::createBullet(const char* filepath, std::vector<Bullet>& bullets )
{
	Bullet eBullet;
	eBullet.GetandSetInfo(filepath, dst, bulletVelocity);
	bullets.push_back(eBullet);
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






