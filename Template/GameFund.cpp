#include "GameFund.h"
#include "background.h"
#include "bulletManager.h"
#include "playerShip.h"
#include "enemyShip.h"

enemyShip enemy("../Assets/PNG/enemyShip.png");
playerShip* player;
background* map;
vector<enemyShip> enemies;


GameFund::GameFund() {}
GameFund::~GameFund() {}

SDL_Renderer* GameFund::pRenderer = nullptr;

void GameFund::init(const char* Title, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed to Start SDL" << std::endl;
		isRunning = false;
	}
	else {
		std::cout << "Init Good\n";
	}

	pWindow = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (pWindow) {
		std::cout << "Window Good" << std::endl;
		isRunning = false;
	}
	else
	{
		std::cout << "Window Bad\n";
		isRunning = false;
	}
	
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	
	SDL_SetRenderDrawColor(pRenderer, 0, 47, 74, 255);
	
	if (pRenderer) {
		std::cout << "Render Good " << std::endl;
		isRunning = true;
	}
	else {
		std::cout << "Render Bad\n";
			isRunning = false;
	}
}

bool GameFund::canSpawn()
{
	if (enemyTimer <= 0) {
		enemyTimer = enemySpawnRate;
		return true;
	}
	enemyTimer -= deltaTime;
	return false;
}

void GameFund::spawnShip()
{
	if (canSpawn()) {
		//enemy("../Assets/PNG/enemyShip.png");
		enemy.dst.y = rand() % 76 -151;
		enemy.dst.x = rand()%798;

		enemies.push_back(enemy);

	}
}

void GameFund::input() {
	player->input();
	spawnShip();
	for (auto& e : enemies) {
		e.shoot();
	}
	

}
void GameFund::update(){
	player->update();

	for (auto& b: enemy.enemyBullet.bullets )
	
		
		
		//Enemies Spawning
	for (enemyShip& e : enemies)
	{
		e.update();
	}
	map->update();
	

}
void GameFund::load() {
	map = new background();
	map->loadMap();
	player = new playerShip("../Assets/PNG/player.png");
	

	player->setPos({ 250,250 });




	

}

void GameFund::draw() {
	SDL_RenderClear(pRenderer);
	map->draw();
	player->render(NULL);
	player->draw();

	for (enemyShip& e : enemies) {
		e.render(NULL);
		e.draw();
	}


	SDL_RenderPresent(pRenderer);
}

bool GameFund::running() {
	return isRunning;
}

void GameFund::clean() {
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit;


}

