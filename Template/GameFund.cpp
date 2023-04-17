#include <SDL_ttf.h>
#include "GameFund.h"

Mix_Chunk* sfxShoot;
Mix_Chunk* sfxShoot2;
Mix_Chunk* sfxHit1;
Mix_Chunk* sfxHit2;
Mix_Chunk* sfxShoot3;
Mix_Chunk* musicBoss;

Mix_Chunk* playerDied;

Mix_Music* music;

bool upMove = false;
bool downMove = false;
bool leftMove = false;
bool rightMove = false;
bool shooting = false;
bool endCondition = false;
bool animation_done = false;
bool turnOff;
bool restartSwitch = false;
bool muteShots;


int volumeFX = MIX_MAX_VOLUME * .2;
int musicVol = MIX_MAX_VOLUME * .1;

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
float enemySpawnDelay = 1.5f;
struct Timer
{
	float elapsed = 0.0f;
	float duration = 0.0f;
	bool Expired() { return elapsed >= duration; }
	void Reset() { elapsed = 0.0f; }
	void Tick(float dt) { elapsed += dt; }
};
namespace Fund
{

	class Sprite
	{
	private:
		SDL_Rect src, dst;

	public:
		SDL_Texture* tTexture;
		float animationCurrentFrame = 0.0f;
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
			tTexture = nullptr;
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
		Sprite(TTF_Font* uiFont, const char* scoreString, SDL_Color color) : Sprite()
		{


			SDL_Surface* surface = TTF_RenderText_Solid(uiFont, scoreString, color);
			if (surface == NULL)
			{
				cout << "Surface Failed to Load\n";
			}
			tTexture = SDL_CreateTextureFromSurface(GameFund::pRenderer, surface);
			if (tTexture == NULL)
			{
				cout << "tTex failed to load\n";
			}
			SDL_FreeSurface(surface);
			TTF_SizeText(uiFont, scoreString, &dst.w, &dst.h);
			src.w = dst.w;
			src.h = dst.h;

		}
		~Sprite()
		{
		//	SDL_DestroyTexture(pTex);
		}

		void draw()
		{
			dst.x = position.x;
			dst.y = position.y;

			textFund::draw(pTex, src, dst,rotation);
		}

		void drawText()
		{
			dst.x = position.x;
			dst.y = position.y;

			textFund::draw(tTexture, src, dst, rotation);
		}
		void nextFrame()
		{
			setFrame(animationCurrentFrame + 1);
		}

		void setFrame(int frame)
		{
			animationCurrentFrame = frame % animationFrameCount;

			int row = frame / 8;
			int col = frame % 8;

			src.y = row * src.h;
			src.x = col * src.w;

		}

		void addFrameTime(float timeScale)
		{
			animationCurrentFrame += timeScale;
			if (animationCurrentFrame >= animationFrameCount)
			{
				animationCurrentFrame -= animationFrameCount;
			}
		}

		void animate(int loops)
		{
			int iterations = 0;

			while (iterations < loops)
			{
				nextFrame();
				draw();
			if (animationCurrentFrame == animationFrameCount)
			{
				animationCurrentFrame = 0;
				iterations++;
			}
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
		float fireRepeatDelay = 0.3f;
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
Fund::Sprite explosion1;
Fund::Sprite explosion2;
Fund::Sprite explosion3;
Fund::Sprite explosion4;
Fund::Sprite explosion5;

Fund::Sprite backgroundNeb;
Fund::Sprite backgroundWet1;
Fund::Sprite backgroundWet2;
Fund::Sprite backgroundDry1;
Fund::Sprite backgroundDry2;




vector<Fund::Ship> enemies;
vector<Fund::Bullet> eBullets;
vector<Fund::Bullet> bullets;

vector<Fund::Sprite> explosions;

//UI
TTF_Font* uiFont;
int score = 0;
Fund::Sprite uiSpriteScore;

Fund::Sprite life;
vector<Fund::Sprite> lives;

Timer restartTimer;


SDL_Renderer* GameFund::pRenderer = nullptr;
bool playedOnce = false;


//Loading Our Lives
void loadLives()
{
	life = Fund::Sprite("../Assets/spaceGame/life.png");
	life.position.x = 10;
	life.position.y = 10;
	lives.clear();
	for (int i = 0; i < 3; i++) {
		lives.push_back(life);
	}
	lives[0].position.x = 10;
	lives[1].position.x = lives[0].position.x + lives[0].getSize().x;
	lives[2].position.x = lives[1].position.x + lives[0].getSize().x;

}
//Init Volume
void start()
{
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(musicVol);
	Mix_Volume(-1, volumeFX);
	Mix_VolumeChunk(sfxHit1, MIX_MAX_VOLUME);
	Mix_VolumeChunk(sfxHit2, MIX_MAX_VOLUME);
}

void addScore()
{
	score += 1;
}

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
	if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, COUNT, chunkSize) != 0) {
		cout << "Audio Bad\n";
	}
	else cout << "Audio Good\n";

	if (TTF_Init() != 0)
	{
		cout << "TTF Init Failed\n" << SDL_GetError << endl;
	}



}

bool GameFund::canSpawn()
{
	if (endCondition == false && enemySpawnTimer <= 0)
	{
		enemySpawnTimer = enemySpawnRate;
		return true;
	}

	else
	{
		enemySpawnTimer -= deltaTime;
		return false;
	}

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
	enemy1.fireRepeatDelay = 1.5;
	enemy1.moveSpeedPx = 80;

	enemies.push_back(enemy1);
	enemySpawnTimer = enemySpawnDelay;

}
//When we restart
void restart()
{
	score = 0;
	enemies.clear();
	eBullets.clear();
	bullets.clear();
	explosions.clear();
	Mix_VolumeChunk(sfxShoot3, 64);
	Mix_VolumeChunk(sfxShoot, 64);
	player.sprite.position.x = (896 / 2) - (player.sprite.getSize().x / 2);
	player.sprite.position.y = 1024 * .75;
	loadLives();
	endCondition = false;
	restartSwitch = false;
}

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
				//Animate Left and Right
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
			case(SDL_SCANCODE_PAGEUP):
				musicVol = min(musicVol + 10, MIX_MAX_VOLUME);
				Mix_VolumeMusic(musicVol);
				break;
			case(SDL_SCANCODE_PAGEDOWN):
				musicVol = max(musicVol - 10, 0);
				Mix_VolumeMusic(musicVol);
				break;
			case (SDL_SCANCODE_EQUALS):
				volumeFX = min(volumeFX + 10, MIX_MAX_VOLUME);
				cout << volumeFX << endl;
				Mix_Volume(-1, volumeFX);
				break;
			case (SDL_SCANCODE_MINUS):
				volumeFX = max(volumeFX - 10, 0);
				cout << volumeFX << endl;
				Mix_Volume(-1, volumeFX);
				break;
			case (SDL_SCANCODE_B):
				turnOff = true;
				break;
			case(SDL_SCANCODE_N):
				turnOff = false;
				break;
			case(SDL_SCANCODE_Z):
				restartSwitch = true;
			case(SDL_SCANCODE_1):
				muteShots = true;
				break;
			case(SDL_SCANCODE_2):
				muteShots = false;
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
	if (player.sprite.position.x >= 896)
	{
		player.sprite.position.x = 0 - player.sprite.getSize().x;
	}
	if (player.sprite.position.x <= 0 - player.sprite.getSize().x-1) {
		player.sprite.position.x = 896;
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
		Mix_PlayChannel(-1, sfxShoot, 0);
	}

	player.move(inputVec);
	player.update();
}
void GameFund::update()
{
	bool masterKey = true;
	updatePlayer();
	if (restartSwitch)
	{
		restart();
	}
	if (!turnOff)
	{
		if (muteShots)
		{
			Mix_VolumeChunk(sfxShoot, 0);
			Mix_VolumeChunk(sfxShoot3, 0);
		}
		else if (!muteShots)
		{
			Mix_VolumeChunk(sfxShoot, volumeFX);
			Mix_VolumeChunk(sfxShoot3, volumeFX);

		}
	}
	 else if (turnOff)
	{
		loadLives();
		score = 0;
		masterKey = false;
		eBullets.clear();
		explosions.clear();
		enemies.clear();
	}
		float backgroundNebSS = 150;
		float backgroundWetSS = 20;
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
				enemy.Shoot(eBullets, velocity, "../Assets/PNG/laserGreen.png");
				Mix_PlayChannel(-1, sfxShoot3, 0);

			}
		}

		if (canSpawn()&&masterKey)
		{
			spawnShip();
		}



		detectCollisions();



		//While we are dead #1
		if (lives.empty())
		{


			restartTimer.Tick(deltaTime);

			player.sprite.position.x = -1000;
			endCondition = true;
			eBullets.clear();
			Mix_VolumeChunk(sfxShoot3, 0);
			Mix_VolumeChunk(sfxShoot, 0);

			restartTimer.duration = 6;
			if (restartTimer.Expired())
			{
				restartTimer.Reset();
				restart();


			}

		}
	}
	

void GameFund::detectCollisions()
{
	int exType = 0;
	exType = rand() % 4;
	int exSoundType = 0;
	exSoundType = rand() % 2;
	//Enemy Bullets to Player
	for (std::vector<Fund::Bullet>::iterator it = eBullets.begin(); it != eBullets.end();)
	{
		Fund::Sprite& enemyBullet = it->sprite;
		if (Fund::areSpritesOverLapping(player.sprite, enemyBullet))
		{

			//Removing Lives
			lives.pop_back();


			if (lives.empty())
			{
				//Setting player explosion
				explosion5.setFrame(0);
				Mix_PlayChannel(-1, playerDied, 0);
				explosion5.position.x = player.sprite.position.x - (explosion5.getSize().x / 2) + 45;
				explosion5.position.y = player.sprite.position.y - (explosion5.getSize().y / 2) + 30;
			}


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

					if (enemyIterator->sprite.position.y >= 1024)
			{
				enemyIterator = enemies.erase(enemyIterator);
				if (enemyIterator == enemies.end()) break;
			}


				if (bulletIterator->sprite.position.y <= 1) {
					bulletIterator = bullets.erase(bulletIterator);
					if (bulletIterator == bullets.end()) { break; }
				}
			if (Fund::areSpritesOverLapping(bulletIterator->sprite, enemyIterator->sprite))
			{
				//Adding Score Count
				addScore();

				//Random Explo
				switch (exType)
				{
				case (0):
					explosion1.position.x = enemyIterator->sprite.position.x- (enemyIterator->sprite.getSize().x/2);
					explosion1.position.y = enemyIterator->sprite.position.y - (enemyIterator->sprite.getSize().y / 2)-10;
					explosion1.animationCurrentFrame = 0;
					explosions.push_back(explosion1);
					Mix_PlayChannel(-1, sfxHit1, 0);

					break;
				case (1):
					explosion2.position.x = enemyIterator->sprite.position.x - (enemyIterator->sprite.getSize().x / 2);
					explosion2.position.y = enemyIterator->sprite.position.y - (enemyIterator->sprite.getSize().y / 2) - 10;
					explosion2.animationCurrentFrame = 0;
					explosions.push_back(explosion2);
					Mix_PlayChannel(-1, sfxHit1, 0);

					break;
				case (2):
					explosion3.position.x = enemyIterator->sprite.position.x - (enemyIterator->sprite.getSize().x / 2);
					explosion3.position.y = enemyIterator->sprite.position.y - (enemyIterator->sprite.getSize().y / 2) - 10;
					explosion3.animationCurrentFrame = 0;
					explosions.push_back(explosion3);
					Mix_PlayChannel(-1, sfxHit2, 0);

					break;
				case (3):
					explosion4.position.x = enemyIterator->sprite.position.x - (enemyIterator->sprite.getSize().x / 2);
					explosion4.position.y = enemyIterator->sprite.position.y - (enemyIterator->sprite.getSize().y / 2) - 10;
					explosion4.animationCurrentFrame = 0;
					explosions.push_back(explosion4);
					Mix_PlayChannel(-1, sfxHit2, 0);
					break;
				}

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

Mix_Chunk* loadSound(const char* filepath)
{
	Mix_Chunk* sound = Mix_LoadWAV(filepath);
	if (sound == NULL) {
		cout << "Sound Failed to Load" << filepath << endl;
	}
	return sound;
}





void GameFund::load() 
{

	sfxShoot = loadSound("../Assets/spaceGame/weaponfire6.wav");
	sfxShoot2 = loadSound("../Assets/spaceGame/laserSmall_000.ogg");
	sfxShoot3 = loadSound("../Assets/spaceGame/laserSmall_002.ogg");
	playerDied = loadSound("../Assets/spaceGame/explosion09.wav");


	sfxHit1 = loadSound("../Assets/spaceGame/lowFrequency_explosion_000.ogg");
	sfxHit2 = loadSound("../Assets/spaceGame/lowFrequency_explosion_001.ogg");
	musicBoss = loadSound("../Assets/spaceGame/spaceShip.wav");
	music = Mix_LoadMUS("../Assets/spaceGame/ObservingTheStar.ogg");

	uiFont = TTF_OpenFont("../Assets/fonts/lazy.ttf", 36);
	if (uiFont == NULL)
	{
		cout << "Font Failed to Load\n";
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

	explosion1 = Fund::Sprite(512, 512, 64, "../Assets/bigBooms/1.png");
	explosion1.setSize(160, 160);

	explosion2 = Fund::Sprite(512, 512, 64, "../Assets/bigBooms/2.png");
	explosion2.setSize(160, 160);

	explosion3 = Fund::Sprite(512, 512, 64, "../Assets/bigBooms/3.png");
	explosion3.setSize(160, 160);

	explosion4 = Fund::Sprite(512, 512, 64, "../Assets/bigBooms/4.png");
	explosion4.setSize(160, 160);

	explosion5 = Fund::Sprite(512, 512, 64, "../Assets/spaceGame/explosion5.png");
	explosion5.setSize(512, 512);


	
	
	player.sprite.position.x = (896/2) - (player.sprite.getSize().x/2);
	player.sprite.position.y = 1024 * .75;

	loadLives();
	start();
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

		//for (auto explosionIT = explosions.begin(); explosionIT != explosions.end();)
		//{
		//	Fund::Sprite& explosion = *explosionIT;
		//	explosionIT->nextFrame();
		//
		//	if (explosionIT->animationCurrentFrame == explosionIT->animationFrameCount-1)
		//	{
		//		explosionIT = explosions.erase(explosionIT);
		//	}
		//	explosionIT->draw();
		//}

		//Drawing Explosions
		for (auto& e : explosions)
		{
			
			if (e.animationCurrentFrame == e.animationFrameCount -1)
			{
				e.position.x = -500;
			}
			e.nextFrame();
			e.draw();
		}
		
		//Drawing player explosion
		if (lives.empty())
		{
			if (explosion5.animationCurrentFrame == explosion5.animationFrameCount-1)
			{
				explosion5.position.x = -1000;
			}
			explosion5.nextFrame();
			explosion5.draw();
		}

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
	//UI

	for (int i = 0; i < lives.size(); i++)
	{
		lives[i].draw();
	}

	//TTF_RenderText takes in a const char as a argument. But we have a string, need to convert String to const char*. Can do this with string.c_str()
	
	//Typing to screen
	SDL_Color color = { 255,255,255,255 };
	std::string scoreString = "Score: " + to_string(score);
	uiSpriteScore = Fund::Sprite(uiFont, scoreString.c_str(), color);


	uiSpriteScore.position.x = (896/2) - uiSpriteScore.getSize().x / 2;
	uiSpriteScore.position.y = (1024 * .05);



	uiSpriteScore.drawText();



	SDL_RenderPresent(pRenderer);
}



bool GameFund::running() {
	return isRunning;
}

void GameFund::clean() {
	Mix_FreeChunk(sfxShoot);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	TTF_Quit;

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit;


}
