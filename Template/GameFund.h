#pragma once

#include <iostream>
#include "SDL.h"

class GameFund
{
public:
	GameFund();
	~GameFund();

	void init(const char* Title, int xPos, int yPos, int width, int height, bool fullscreen);

	void input();
	void update();
	void load();
	void draw();
	void clean();
	bool running();

private:
	bool isRunning;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

	int count;


};

