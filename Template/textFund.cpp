#include "textFund.h"




SDL_Texture* textFund::loadTexture(const char* filename,int rotation)
{
	SDL_Texture* image = IMG_LoadTexture(GameFund::pRenderer, filename);

	return image;
}



void textFund::draw(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dst,int rotation)
{
	//SDL_RenderCopy(GameFund::pRenderer, tex, &src, &dst);
	SDL_RenderCopyEx(GameFund::pRenderer, tex, &src, &dst, rotation, NULL, SDL_FLIP_NONE);
}
