#include "GameFund.h"
#include "gameStrut.cpp"
int SCREEN_WIDTH = 900;
int SCREEN_HEIGHT = 900;

spriteObject backGround_1 = spriteObject();
spriteObject playerShip = spriteObject();
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


GameFund::GameFund() {}
GameFund::~GameFund() {}

void GameFund::init(const char* Title, int xPos,int yPos, int width, int height, bool fullscreen) {
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

	pWindow = SDL_CreateWindow(Title, xPos, yPos, width, height, flags);
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
	
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	
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
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}
void GameFund::update(){



}
void GameFund::load() {
	//SDL_Texture* IMG_LoadTexture(SDL_Renderer * renderer, const char* file);

//Applying textures
	playerShip = spriteObject(pRenderer, "../Assets/PNG/player.png", NULL);
	playerProjectile = spriteObject(pRenderer, "../Assets/PNG/Lasers/laserRed01.png", NULL);
	playerHit = spriteObject(pRenderer, "../Assets/PNG/laserRedShot.png", NULL);
	enemyShip = spriteObject(pRenderer, "../Assets/PNG/Enemies/enemyBlue2.png", NULL);
	enemyProjectiles = spriteObject(pRenderer, "../Assets/PNG/Lasers/laserBlue01.png", 180);
	bossSprite = spriteObject(pRenderer, "../Assets/PNG/Ships/spaceShips_005.png", NULL);
	bossProjectiles = spriteObject(pRenderer, "../Assets/PNG/Missiles/spaceMissiles_001.png", 180);
	astroid_1 = spriteObject(pRenderer, "../Assets/PNG/Meteors/meteorBrown_big4.png", 0);
	backGround_1 = spriteObject(pRenderer, "../Assets/PNG/Background/starBackground.png", NULL);

	powerUp_1 = spriteObject(pRenderer, "../Assets/PNG/Power-ups/powerupBlue_bolt.png", NULL);
	powerUp_2 = spriteObject(pRenderer, "../Assets/PNG/Power-ups/powerupBlue.png", NULL);
	powerUp_3 = spriteObject(pRenderer, "../Assets/PNG/Power-ups/powerupBlue_shield.png", NULL);
	powerUp_4 = spriteObject(pRenderer, "../Assets/PNG/Power-ups/powerupBlue_star.png", NULL);
	playerShield = spriteObject(pRenderer, "../Assets/PNG/shield.png", NULL);

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
		float bossMissleHeight = bossProjectiles.src.h * 1.5;
		float bossMissleWidth = bossProjectiles.src.w * 1.5;
		//Player Projectiles
		int playerLaserHeight = playerProjectile.src.h;
		int playerLaserWidth = playerProjectile.src.w;
		//Enemy Projectiles
		int enemyLaserHeight = enemyProjectiles.src.h;
		int enemyLaserWidth = enemyProjectiles.src.w;
		
		//Power Up 1
		int powerUpHeight_1 = powerUp_1.src.h;
		int powerUpWidth_1 = powerUp_1.src.w;
		//Power Up 2
		int powerUpHeight_2 = powerUp_2.src.h;
		int powerUpWidth_2 = powerUp_2.src.w;
		//Power Up 3
		int powerUpHeight_3 = powerUp_3.src.h;
		int powerUpWidth_3 = powerUp_3.src.w;
		//Power Up 4
		int powerUpHeight_4 = powerUp_4.src.h;
		int powerUpWidth_4 = powerUp_4.src.w;
		
		//Player sheild
		int playerShieldHeight = playerShield.src.h;
		int playerShieldWidth = playerShield.src.w;
	
	//Screen Positions
		//Player Ship
	playerShip.dst.x = (SCREEN_WIDTH * .5) - (playerWidth / 2);
	playerShip.dst.y = (SCREEN_HEIGHT * .9);
	playerShip.dst.w = playerWidth;
	playerShip.dst.h = playerHeight;
	//Player Projectile
	playerProjectile.dst.x = playerShip.dst.x + (playerWidth / 2) - (playerLaserWidth / 2);
	playerProjectile.dst.y = playerShip.dst.y - (playerHeight);
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
	bossSprite.dst.y = (SCREEN_HEIGHT * .25) - bossHeight / 2;
	bossSprite.dst.h = bossHeight;
	bossSprite.dst.w = bossWidth;
	//Boss Projectile Position
	bossProjectiles.dst.x = bossSprite.dst.x + (bossWidth / 2) - (bossMissleWidth / 2);
	bossProjectiles.dst.y = bossSprite.dst.y + bossHeight;
	bossProjectiles.dst.h = bossMissleHeight;
	bossProjectiles.dst.w = bossMissleWidth;
	//Astroid Position
	astroid_1.dst.x = SCREEN_WIDTH * .5 - (astroidWidth / 2);
	astroid_1.dst.y = SCREEN_HEIGHT * .5;
	astroid_1.dst.w = astroidWidth;
	astroid_1.dst.h = astroidHeight;
	//Background
	backGround_1.dst.x = (SCREEN_WIDTH * 0);
	backGround_1.dst.y = (SCREEN_HEIGHT * 0);
	backGround_1.dst.w = SCREEN_WIDTH;
	backGround_1.dst.h = SCREEN_HEIGHT;



	//Player Shield. 
	playerShield.dst.x = playerShip.dst.x - ((playerShield.src.w - playerShip.src.w) / 2);
	playerShield.dst.y = playerShip.dst.y - ((playerShield.src.h - playerShip.src.h) / 2);
	playerShield.dst.w = playerShieldWidth;
	playerShield.dst.h = playerShieldHeight;

	//Power Up 1
	powerUp_1.dst.y = playerShield.dst.y;
	powerUp_1.dst.x = playerShield.dst.x + playerShield.src.w;
	//Power Up 2
	powerUp_2.dst.y = powerUp_1.dst.y;
	powerUp_2.dst.x = powerUp_1.dst.x + powerUp_1.src.w;
	//Power Up 2
	powerUp_3.dst.y = powerUp_2.dst.y;
	powerUp_3.dst.x = powerUp_2.dst.x + powerUp_1.src.w;
	//Power Up 2
	powerUp_4.dst.y = powerUp_3.dst.y;
	powerUp_4.dst.x = powerUp_3.dst.x + powerUp_1.src.w;


}

void GameFund::draw() {
	SDL_RenderClear(pRenderer);
	//This is where you add stuff to Render
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




	powerUp_1.draw(pRenderer);
	powerUp_2.draw(pRenderer);
	powerUp_3.draw(pRenderer);
	powerUp_4.draw(pRenderer);
	playerShield.draw(pRenderer);

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

