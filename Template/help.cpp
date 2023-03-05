// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;
// Global variables are accessible from any context
constexpr float FPS = 60.0f;
constexpr float DELAY_TIME = 1000.0f / FPS;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 600;
bool isGameRunning = true;
SDL_Window* pWindow;
SDL_Renderer* pRenderer;
SDL_Rect mySpriteSrc;
SDL_Rect mySpriteDst;

namespace Fund
{

	struct Sprite
	{
	public:

		SDL_Texture* pTexture;
		SDL_Rect src;
		SDL_Rect dst;
		double rotationDegrees = 0;
		SDL_RendererFlip flipState = SDL_FLIP_NONE;

		Sprite()
		{
			std::cout << "Sprite Default Constructor!" << std::endl;
			pTexture = nullptr;
			//rotationDegrees = 0;
			src = { 0,0,0,0 };
			dst = { 0,0,0,0 };
		}


		Sprite(SDL_Renderer* renderer, const char* imageFilePath)
		{
			std::cout << "Sprite Constructor!" << std::endl;
			pTexture = IMG_LoadTexture(renderer, imageFilePath);
			if (pTexture == NULL)
			{
				std::cout << "Image load failed! " << SDL_GetError() << std::endl;
			}
			else
			{
				std::cout << "Image load success: " << imageFilePath << std::endl;
			}

			if (SDL_QueryTexture(pTexture, NULL, NULL, &src.w, &src.h) != 0)
			{
				std::cout << "Query Texture failed! " << SDL_GetError() << std::endl;
			}
			src.x = 0;
			src.y = 0;

			dst.x = 0;
			dst.y = 0;
			dst.w = src.w;
			dst.h = src.h;
		}

		void Draw(SDL_Renderer* renderer)
		{
			int result = SDL_RenderCopyEx(renderer, pTexture, &src, &dst, rotationDegrees, NULL, flipState);
			if (result != 0)
			{
				std::cout << "Render failed! " << SDL_GetError() << std::endl;
			}
		}

		void SetPosition(int x, int y)
		{
			dst.x = x;
			dst.y = y;
		}
	};
}


using namespace Fund;
Sprite MC = Sprite();
Sprite Enemy1;
Sprite Enemy2;
Sprite Boss;



bool Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	// Display Main SDL Window

	pWindow = SDL_CreateWindow("Brandon Quach 101191483", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if (pWindow == NULL)
	{
		cout << "Windows creation failed!" << SDL_GetError() << endl;
		return false;
	}
	else
	{
		cout << "Winidows creation Success!" << endl;

	}

	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	if (pRenderer == NULL)
	{
		cout << "Renderer creation failed!" << SDL_GetError() << endl;
		return false;
	}
	else
	{
		cout << "Renderer creation Success!" << endl;
	}
	return true;
}
void Load()
{
	MC = Sprite(pRenderer, "../Assets/PNG/player.png");

	int MCW = MC.src.w;
	int MCH = MC.src.h;
	MC.dst.w = MCW;
	MC.dst.h = MCH;
	MC.dst.x = (WINDOW_WIDTH / 8); // start with the left eighth of the screen as open space
	MC.dst.y = (WINDOW_HEIGHT / 2) - MCH / 2; // exactly centered vertically
	MC.SetPosition(100, 400);

	//Background_image.dst.w = WINDOW_WIDTH;



	Enemy1 = Sprite(pRenderer, "../Assets/PNG/player.png");
	Enemy1.SetPosition(700, 400);

	Enemy1.flipState = SDL_FLIP_HORIZONTAL;


	Enemy2 = Sprite(pRenderer, "../Assets/PNG/player.png");
	Enemy2.SetPosition(700, 100);

	Enemy2.flipState = SDL_FLIP_HORIZONTAL;

	Boss = Sprite(pRenderer, "../Assets/PNG/player.png");
	Boss.SetPosition(900, 250);

	Boss.flipState = SDL_FLIP_HORIZONTAL;

}
void Input()
{
}

void Update()
{

}

void Draw()
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 20, 255);
	SDL_RenderClear(pRenderer);

	MC.Draw(pRenderer); //Call the member function Draw on my Sprite object
	Enemy1.Draw(pRenderer);
	Enemy2.Draw(pRenderer);
	Boss.Draw(pRenderer);

	//Show the BackBuffer which we have been drawing to prior. This is part of a common rendering technique called Double Buffering.
	SDL_RenderPresent(pRenderer);
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

	isGameRunning = Initialize();

	SDL_Texture* pMysprite = IMG_LoadTexture(pRenderer, "../Assets/textures/explosion1.png");

	Load();

	// Main Game Loop
	while (isGameRunning)
	{
		const auto frame_start = static_cast<float>(SDL_GetTicks());
		//Calling three functions in sequence...
		Input();
		Update();
		Draw();

		const float frame_time = static_cast<float>(SDL_GetTicks()) - frame_start;
		if (const float frame_time = static_cast<float>(SDL_GetTicks()) - frame_start;
			frame_time < DELAY_TIME)
		{
			SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
		}

		// delta time
		const auto delta_time = (static_cast<float>(SDL_GetTicks()) - frame_start) / 1000.0f;


	}

	getchar();
	return 0;
}

