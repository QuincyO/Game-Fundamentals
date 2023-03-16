#include "fundObject.h"
#include"textFund.h"
#include "bulletManager.h"
	bulletManager bullet;



 fundObject::fundObject(const char* texture,int x,int y) {
	objectTexture = textFund::loadTexture(texture,NULL);
	SDL_QueryTexture(objectTexture, NULL, NULL, &srcRect.w, &srcRect.h);
		srcRect.x = 0;
		srcRect.y = 0;
		dstRect.w = srcRect.w;
		dstRect.h = srcRect.h;
	if (objectTexture) {
		std::cout << "Image Created\n";
	}
	else {
		std::cout << "Image Failed to Load: " << SDL_GetError << std::endl;
	}
	xPos = x;
	yPos = y;
	dstRect.x = xPos;
	dstRect.y = yPos;
}


 void fundObject::input()
 {

	 SDL_Event event; //Creating SDL Event Viarable
	 while (SDL_PollEvent(&event)) {
		 SDL_Scancode key = event.key.keysym.scancode;
		 switch (event.type)
		 {
		 case (SDL_KEYDOWN):
			 switch (key)
			 {
			 case(SDL_SCANCODE_W):
				 upMove = true;
				 break;
			 case(SDL_SCANCODE_S):
				 downMove = true;
				 break;
			 case(SDL_SCANCODE_A):
				 leftMove = true;
				 break;
			 case(SDL_SCANCODE_D):
				 rightMove = true;
				 break;
			 case(SDL_SCANCODE_SPACE):
				 shooting = true;
				 break;
			 }
			 break;
		 case (SDL_KEYUP):
			 switch (key)
			 {
			 case(SDL_SCANCODE_W):
				 upMove = false;
				 break;
			 case(SDL_SCANCODE_S):
				 downMove = false;
				 break;
			 case(SDL_SCANCODE_A):
				 leftMove = false;
				 break;
			 case(SDL_SCANCODE_D):
				 rightMove = false;
				 break;
			 case(SDL_SCANCODE_SPACE):
				 shooting = false;
				 break;
			 }

		 }
	 }
 }

 Vec2 fundObject::getPos()
 {
	 Vec2 returnvec = { dstRect.x,dstRect.y };
	 return returnvec;
 }

 void fundObject::setSpriteFrame(int width, int height)
 {
	 srcRect.w = width;
	 srcRect.h = height;
	 dstRect.w = srcRect.w;
	 dstRect.h = srcRect.h;
 }

 void fundObject::setFrame(int frame)
 {
	 //currentFrame = frame;
	srcRect.x = srcRect.w * currentFrame;
 }

 void fundObject::setSize(Vec2 widthHeight)
 {
	 dstRect.x = widthHeight.x;
	 dstRect.y = widthHeight.y;

 }

 void fundObject::setSize(int w, int h)
 {
	 dstRect.w = w;
	 dstRect.h = h;
 }

 void fundObject::update() {
	//Movement or Actions

	//2 Axis Movement
	if (upMove) {
			dstRect.y -= playerMoveSpeedPerSec;

		}
	if (downMove) {
		dstRect.y += playerMoveSpeedPerSec +1 ;

	}
	if (leftMove) {
		dstRect.x -= playerMoveSpeedPerSec;

	}
	if (rightMove) {
		dstRect.x += playerMoveSpeedPerSec +1;

	}
	//Shooting Mechanic
	shoot();
	bullet.updateBullet();

	//Preventing From exiting Box
		if (dstRect.x >= 896-dstRect.w-10) {
			dstRect.x = 896 - dstRect.w-10;
		}
		if (dstRect.x <= 0+10) {
			dstRect.x = 10;
		}
		if (dstRect.y >= 1024 - dstRect.h-10) {
			dstRect.y = 1024 - dstRect.h-10;
		}
		if (dstRect.y <= 0 + 10) {
			dstRect.y = 0+10;
		}
}

void fundObject::shoot()
{
	//Shooting Mechanic
	if (shooting && shootingTimer <= 0.0f) {
		currentFrame += 1;
		//bullet.createBullet(dstRect.x, dstRect.y,dstRect.w,dstRect.h);
		shootingTimer = shootCD;
	}
	shootingTimer -= deltaTime;
}

void fundObject::render(int rotation) {
	SDL_RenderCopyEx(GameFund::pRenderer, objectTexture, &srcRect, &dstRect, rotation , NULL, flip);
		bullet.drawBullet();
}