#include "fundObject.h"
#include"textFund.h"



 fundObject::fundObject(const char* texture,int x,int y) {
	objectTexture = textFund::loadTexture(texture,rotation);
	if (objectTexture) {
		std::cout << "Image Created\n";
	}
	else {
		std::cout << "Image Failed to Load: " << SDL_GetError << std::endl;
	}
	xPos = x;
	yPos = y;
}

void fundObject::update() {
	//Movement or Actions

	SDL_QueryTexture(objectTexture, NULL, NULL, &srcRect.w, &srcRect.h);

	srcRect.x = 0;
	srcRect.y = 0;


	dstRect.w = srcRect.w;
	dstRect.h = srcRect.h;
	dstRect.x = xPos;
	dstRect.y = yPos;

}

void fundObject::render() {
	SDL_RenderCopyEx(GameFund::pRenderer, objectTexture, &srcRect, &dstRect, rotation , NULL, flip);
}