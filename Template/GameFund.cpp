#include "GameFund.h"
#include "background.h"
#include "bulletManager.h"
#include "playerShip.h"
#include "enemyShip.h"


vector<enemyShip> enemies;
playerShip* player;
enemyShip* enemy;
background* map;


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

void GameFund::input() {
	player->input();
	enemy->shoot({0,100});

}
void GameFund::update(){
	player->update();
	enemy->update();
	map->update();
	

}
void GameFund::load() {
	map = new background();
	map->loadMap();
	player = new playerShip("../Assets/PNG/player.png");
	

	player->setPos({ 250,250 });



	enemy = new enemyShip("../Assets/PNG/enemyShip.png");
	enemy->setPos({ 400,400 });
	

}

void GameFund::draw() {
	SDL_RenderClear(pRenderer);
	map->draw();
	player->render(NULL);
	player->draw();
	enemy->render(NULL);
	enemy->draw();


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

