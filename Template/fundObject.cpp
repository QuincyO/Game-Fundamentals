#include "fundObject.h"
#include"textFund.h"



 fundObject::fundObject(const char* texture,int x,int y) {
	objectTexture = textFund::loadTexture(texture,NULL);
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

void fundObject::update() {
	//Movement or Actions
	SDL_QueryTexture(objectTexture, NULL, NULL, &srcRect.w, &srcRect.h);



		srcRect.x = 0;
		srcRect.y = 0;


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
	if (shooting && shootingTimer <= 0.0f) {
		std::cout << "Shooting\n";

		//Resetting The Timer
		shootingTimer = shootCD;
	}

	shootingTimer -= deltaTime;

		dstRect.w = srcRect.w;
		dstRect.h = srcRect.h;
	



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

void fundObject::render(int rotation) {
	SDL_RenderCopyEx(GameFund::pRenderer, objectTexture, &srcRect, &dstRect, rotation , NULL, flip);
}