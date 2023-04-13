#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "Vec2.h"
#include "background.h"
#include <string>

#include "SDL_mixer.h"
#include<SDL_image.h>


static float deltaTime = 1.0f/ 60.0f;



class GameFund
{
public:
	GameFund() {};
	~GameFund();

	void init(const char* Title, int width, int height, bool fullscreen);

	bool canSpawn();
	void spawnShip();
	void input();
	void updatePlayer();
	void update();
	void detectCollisions();
	void load();
	void start();
	void draw();
	void clean();
	bool running();

	static SDL_Renderer* pRenderer;

private:
	float deltaTime = 1.0f / 60.0f;
	bool isRunning;
	SDL_Window* pWindow;
	float enemySpawnRate = 2.0f;
	float enemyTimer;



	int count;


};

