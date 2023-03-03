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

	struct spriteObject
	{

	public:
		SDL_Texture* pTexture;
		SDL_Rect src;
		SDL_Rect dst;
		double sAngle;
		//Default Consturctor with no arguments
		spriteObject()
		{
			pTexture = nullptr;
			sAngle = 0;
			src = { 0,0,0,0 };
			dst = { 0,0,0,0 };

		}
		//Constructor with arguments
		spriteObject(SDL_Renderer* renderer, const char* fileName, int angle)
		{
			pTexture = IMG_LoadTexture(renderer, fileName);
			if (pTexture == NULL) {
				std::cout << "Image Failed to Load: ";
				std::cout << fileName << std::endl;
			}
			else std::cout << "Image Load Succesful\n";
			SDL_QueryTexture(pTexture, NULL, NULL, &src.w, &src.h);

			src.x = 0;
			src.y = 0;
			dst.w = src.w;
			dst.h = src.h;
			sAngle = angle;
		}

		//Member Function of spriteObject Struct
		void draw(SDL_Renderer* renderer)
		{
			SDL_RenderCopyEx(pRenderer, pTexture, &src, &dst, sAngle, NULL, Flip);
		}



	private:


	};

spriteObject backGround_1 = spriteObject();
spriteObject playerShip = spriteObject();
spriteObject playerProjectile = spriteObject();
spriteObject playerHit = spriteObject();
spriteObject enemyShip = spriteObject();
spriteObject enemyProjectiles = spriteObject();
spriteObject bossSprite = spriteObject();
spriteObject bossProjectiles = spriteObject();
spriteObject astroid_1 = spriteObject();






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
	playerShip = spriteObject(pRenderer, "../Assets/PNG/player.png",NULL);
	playerProjectile = spriteObject(pRenderer, "../Assets/PNG/Lasers/laserRed01.png",NULL);
	playerHit = spriteObject(pRenderer, "../Assets/PNG/laserRedShot.png",NULL);
	enemyShip = spriteObject(pRenderer, "../Assets/PNG/Enemies/enemyBlue2.png",NULL);
	enemyProjectiles = spriteObject(pRenderer, "../Assets/PNG/Lasers/laserBlue01.png",180);
	bossSprite = spriteObject(pRenderer, "../Assets/PNG/Ships/spaceShips_005.png",NULL);
	bossProjectiles = spriteObject(pRenderer, "../Assets/PNG/Missiles/spaceMissiles_001.png",180);
	astroid_1 = spriteObject(pRenderer, "../Assets/PNG/Meteors/meteorBrown_big4.png",0);
	backGround_1 = spriteObject(pRenderer, "../Assets/PNG/Background/starBackground.png",NULL);


	//Object Sizing
		//PlayerShip
			int playerHeight = playerShip.src.h;
			int playerWidth = playerShip.src.w;
		//EnemyShip
			int enemyHeight = enemyShip.src.h;
			int enemyWidth = enemyShip.src.w;
		//Boss Ship
			int bossHeight = bossSprite.src.h;
			int bossWidth = bossSprite.src.w;
		//Astroids
			int astroidHeight = astroid_1.src.h;
			int astroidWidth = astroid_1.src.w;
		//Boss Projectiles
			int bossMissleHeight = bossProjectiles.src.h*1.5;
			int bossMissleWidth = bossProjectiles.src.w*1.5;
		//Player Projectiles
			int playerLaserHeight = playerProjectile.src.h;
			int playerLaserWidth = playerProjectile.src.w;
		//Enemy Projectiles
			int enemyLaserHeight = enemyProjectiles.src.h;
			int enemyLaserWidth = enemyProjectiles.src.w;

	//Screen Positions
		//Player Ship
			playerShip.dst.x = (SCREEN_WIDTH * .5) - (playerWidth / 2);
			playerShip.dst.y = (SCREEN_HEIGHT * .9);
			playerShip.dst.w = playerWidth;
			playerShip.dst.h = playerHeight;
		//Player Projectile
			playerProjectile.dst.x = playerShip.dst.x+(playerWidth/2)-(playerLaserWidth/2);
			playerProjectile.dst.y = playerShip.dst.y - (playerHeight) ;
			playerProjectile.dst.w = playerLaserWidth;
			playerProjectile.dst.h = playerLaserHeight;
		//Player Hit Marker
			playerHit.dst.y = -50;
			playerHit.dst.x = -50;
			playerHit.dst.w = playerHit.src.w;
			playerHit.dst.h = playerHit.src.h;
		//Enemy Ship Position
			enemyShip.dst.x = (SCREEN_WIDTH * .15) - (enemyHeight / 2);
			enemyShip.dst.y = (SCREEN_HEIGHT * .15);
			enemyShip.dst.h = enemyHeight;
			enemyShip.dst.w = enemyWidth;
		//Enemy Projectile Positon
			enemyProjectiles.dst.x = (enemyShip.dst.x) + (enemyWidth / 2) - (enemyLaserWidth / 2);
			enemyProjectiles.dst.y = (enemyShip.dst.y) + enemyHeight;
			enemyProjectiles.dst.h = enemyLaserHeight;
			enemyProjectiles.dst.w = enemyLaserWidth;
		//Boss Ship Location
			bossSprite.dst.x = (SCREEN_WIDTH * .75) - (bossWidth / 2);
			bossSprite.dst.y = (SCREEN_HEIGHT * .25)-bossHeight/2;
			bossSprite.dst.h = bossHeight;
			bossSprite.dst.w = bossWidth;
		//Boss Projectile Position
			bossProjectiles.dst.x = bossSprite.dst.x+(bossWidth/2)-(bossMissleWidth/2);
			bossProjectiles.dst.y = bossSprite.dst.y+bossHeight;
			bossProjectiles.dst.h = bossMissleHeight;
			bossProjectiles.dst.w = bossMissleWidth;
		//Astroid Position
			astroid_1.dst.x = SCREEN_WIDTH * .5 - (astroidWidth/2);
			astroid_1.dst.y = SCREEN_HEIGHT * .5;
			astroid_1.dst.w = astroidWidth;
			astroid_1.dst.h = astroidHeight;
		//Background
			backGround_1.dst.x = (SCREEN_WIDTH * 0);
			backGround_1.dst.y = (SCREEN_HEIGHT*0);
			backGround_1.dst.w = SCREEN_WIDTH;
			backGround_1.dst.h = SCREEN_HEIGHT;
}
void draw() {

	SDL_SetRenderDrawColor(pRenderer, 75, 81, 100, 0);


	//Drawing my game objects
	backGround_1.draw(pRenderer);
	astroid_1.draw(pRenderer);
	playerShip.draw(pRenderer);
	playerProjectile.draw(pRenderer);
	playerHit.draw(pRenderer);
	enemyShip.draw(pRenderer);
	enemyProjectiles.draw(pRenderer);
	bossSprite.draw(pRenderer);
	bossProjectiles.draw(pRenderer);



	SDL_RenderPresent(pRenderer);
	SDL_RenderClear(pRenderer);


}
void update(unsigned long int time) {
	astroid_1.sAngle += 1;
	enemyShip.dst.y += 2;
	playerProjectile.dst.y -= 30;
	enemyProjectiles.dst.y = enemyShip.dst.y+enemyShip.src.w;
	if (enemyShip.dst.y > SCREEN_HEIGHT) {
		enemyShip.dst.y = (SCREEN_HEIGHT * 0) - enemyShip.src.h;
	}

	if ((playerProjectile.dst.y<=astroid_1.dst.y+astroid_1.src.h)&&(playerProjectile.dst.y>=astroid_1.dst.y))
	{
		playerHit.dst.y = astroid_1.dst.y + (astroid_1.src.h / 4);
		playerHit.dst.x = astroid_1.dst.x + (astroid_1.src.w / 4);

		}
	else {
		playerHit.dst.y = -100;
		playerHit.dst.x = -100;
	}
	if (playerProjectile.dst.y < (SCREEN_HEIGHT*0)) {
		playerProjectile.dst.y = playerShip.dst.y - playerShip.src.h;
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
		update(frame_start);




		if (const float frame_time = static_cast<float>(SDL_GetTicks()) - frame_start;
			frame_time < DELAY_TIME)
		{
			SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
		}



	}

	return 0;
}

