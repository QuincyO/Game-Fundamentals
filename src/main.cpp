// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>
#include<SDL_image.h>
#include <SDL.h>


constexpr float FPS = 60.0f;
constexpr float DELAY_TIME = 1000.0f / FPS;
bool isGameRunning = true;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 1100;
SDL_Window* pWindow = nullptr;
SDL_Renderer* pRenderer = nullptr;
SDL_RendererFlip Flip = SDL_FLIP_NONE;

SDL_Surface* backGround;

SDL_Texture* enemySprite;
SDL_Texture* enemyProjectiles;
SDL_Texture* playerSprite;
SDL_Texture* playerProjectiles;
SDL_Texture* bossSprite;
SDL_Texture* bossProjectiles;
SDL_Texture* astroidObject;
SDL_Texture* background_1;



SDL_Rect playerSpriteSRC, enemySpriteSRC,playerProjectilesSRC, enemyProjectilesSRC, bossSpriteSRC, bossProjectilesSRC, astroidObjectSRC;
SDL_Rect playerSpriteDST, enemySpriteDST,playerProjectilesDST, enemyProjectilesDST, bossSpriteDST,bossProjectilesDST, astroidObjectDST;



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

	//Applying textures
	playerSprite = IMG_LoadTexture(pRenderer, "../Assets/PNG/player.png");
	playerProjectiles = IMG_LoadTexture(pRenderer, "../Assets/PNG/Lasers/laserBlue01.png");
	enemySprite = IMG_LoadTexture(pRenderer, "../Assets/PNG/Enemies/enemyBlue2.png");
	enemyProjectiles = IMG_LoadTexture(pRenderer, "../Assets/PNG/Lasers/laserRed01.png");
	bossSprite = IMG_LoadTexture(pRenderer, "../Assets/PNG/Ships/spaceShips_005.png");
	bossProjectiles = IMG_LoadTexture(pRenderer, "../Assets/PNG/Missiles/spaceMissiles_001.png");
	astroidObject = IMG_LoadTexture(pRenderer, "../Assets/PNG/Meteors/meteorBrown_big4.png");


	backGround = IMG_Load("..Assets/PNG/Background/backgroundColor");
	background_1 = SDL_CreateTextureFromSurface(pRenderer, backGround);

	int backgroundWidth, backgroundHeight;
	SDL_QueryTexture(background_1, NULL, NULL, &backgroundWidth, &backgroundHeight);
	SDL_FreeSurface(backGround);


	if (bossProjectiles == NULL) {
		std::cout << "Image Load Failed\n";
	}
	else std::cout << "Image Load Successful\n";

	//Player Sprite
		playerSpriteSRC.x = 0;
		playerSpriteSRC.y = 0;
		playerSpriteSRC.w = 99;
		playerSpriteSRC.h = 75;
	//Player Projectile Sprite
		playerProjectilesSRC.x = 0;
		playerProjectilesSRC.y = 0;
		playerProjectilesSRC.w = 9;
		playerProjectilesSRC.h = 54;
	//Enemy Ship Sprite
		enemySpriteSRC.x = 0;
		enemySpriteSRC.y = 0;
		enemySpriteSRC.w = 104;
		enemySpriteSRC.h = 84;
	//Enemy ship Projectiles Sprite
		enemyProjectilesSRC.x = 0;
		enemyProjectilesSRC.y = 0;
		enemyProjectilesSRC.w = 9;
		enemyProjectilesSRC.h = 54;
	//Boss Sprite
		bossSpriteSRC.x = 0;
		bossSpriteSRC.y = 0;
		bossSpriteSRC.w = 342;
		bossSpriteSRC.h = 301;
	//Boss Projectile Sprites
		bossProjectilesSRC.x = 0;
		bossProjectilesSRC.y = 0;
		bossProjectilesSRC.w = 40;
		bossProjectilesSRC.h = 69;
	//Astroid Sprite
		astroidObjectSRC.x = 0;
		astroidObjectSRC.y = 0;
		astroidObjectSRC.w = 98;
		astroidObjectSRC.h = 96;
	//Object Sizing
		//PlayerShip
			int playerHeight = playerSpriteSRC.h;
			int playerWidth = playerSpriteSRC.w;
		//EnemyShip
			int enemyHeight = enemySpriteSRC.h;
			int enemyWidth = enemySpriteSRC.w;
		//Boss Ship
			int bossHeight = bossSpriteSRC.h;
			int bossWidth = bossSpriteSRC.w;
		//Astroids
			int astroidHeight = astroidObjectSRC.h;
			int astroidWidth = astroidObjectSRC.w;
		//Boss Projectiles
			int bossMissleHeight = bossProjectilesSRC.h*1.5;
			int bossMissleWidth = bossProjectilesSRC.w*1.5;
		//Player Projectiles
			int playerLaserHeight = playerProjectilesSRC.h;
			int playerLaserWidth = playerProjectilesSRC.w;
		//Enemy Projectiles
			int enemyLaserHeight = enemyProjectilesSRC.h;
			int enemyLaserWidth = enemyProjectilesSRC.w;

	//Screen Positions
		//Player Ship
			playerSpriteDST.x = (SCREEN_WIDTH * .5) - (playerWidth / 2);
			playerSpriteDST.y = (SCREEN_HEIGHT * .9);
			playerSpriteDST.w = playerWidth;
			playerSpriteDST.h = playerHeight;
		//Player Projectile
			playerProjectilesDST.x = playerSpriteDST.x+(playerWidth/2)-(playerLaserWidth/2);
			playerProjectilesDST.y = playerSpriteDST.y - (playerHeight) ;
			playerProjectilesDST.w = playerLaserWidth;
			playerProjectilesDST.h = playerLaserHeight;
		//Enemy Ship Position
			enemySpriteDST.x = (SCREEN_WIDTH * .15) - (enemyHeight / 2);
			enemySpriteDST.y = (SCREEN_HEIGHT * .15);
			enemySpriteDST.h = enemyHeight;
			enemySpriteDST.w = enemyWidth;
		//Enemy Projectile Positon
			enemyProjectilesDST.x = (enemySpriteDST.x) + (enemyWidth / 2) - (enemyLaserWidth / 2);
			enemyProjectilesDST.y = (enemySpriteDST.y) + enemyHeight;
			enemyProjectilesDST.h = enemyLaserHeight;
			enemyProjectilesDST.w = enemyLaserWidth;
		//Boss Ship Location
			bossSpriteDST.x = (SCREEN_WIDTH * .75) - (bossWidth / 2);
			bossSpriteDST.y = (SCREEN_HEIGHT * .25)-bossHeight/2;
			bossSpriteDST.h = bossHeight;
			bossSpriteDST.w = bossWidth;
		//Boss Projectile Position
			bossProjectilesDST.x = bossSpriteDST.x+(bossWidth/2)-(bossMissleWidth/2);
			bossProjectilesDST.y = bossSpriteDST.y+bossHeight;
			bossProjectilesDST.h = bossMissleHeight;
			bossProjectilesDST.w = bossMissleWidth;
		//Astroid Position
			astroidObjectDST.x = SCREEN_WIDTH * .5 - (astroidWidth/2);
			astroidObjectDST.y = SCREEN_HEIGHT * .5;
			astroidObjectDST.w = astroidWidth;
			astroidObjectDST.h = astroidHeight;
}
void draw() {

	SDL_SetRenderDrawColor(pRenderer, 75, 81, 100, 0);

	//Render Player Ship and Laser
	SDL_RenderCopy(pRenderer, playerSprite, &playerSpriteSRC, &playerSpriteDST);
	SDL_RenderCopy(pRenderer, playerProjectiles, &playerProjectilesSRC, &playerProjectilesDST);
	//Render Enemy Ship and Laser
	SDL_RenderCopyEx(pRenderer, enemySprite, &enemySpriteSRC, &enemySpriteDST, 0, NULL, Flip);
	SDL_RenderCopyEx(pRenderer, enemyProjectiles, &enemyProjectilesSRC, &enemyProjectilesDST, 180, NULL, Flip);
	//Render Boss Ship and Missle
	SDL_RenderCopyEx(pRenderer, bossSprite, &bossSpriteSRC, &bossSpriteDST, 0, NULL, Flip);
	SDL_RenderCopyEx(pRenderer, bossProjectiles, &bossProjectilesSRC, &bossProjectilesDST, 180, NULL, Flip);
	//Render Astroid
	SDL_RenderCopyEx(pRenderer, astroidObject, &astroidObjectSRC, &astroidObjectDST,0, NULL, Flip);



	SDL_RenderPresent(pRenderer);
	SDL_RenderClear(pRenderer);


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

