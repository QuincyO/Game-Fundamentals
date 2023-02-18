// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>
#include<SDL_image.h>


constexpr float FPS = 60.0f;
constexpr float DELAY_TIME = 1000.0f / FPS;
bool isGameRunning = true;
SDL_Window* pWindow = nullptr;
SDL_Renderer* pRenderer = nullptr;
SDL_Texture* pMySprite = nullptr;


bool init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL init failed:" << SDL_GetError();
		return false;
	}
	std::cout << "SDL init Good";
	pWindow = SDL_CreateWindow("Quincy Orta 101070454", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, 0);


	if (pWindow == NULL) {
		return false;
	}
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	if (pRenderer == NULL) {
		return false;
	}
	return true;
}
void load() {
	//SDL_Texture* IMG_LoadTexture(SDL_Renderer * renderer, const char* file);
	pMySprite = IMG_LoadTexture(pRenderer, "../Assets/textures/ncl.png");
	if (pMySprite == NULL) {
		std::cout << "Image Failed to Load \n";
	}
}
void draw() {
	SDL_RenderCopy(pRenderer, pMySprite, NULL, NULL);
	SDL_RenderPresent(pRenderer);

}
void update() {

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


	// Display Main SDL Window

	// Main Game Loop
	load();
	while (isGameRunning)
	{
		const auto frame_start = static_cast<float>(SDL_GetTicks());
		input();
		draw();
		input();




		if (const float frame_time = static_cast<float>(SDL_GetTicks()) - frame_start;
			frame_time < DELAY_TIME)
		{
			SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
		}



	}

	return 0;
}

