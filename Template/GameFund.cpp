#include "GameFund.h"
#include "background.h"
#include "Bullet.h"
//#include "fundObject.cpp"
/* backGround_1 = spriteObject();
//spriteObject playerShip = spriteObject();
spriteObject playerProjectile = spriteObject();
spriteObject playerHit = spriteObject();
spriteObject enemyShip = spriteObject();
spriteObject enemyProjectiles = spriteObject();
spriteObject bossSprite = spriteObject();
spriteObject bossProjectiles = spriteObject();
spriteObject astroid_1 = spriteObject();
//Written Michael
spriteObject powerUp_1 = spriteObject();
spriteObject powerUp_2 = spriteObject();
spriteObject powerUp_3 = spriteObject();
spriteObject powerUp_4 = spriteObject();
spriteObject playerShield = spriteObject();
*/

fundObject* playerShip;
fundObject* enemyShip;
fundObject* heli; //Animation Testing


				  
//fundObject* bullet1;
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
	
	SDL_SetRenderDrawColor(pRenderer, 94, 63, 107, 255);
	
	if (pRenderer) {
		std::cout << "Render Good " << std::endl;
		isRunning = true;
	}
	else {
		std::cout << "Render Bad\n";
			isRunning = false;
	}
//player = fundObject("../Assets/PNG/player.png", pRenderer);
}

void GameFund::input() {
	playerShip->input();
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}
void GameFund::update(){
	playerShip->update();

	for (fundObject& enemies : enemyShips) {

	};
	enemyShip->update();
	heli->update();
	heli->setFrame(0);
}
void GameFund::load() {
	map = new background();
	playerShip = new fundObject("../Assets/PNG/player.png",0,500);

	v
	//enemyShip = new fundObject("../Assets/PNG/enemyShip.png",250, 250);
	
	heli = new fundObject("../Assets/textures/helicopter.png", 500, 500);
	heli->setSpriteFrame(128,56);

}

void GameFund::draw() {
	SDL_RenderClear(pRenderer);
	map->drawMap();
	playerShip->render(NULL);
	enemyShip->render(NULL);
	for (fundObject& enemies : enemyShips) {

	}
	//heli->render(NULL);

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

