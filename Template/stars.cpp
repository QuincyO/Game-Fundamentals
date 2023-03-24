#include "stars.h"

Stars::Stars(const char* filepath)
{
	starTex = textFund::loadTexture(filepath,NULL);

	SDL_QueryTexture(starTex, NULL, NULL, &src.w, &src.h);
	src.x = src.y = 0;
	dst.w = src.w;
	dst.h = src.h;

}

void Stars::generateStars()
{
	for (int i = 0; i < 100; i++)
	{

	}
}

void Stars::drawStars()
{
	SDL_RenderCopy(GameFund::pRenderer, starTex, &src, &dst);
}
