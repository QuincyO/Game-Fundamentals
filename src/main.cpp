// Core Libraries
#include <crtdbg.h>
#include <Windows.h>
#include "GameFund.h"
constexpr float FPS = 60.0f;
constexpr float DELAY_TIME = 1000.0f / FPS;
const int SCREEN_WIDTH = 896; //896 divisible by 32
const int SCREEN_HEIGHT = 1024;//1024 dividisible by 32

int main(int argc, char* args[])
{
srand(time(NULL));
	// show and position the application console
	AllocConsole();
	auto console = freopen("CON", "w", stdout);
	const auto window_handle = GetConsoleWindow();
	MoveWindow(window_handle, 100, 700, 800, 200, TRUE);
	GameFund* game = nullptr;
	Uint32 frames = 0;
	std::cout << "Hello World" << endl;

	game = new GameFund();
	game->init("Quincy and Michael Space Game", SCREEN_WIDTH, SCREEN_HEIGHT, false);

	game->load();
	// Main Game Loop
	while (game->running())
	{
		const auto frame_start = static_cast<float>(SDL_GetTicks());
		game->input();
		game->update();
		game->draw();

	if (const float frame_time = static_cast<float>(SDL_GetTicks()) - frame_start;
		frame_time < DELAY_TIME)
	{
     			SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
	}

	}
	game->clean();

	return 0;
}

