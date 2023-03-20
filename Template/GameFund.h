#pragma once

#include <iostream>
#include "SDL.h"
#include"fundObject.h"

class GameFund
{
public:
	GameFund();
	~GameFund();

	void init(const char* Title, int width, int height, bool fullscreen);

	void input();
	void update();
	void load();
	void draw();
	void clean();
	bool running();

	static SDL_Renderer *pRenderer;

private:
	bool isRunning;
	SDL_Window* pWindow;

	int count;


};

