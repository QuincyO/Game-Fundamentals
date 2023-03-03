// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>
#include <sdl.h>
#include <SDL_Image.h>

//icluding another code file.tooo read this

// global variables are accesssible from any context
constexpr float FPS = 60.0f;//target frames per second
constexpr float DELAY_TIME = 1000.0f / FPS;//target time between frames in ms
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;


//initialise SDL,open a window and set up renderer


bool isGameRunning = true;

//anything with a star to its right is apointer.SDL_Window is a memory address of an SDL_Window
//pointers vcan also be set to point to memeory address 0, meaning no address. we call these null poimters
//computer memory is
SDL_Window* pWindow = nullptr;// asssigning a pointer to nullptr means the address 0
SDL_Renderer* pRenderer = NULL;//NULL is the address 0
SDL_Texture* pMysprite = NULL;// texture is another word for image in game programming 
SDL_Rect Myspritesrc;
SDL_Rect MyspriteDst;

// set up game window
bool Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Display Main SDL Window
	// 
	// get pointer to SDL_Window object
	pWindow = SDL_CreateWindow("pavanijalapati-101433827", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, 0
	);
	if (pWindow == NULL) // if window address as not been set
	{
		std::cout << "window creation failed!" << SDL_GetError() << std::endl;
		return false;
	}
	else {
		std::cout << "window creation successful!\n";
	}

	//get pointer to SDL_Renderer object to use for drawing sprites
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	if (pRenderer == NULL) //if create renderer failed....
	{

		std::cout << "Renderer creation failed!" << SDL_GetError() << std::endl;
		return false;
	}
	else {
		std::cout << "Renderer creation successful!\n";

	}
	return true;
}

void Load() {
	//load texture...
		//SdL_Texture*IMG_LoadTexture(SDL_Renderer*renderer,const char*file);
	pMysprite = IMG_LoadTexture(pRenderer, "../Assets/textures/enterprise.png");
	if (pMysprite == NULL)
	{

		std::cout << "Image load failed!" << SDL_GetError() << std::endl;

	}
	else
	{
		std::cout << "Image load successful!\n";

	}

	//describe location to copy from in the texture
	Myspritesrc.x = 0;
	Myspritesrc.y = 0;
	Myspritesrc.w = 643;
	Myspritesrc.h = 296;

	// describe location to paste to on the screen
	int shipwidth = Myspritesrc.w / 4;
	int shipheight = Myspritesrc.h / 4;
	MyspriteDst.x = SCREEN_WIDTH / 8;//start with the left eighth of the screen as open space
	MyspriteDst.y = (SCREEN_HEIGHT / 2) - (shipheight / 2);//exactly centered vertically
	MyspriteDst.w = shipwidth;
	MyspriteDst.h = shipheight;
}
void Input()
{


}

void update()
{
	MyspriteDst.x = MyspriteDst.x + 1;
}

void Draw()
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 20, 255);
	SDL_RenderClear(pRenderer);

	//the & before a variable asks for that object's memory address
	int result = SDL_RenderCopy(pRenderer, pMysprite, &Myspritesrc, &MyspriteDst);
	if (result != 0) {
		std::cout << "Render failed!" << SDL_GetError() << std::endl;
	}


	// show the backbuffer which we have been drawing to prior.This is part of a common rendering technique called double buffering
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
	Load();
	//Load texture....
	//SDL_Texture * IMG_LoadTexture(SDL_Renderer *renderer, const, char *file)

	//Render Texture
	//int SDL_RenderCopy(SDL_Renderer* renderer,
   //SDL_Texture*texture,
   //const SDL_RECT*srcrect,



 // Main Game Loop,one iteration of this game loop is one frame
	while (isGameRunning)
	{
		//time at the start of the frame, in ms
		const auto frame_start = static_cast<float>(SDL_GetTicks());
		Input();
		update();
		Draw();

		//fake player input
		//update game state(presumably based on other conditions and input)
		//draw to score to show new game state to player
		//figure how long we need to wait for the next frame training.
		// current time - time at start of frame = time elapsed during this frame
		const float frame_time = static_cast<float>(SDL_GetTicks()) - frame_start;
		if (frame_time < DELAY_TIME)// if time passed is less than the time we have for each frame...
		{
			//do nothing for a while until its time for the next frame
			SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
		}

		// delta time. time elapsed this frame,in seconds
		const float delta_time = (static_cast<float>(SDL_GetTicks()) - frame_start) / 1000.0f;

	}



	return 0;
}

