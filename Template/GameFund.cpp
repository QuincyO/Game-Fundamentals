
#include "GameFund.h"

#include "enemyShip.h"
//enemyShip enemy("../Assets/PNG/enemyShip.png");
background* map;
vector<enemyShip> enemies;
playerShip* player;




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
	
	 pRenderer= SDL_CreateRenderer(pWindow, -1, 0);
	
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


	}
}

void GameFund::input() {
	player->input();
//	spawnShip();
//	for (auto& e : enemies) {
//		e.shoot();
//	}
//	
//
}
void GameFund::update(){
	player->update();

//	for (auto& b : enemy.bullets)
//	{
//		//check for collision
//	}
	
		
		
		//Enemies Spawning
//	for (enemyShip& e : enemies)
//	{
//		e.update();
//	}
//	map->update();
	

}
void GameFund::load() {
	player = new playerShip("../Assets/PNG/player.png");
	player->setPos({ 250,250 });
	//map = new background();
	//map->loadMap();
	//player = new playerShip("../Assets/PNG/player.png");
	//
	//
	//player->setPos({ 250,250 });




	

}

void GameFund::draw() {
	SDL_RenderClear(pRenderer);
	player->draw(NULL);
	
	//map->draw();
	//player->render(NULL);
	//player->draw();
	//
	//for (enemyShip& e : enemies) {
	//	e.render(NULL);
	//	e.draw();
	//}


	SDL_RenderPresent(pRenderer);
}



bool GameFund::running() {
	return isRunning;
}

void GameFund::clean() {
	delete player;
	player = nullptr;
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit;


}
