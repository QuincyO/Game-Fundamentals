#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "fundObject.h"



class GameFund
{
public:
	GameFund();
	~GameFund();

	void init(const char* Title, int width, int height, bool fullscreen);

	bool canSpawn();
	void spawnShip();
	void input();
	void update();
	void load();
	void draw();
	void clean();
	bool running();

	static SDL_Renderer *pRenderer;

private:
	float deltaTime = 1.0f / 60.0f;
	bool isRunning;
	SDL_Window* pWindow;
	float enemySpawnRate = 2.0f;
	float enemyTimer;


	int count;


};

