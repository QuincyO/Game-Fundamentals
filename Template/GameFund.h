#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "Vec2.h"
#include "background.h"
#include "pRenderer.h"
#include "playerShip.h"


//#include "enemyShip.h"



class GameFund
{
public:
	GameFund() { pRenderer = nullptr;  };
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

	static SDL_Renderer* pRenderer;
	

private:
	float deltaTime = 1.0f / 60.0f;
	bool isRunning;
	SDL_Window* pWindow;
	//enemyShip* enemy;
	float enemySpawnRate = 2.0f;
	float enemyTimer;


	int count;


};

