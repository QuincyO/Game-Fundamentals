#include "fundObject.h"


 fundObject::fundObject(const char* texture) {
	objectTexture = textFund::loadTexture(texture,NULL);
	SDL_QueryTexture(objectTexture, NULL, NULL, &src.w, &src.h);
		src.x = 0;
		src.y = 0;
		dst.w = src.w;
		dst.h = src.h;

	if (objectTexture) {
		std::cout << "Image Created\n";
	}
	else {
		std::cout << "Image Failed to Load: " << SDL_GetError << std::endl;
	}
}



 void fundObject::input()
 {

 }



 Vec2 fundObject::getPos()
 {
	 Vec2 posXY = { dst.x,dst.y };
	 return posXY;
 }

 Vec2 fundObject::getSize()
 {
	Vec2 sizeXY = { dst.w,dst.h };
	 return sizeXY;
 }

 void fundObject::setPos(Vec2 posXY)
 {
	 dst.x = posXY.x;
	 dst.y = posXY.y;
 }

 void fundObject::setSpriteFrame(int width, int height,int frameTotal)
 {
	 src.w = width;
	 src.h = height;
	 src.w = src.w;
	 dst.h = src.h;
	 frameCount = frameTotal;
 }

 void fundObject::animate()
 {
	 if (animationTimer <= 0.0f) {
		 nextFrame();
		 animationTimer = animationTime;
	 }
	 animationTimer -= deltaTime;
 }

 void fundObject::setFrame(int frame)
 {
	currentFrame = frame;
	src.x = src.w * currentFrame;
	currentFrame %= frameCount;
 }
 
 void fundObject::nextFrame()
 {
	 setFrame(currentFrame + 1);
 }

 void fundObject::setSize(Vec2 width_or_height)
 {
	 dst.w = width_or_height.x;
	 dst.h = width_or_height.y;

 }


 void fundObject::update() {

}

void fundObject::shoot()
{
	//Shooting Mechanic

}

void fundObject::render(int rotation) {
	SDL_RenderCopyEx(gameRenderer::pRenderer, objectTexture, &src, &dst, rotation , NULL, flip);
		
}

void fundObject::createBullet(const char* filepath, SDL_Rect dst, Vec2 Velo)
{
	//bullet.GetandSetInfo(filepath, dst, Velo);
	//bullets.push_back(bullet);
}

void fundObject::updateBullets()
{
	//for (Bullet& b : bullets) {
	//	b.update();
	//}
}

void fundObject::drawBullets()
{
//for (Bullet& b : bullets)
//{
//	b.draw(NULL);
//}

}
