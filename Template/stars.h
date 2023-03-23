#pragma once
#include <SDL.h>
class Stars
{
public:

	Stars() {};
	~Stars() {};

	void generateStars();



private:
	
	SDL_Rect src, dst;

};

