
#include "GameFund.h"


enum audioChan
{
	SHOOT,
	UI,
	GEN1,
	GEN2,
	GEN3,
	COUNT,
};

float enemySpawnTimer = 0.0f;
float enemySpawnDelay = 1.0f;

namespace Fund
{

	class Sprite
	{
	private:
		SDL_Rect src, dst;

		float animationCurrentFrame = 0.0f;
	public:
		SDL_Texture* pTex;
		double rotation = 0;
		SDL_RendererFlip flipState = SDL_FLIP_NONE;
		Vec2 position;
		int animationFrameCount = 0;

		//Setters
		void setSize(Vec2 sizeWidthHeight)
		{
			dst.w = sizeWidthHeight.x;
			dst.h = sizeWidthHeight.y;
		}

		void setSize(int w, int h)
		{
			dst.w = w;
			dst.h = h;
		}
		//Getters
		SDL_Rect getRect() const
		{
			SDL_Rect returnValue = dst;
			returnValue.x = position.x;
			returnValue.y = position.y;
			return dst;
		}

		Vec2 getSize() const
		{
			Vec2 returnVec = { dst.w,dst.h };
			return returnVec;
		}

		void setSpruteSheet(int width, int height)
		{
			src.w = width;
			src.h = height;
		}
		//Default constructor
		Sprite()
		{
			pTex = nullptr;
			src = {};
			dst = {};
		}

		Sprite(const char* filepath)
		{
			
			src = {};
			pTex = textFund::loadTexture(filepath, rotation);
			SDL_QueryTexture(pTex, NULL, NULL, &src.w, &src.h);
			dst = SDL_Rect{ 0,0,src.w,src.h };
		}
		//Animation Constructor and Filepath Constructor
		Sprite(int frameSizex, int frameSizeY, int frameCount, const char* filepath) : Sprite(filepath)
		{
			cout << "Animation Constructor\n";
			setSpruteSheet(frameSizex, frameSizeY);
			//setSize(frameSizex, frameSizeY);
			animationFrameCount = frameCount;
		}

		void draw()
		{
			dst.x = position.x;
			dst.y = position.y;
			src.x = src.w * (int)animationCurrentFrame;
			
			textFund::draw(pTex, src, dst,rotation);
		}
		void nextFrame()
		{
			setFrame(animationCurrentFrame + 1);
		}

		void setFrame(int frame)
		{
			animationCurrentFrame = frame % animationFrameCount;
			src.x = src.w * animationCurrentFrame;
			

		}

		void addFrameTime(float timeScale)
		{
			animationCurrentFrame += timeScale;
			if (animationCurrentFrame >= animationFrameCount)
			{
				animationCurrentFrame -= animationFrameCount;
			}
		}
	};//Class Sprite

	class Bullet
	{
	public:
		Sprite sprite;
		Vec2 velocity;
		void update()
		{
			sprite.position.x += velocity.x * deltaTime;
			sprite.position.y += velocity.y * deltaTime;
		}
	};


	class Ship
	{
	public:
		Sprite sprite;
		float moveSpeedPx = 150;
		float fireRepeatDelay = 0.5f;
	private:
		float fireRepeatTimer;
	public:
		void move(Vec2 input)
		{
			sprite.position.x += input.x * (moveSpeedPx * deltaTime);
			sprite.position.y += input.y * (moveSpeedPx * deltaTime);
		}

		void Shoot(std::vector<Bullet>& container, Vec2 velocity, const char* filepath)
		{
			//Bullet Creation
			Sprite bulletSprite = Sprite(filepath);

			//Set Bullet at playerLocation
			bulletSprite.position.x = sprite.position.x + (sprite.getSize().x/2) - (bulletSprite.getSize().x/2);
			bulletSprite.position.y = sprite.position.y;

			bulletSprite.setSize(bulletSprite.getSize().x * .75, bulletSprite.getSize().y * .75);

			Bullet bullet;
			bullet.sprite = bulletSprite;
			bullet.velocity = velocity;

			container.push_back(bullet);

			fireRepeatTimer = fireRepeatDelay;
		}

		void update()
		{
			fireRepeatTimer -= deltaTime;
		}

		bool canShoot()
		{
			if (fireRepeatTimer <= 0.0f && sprite.position.y >= 0)
			{
				return true;
			}
			else return false;
		}
	};

	//AABB collision

	bool areSpritesOverLapping(const Sprite& A, const Sprite& B)
	{
		int minAx, maxAx, minBx, maxBx;
		int minAy, maxAy, minBy, maxBy;

		SDL_Rect boundsA = A.getRect();
		SDL_Rect boundsB = B.getRect();

		SDL_bool isColliding = SDL_HasIntersection(&boundsA, &boundsB);
		return (bool)isColliding;
	}
};

Fund::Ship player;
Fund::Sprite backgroundNeb;
Fund::Sprite backgroundWet1;
Fund::Sprite backgroundWet2;
Fund::Sprite backgroundDry1;
Fund::Sprite backgroundDry2;


Mix_Chunk* shoot;
Mix_Music* music;

vector<Fund::Ship> enemies;
vector<Fund::Bullet> eBullets;
vector<Fund::Bullet> bullets;
vector<Fund::Sprite> mapItems;



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

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

	if (pRenderer) {
		std::cout << "Render Good " << std::endl;
		isRunning = true;
	}
	else {
		std::cout << "Render Bad\n";
		isRunning = false;
	}
	const int chunkSize = 1024;
	const int frequency = 22050;
	//if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, COUNT, chunkSize) != 0) {
	//	cout << "Audio Bad\n";
	//}
	//else cout << "Audio Good\n";
}

bool GameFund::canSpawn()
{
	return false;
}

void GameFund::spawnShip()
{
	Fund::Sprite enemy;
	enemy = Fund::Sprite("../Assets/PNG/enemyShip.png");
	enemy.setSize(enemy.getSize().x * .75, enemy.getSize().y * .75);
	enemy.position.x = rand() % 786;
	enemy.position.y = rand() % 150 * -1;
	Fund::Ship enemy1;
	enemy1.sprite = enemy;
	enemy1.fireRepeatDelay = 2.0;
	enemy1.moveSpeedPx = 80;

	enemies.push_back(enemy1);
	enemySpawnTimer = enemySpawnDelay;

}

bool upMove = false;
bool downMove = false;
bool leftMove = false;
bool rightMove = false;
bool shooting = false;

void GameFund::input() {
	SDL_Event pEvent;
	while (SDL_PollEvent(&pEvent)) {
		switch (pEvent.type)
		{
		case (SDL_KEYDOWN):
		{
			SDL_Scancode key = pEvent.key.keysym.scancode;
			switch (key)
			{
			case(SDL_SCANCODE_W):
				upMove = true;
				break;
			case(SDL_SCANCODE_S):
				downMove = true;
				break;
			case(SDL_SCANCODE_A):
				player.sprite.pTex = textFund::loadTexture("../Assets/PNG/playerLeft.png",NULL);
				leftMove = true;
				break;
			case(SDL_SCANCODE_D):
				player.sprite.pTex = textFund::loadTexture("../Assets/PNG/playerRight.png",NULL);
				rightMove = true;
				break;
			case(SDL_SCANCODE_SPACE):
				shooting = true;
				break;
			case(SDL_SCANCODE_PAGEDOWN):


				break;
			}
			break;
		}
		
			case (SDL_KEYUP):
			{
				SDL_Scancode key = pEvent.key.keysym.scancode;
				switch (key)
				{
				case(SDL_SCANCODE_W):
					upMove = false;
					break;
				case(SDL_SCANCODE_S):
					downMove = false;
					break;
				case(SDL_SCANCODE_A):
				player.sprite.pTex = textFund::loadTexture("../Assets/PNG/player.png",NULL);
					leftMove = false;
					break;
				case(SDL_SCANCODE_D):
				player.sprite.pTex = textFund::loadTexture("../Assets/PNG/player.png",NULL);
					rightMove = false;
					break;
				case(SDL_SCANCODE_SPACE):
					shooting = false;
					break;
				}
				}
			}
		}

	}

void GameFund::updatePlayer()
{
	Vec2 inputVec;
	if (upMove) { inputVec.y = -1; }
	if (downMove) { inputVec.y = 1; }
	if (leftMove) { inputVec.x = -1; }
	if (rightMove) { inputVec.x = 1; }

	//Preventing From exiting Box
	if (player.sprite.position.x >= 896 - player.sprite.getSize().x - 10)
	{
		player.sprite.position.x = 896 - player.sprite.getSize().x - 10;
	}
	if (player.sprite.position.x <= 0 + 10) {
		player.sprite.position.x = 10;
	}
	if (player.sprite.position.y >= 1024 - player.sprite.getSize().y - 10)
	{
		player.sprite.position.y = 1024 - player.sprite.getSize().y - 11;
	}
	if (player.sprite.position.y <= 0 + 10) { player.sprite.position.y = 0 + 10; }

	if (shooting && player.canShoot())
	{
		Vec2 velocity = { 0,-600 };
		player.Shoot(bullets, velocity, "../Assets/PNG/laserRed.png");
	}

	player.move(inputVec);
	player.update();
}
void GameFund::update()
{
	updatePlayer();

	float backgroundNebSS = 150;
	float backgroundWetSS = 10;
	float backgroundDry1SS = 60;
	//Update Map
	backgroundNeb.position.y += backgroundNebSS * deltaTime;


	backgroundWet1.position.y += backgroundWetSS * deltaTime;
	backgroundWet2.position.y += backgroundWetSS * deltaTime;

	backgroundDry1.position.y += backgroundDry1SS * deltaTime;
	backgroundDry2.position.y += backgroundDry1SS * deltaTime;
	if (backgroundNeb.position.y >= 1024)
	{

		backgroundNeb.position.y = -backgroundNeb.getSize().y;
		backgroundNeb.nextFrame();

	}


	if (backgroundWet1.position.y >= 1024)
	{
		backgroundWet1.position.y = backgroundWet2.position.y - backgroundWet1.getSize().y;
	}
	if (backgroundWet2.position.y >= 1024)
	{
		backgroundWet2.position.y = backgroundWet1.position.y - backgroundWet1.getSize().y;
	}

	if (backgroundDry1.position.y >= 1024)
	{
		backgroundDry1.position.y = backgroundDry2.position.y - backgroundDry1.getSize().y;
	}
	if (backgroundDry2.position.y >= 1024)
	{
		backgroundDry2.position.y = backgroundDry1.position.y - backgroundDry2.getSize().y;
	}



	//Update player bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		//To access elements of an array, we use the array access operator []
		bullets[i].update();
	}

	//Update enemy bullets
	for (int i = 0; i < eBullets.size(); i++)
	{
		eBullets[i].update();
	}

	//Update enemy ships
	for (int i = 0; i < enemies.size(); i++)
	{
		//Get reference to enemy at index i (& makes it a reference variable)
		Fund::Ship& enemy = enemies[i];

		enemy.move({ 0, 1 });
		enemy.update();
		if (enemy.canShoot())
		{
			bool towardRight = false;
			Vec2 velocity = { 0, 250 };
			enemy.Shoot(eBullets, velocity,"../Assets/PNG/laserGreen.png");
		}
	}



	//Spawn enemies on timer and update timer
	if (enemySpawnTimer <= 0)
	{
		spawnShip();
	}
	else
	{
		enemySpawnTimer -= deltaTime;
	}
	
	detectCollisions();
}
void GameFund::detectCollisions()
{
	//Enemy Bullets to Player
	for (std::vector<Fund::Bullet>::iterator it = eBullets.begin(); it != eBullets.end();)
	{
		Fund::Sprite& enemyBullet = it->sprite;
		if (Fund::areSpritesOverLapping(player.sprite, enemyBullet))
		{
			cout << "Player was hit!\n";
			player.sprite.rotation += 90;


			it = eBullets.erase(it);
		}
		if (it != eBullets.end()) it++;
	}

	//Player Bullets to enemy Ships
	for (std::vector<Fund::Bullet>::iterator bulletIterator = bullets.begin(); bulletIterator != bullets.end();)
	{
		//For every enemy sprite...
		for (auto enemyIterator = enemies.begin(); enemyIterator != enemies.end();)
		{
		std::vector<Fund::Bullet>::iterator bulletIT = bulletIterator;
			//Test for collision between player bullet and enemy
			if (Fund::areSpritesOverLapping(bulletIterator->sprite, enemyIterator->sprite))
			{
				//Destroy bullet
				bulletIterator = bullets.erase(bulletIterator);
				//Destroy enemy
				enemyIterator = enemies.erase(enemyIterator);

				if (bulletIterator == bullets.end()) { break; }

				//If we destroy the last object in one of the containers, then stop comparing.
					//break; // leave the for loop
			}

			
			if (enemyIterator != enemies.end()) enemyIterator++;
		}
		if (bulletIterator != bullets.end()) bulletIterator++; // as long as we are not at the end, then increment our iterator
	}


}
void GameFund::load() {

	music = Mix_LoadMUS("../Assets/audio/Mutara.mp3");
	shoot = Mix_LoadWAV("../Assets/bonus/sfx_laser2.ogg");
	if (music == NULL) {
		cout << "Music Failed to load\n";
	}if (shoot == NULL) {
		cout << "Shoot Failed to load\n";
	}


	backgroundNeb = Fund::Sprite(1060, 1748, 2, "../Assets/Backgrounds/nebula2.png");
	backgroundNeb.setSize(896, 1024);
	backgroundNeb.position.y = -backgroundNeb.getSize().y+1;

	backgroundWet1 = Fund::Sprite("../Assets/Backgrounds/nebulawetstars.png");
	backgroundWet1.setSize(896, 1024);
	backgroundWet2 = Fund::Sprite("../Assets/Backgrounds/nebulawetstars.png");
	backgroundWet2.setSize(896, 1024);
	backgroundWet2.position.y = -backgroundWet2.getSize().y;
	
	backgroundDry1 = Fund::Sprite("../Assets/Backgrounds/nebuladrystars.png");
	backgroundDry1.setSize(896, 1024);
	backgroundDry1.position.y = 500;
	backgroundDry2 = Fund::Sprite("../Assets/Backgrounds/nebuladrystars.png");
	backgroundDry2.setSize(896, 1024);
	backgroundDry2.position.y = backgroundDry1.position.y - backgroundDry2.getSize().y;

	player.sprite = Fund::Sprite("../Assets/PNG/player.png");
	player.sprite.setSize(player.sprite.getSize().x * .75, player.sprite.getSize().y * .75);

	
	
	player.sprite.position.x = 250;
	player.sprite.position.y = 250;

}

void GameFund::start()
{
	Mix_PlayMusic(music,-1);
}

void GameFund::draw() {
	SDL_RenderClear(pRenderer);
	//First Layer Background
		backgroundWet1.draw();
		backgroundWet2.draw();
	//Second Layer Background
		backgroundDry1.draw();
		backgroundDry2.draw();

	//Third Layer Background
		backgroundNeb.draw();


	//Drawing Player
	player.sprite.draw();

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].sprite.draw();
	}
	
	//Draw ALL enemy bullets on screen
	for (int i = 0; i < eBullets.size(); i++)
	{
		eBullets[i].sprite.draw();
	}
	
	//Draw ALL enemy Ships on screen
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].sprite.draw();
	}


	SDL_RenderPresent(pRenderer);
}



bool GameFund::running() {
	return isRunning;
}

void GameFund::clean() {
	Mix_FreeChunk(shoot);
	Mix_FreeMusic(music);
	Mix_CloseAudio();

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit;


}
