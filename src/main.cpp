// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>
#include<SDL_image.h>
#include "Game.h"

constexpr float FPS = 60.0f;
constexpr float DELAY_TIME = 1000.0f / FPS;
bool isGameRunning = true;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
SDL_Window* pWindow = nullptr;
SDL_Renderer* pRenderer = nullptr;
SDL_RendererFlip Flip = SDL_FLIP_NONE;

SDL_Texture* playerSprite, enemySprite, projectileShips, bossSprite;
SDL_Rect* playerSpriteSRC, enemySpriteSRC, projectileShipsSRC, bossSpriteSRC;
SDL_Rect* playerSpriteDST, enemySpriteDST, projectileShipsDST, bossSpriteSRC;


bool init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL init failed:" << SDL_GetError();
		return false;
	}
	std::cout << "SDL init Good \n";
	pWindow = SDL_CreateWindow("Quincy Orta 101070454", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);


	if (pWindow == NULL) {
		return false;
		std::cout << "Failed to open window" << std::endl;
	}
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	if (pRenderer == NULL) {
		std::cout << "pRender did not load" << std::endl;
		return false;
	}
	return true;
}
void load() {
	//SDL_Texture* IMG_LoadTexture(SDL_Renderer * renderer, const char* file);
	pMySprite = IMG_LoadTexture(pRenderer, "../Assets/PNG/playerShip1_blue.png");

	if (pMySprite == NULL) {
		std::cout << "Image Failed to Load \n";
	}
	else std::cout << "Image load good" << std::endl;


	enterpriseSpriteSRC.x = 0;
	enterpriseSpriteSRC.y = 0;
	enterpriseSpriteSRC.w = 75;
	enterpriseSpriteSRC.h = 99;

	int shipHeight = enterpriseSpriteSRC.h / 2;
	int shipWidth = enterpriseSpriteSRC.w / 2;

	enterpriseSpriteDST.x = 0;
	enterpriseSpriteDST.y = (SCREEN_HEIGHT*.75)-(shipHeight/2);
	enterpriseSpriteDST.w = shipWidth;
	enterpriseSpriteDST.h = shipHeight;

	mySpriteSRC.x = 0;
	mySpriteSRC.y = 0;
	mySpriteSRC.w = 75;
	mySpriteSRC.h = 99;

	mySpriteDST.x = SCREEN_WIDTH-shipWidth;
	mySpriteDST.y = (SCREEN_HEIGHT / 4) - (shipHeight / 2);
	mySpriteDST.w = shipWidth;
	mySpriteDST.h = shipHeight;
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

}
void draw() {

	SDL_SetRenderDrawColor(pRenderer, 75, 81, 100, 0);
	SDL_RenderCopy(pRenderer, pMySprite, &enterpriseSpriteSRC, &enterpriseSpriteDST);
	SDL_RenderCopyEx(pRenderer, pMySprite, &mySpriteSRC, &mySpriteDST, 270, NULL,Flip);
	SDL_RenderPresent(pRenderer);
	SDL_RenderClear(pRenderer);


}
void update() {
	enterpriseSpriteDST.x += 1;
	if (enterpriseSpriteDST.x > SCREEN_WIDTH) {
		enterpriseSpriteDST.x = 0 - (enterpriseSpriteSRC.w/2);
	}
	mySpriteDST.x -= 1;
	if (mySpriteDST.x <= 0-(mySpriteSRC.w/2)) {
		mySpriteDST.x = SCREEN_WIDTH + (mySpriteDST.w / 2);
	}
}
void input() {

}

/**
 * \brief Program Entry Point
 */
int main(int argc, char* args[])
{
	// show and position the application console
	AllocConsole();
	auto console = freopen("CON", "w", stdout);
	const auto window_handle = GetConsoleWindow();
	MoveWindow(window_handle, 100, 700, 800, 200, TRUE);

	isGameRunning = init();
	Uint32 frames = 0;


	load();

	// Display Main SDL Window
	// Main Game Loop
	while (isGameRunning)
	{
		const auto frame_start = static_cast<float>(SDL_GetTicks());
		input();
		draw();
		update();




		if (const float frame_time = static_cast<float>(SDL_GetTicks()) - frame_start;
			frame_time < DELAY_TIME)
		{
			SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
		}



	}

	return 0;
}

