// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>
#include <SDL.h> // Allows us to use features from the SDL Library
#include <SDL_Image.h>
#include <vector> //std::vector is an array with variable size

/*
 Lab 11 (week 12)
1. Add a function to detect when two objects overlap using AABB collision detection
2. Loop through every object to determine which objects are colliding with each other
For part 1. We do not need anything beyond the Sprite class
For part 2. Ideally, to be fully prepared for this lab we have containers of enemies, enemy bullets, and player bullets
AABB collision detection:
1. For each rectangle, find their minimum and maximum coordinates in one axis (e.g. x)
	This represents their "projection" onto the axis. It's like the shadow they would cast on that axis.
	1.a.Then we ask: Do they overlap?
		1.a.i. Is the maximum of one less than the minimum of the other?... and more questions like that...
*/

//All these variables are considered "Global variables" which can be accessed from any Function.
constexpr float FPS = 60.0f;
constexpr float DELAY_TIME = 1000.0f / FPS; // target deltaTime in ms
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

//At 60FPS, how much time passes each frame?
//60 frames per second. Every second, we pass 60 frames
//How many seconds pass for each frame?
float deltaTime = 1.0f / FPS; // time passing between frames in seconds

SDL_Window* pWindow = nullptr; //This is a pointer to SDL_Window. It stores a memory location which we can use later
SDL_Renderer* pRenderer = nullptr;
bool isGameRunning = true;


//To be used in our enemy spawning code
float enemySpawnDelay = 1.0f;
float enemySpawnTimer = 0.0f;

namespace Fund
{
	struct Vec2 // This struct represents a 2-dimensional vector
	{
		float x = 0;
		float y = 0;
	};

	//Declaring a struct or class declares a new type of object we can make. After this is declared, we can make Sprite variables that
	//have all of the contained data fields, and functions
	struct Sprite
	{
	private: //private fields cannot be accessed outside the struct or class

		SDL_Texture* pTexture;
		SDL_Rect src;
		SDL_Rect dst;
		//	int animationCurrentFrame = 0;
		//	float animationTime01 = 0.0f;//0 is frame 0, 1 is frameCount, multiply by frameCount to get currentFrame e.g. 0 * frameCount = 0. 1 * frameCount = 5 //Option A

		float animationCurrentFrame = 0.0f; // same as storing which frame, but must be converted back to int to draw (e.g. frame 3.4 becomes frame 3) // Option B

	public: //public fields can be accessed from outside the struct or class
		double rotation = 0;
		SDL_RendererFlip flipState = SDL_FLIP_NONE;
		Vec2 position; // position of the sprite on the screen
		int animationFrameCount = 1;

		//Getter and setter functions
		//Functions which change the state of a struct or class are sometimes called Mutators, or setters
		void SetSize(Vec2 sizeWidthHeight)
		{
			dst.w = sizeWidthHeight.x;
			dst.h = sizeWidthHeight.y;
		}

		//This and the other SetSize have the exact same name, but take different data. The correct one will be chosen by the compiler based on what parameters you put in it
		void SetSize(int w, int h)
		{
			dst.w = w;
			dst.h = h;
		}

		SDL_Rect GetRect() const // const keyword says "this function does not change anything about the class)
		{
			SDL_Rect returnValue = dst;
			returnValue.x = position.x;
			returnValue.y = position.y;
			return dst;
		}

		//Functions which access data from within are sometimes called Accessors, or getters
		Vec2 GetSize() const
		{
			Vec2 returnVec = { dst.w,dst.h };
			return returnVec;
		}

		//For animation, we want to know the dimensions of one frame of animation
		void SetSpriteSheetFrameSize(int width, int height)
		{
			src.w = width;
			src.h = height;
		}

		//This is a constructor. This is a special type of function used when creating an object.
		//The compiler knows it's a constructor because it has parentheses like a function, 
		//has the SAME NAME as the struct or class, and has no return type. 
		//This one has no arguments. In that case it's called the Default Constructor and is used to set default values
		Sprite()
		{
			std::cout << "Sprite default constructor\n";
			pTexture = nullptr;
			src = SDL_Rect{ 0,0,0,0 };
			dst = SDL_Rect{ 0,0,0,0 };
		}

		//Constructors can have arguments as well, which is handy when we need to make them different
		Sprite(SDL_Renderer* renderer, const char* filePathToLoad)
		{
			std::cout << "Sprite filepath constructor\n";
			;			src = SDL_Rect{ 0,0,0,0 };
			pTexture = IMG_LoadTexture(renderer, filePathToLoad); //load into our pTexture pointer
			if (pTexture == NULL) // if failed load
			{
				std::cout << "Image failed to load: " << SDL_GetError() << std::endl;
			}
			SDL_QueryTexture(pTexture, NULL, NULL, &src.w, &src.h); //ask for the dimensions of the texture
			//At this point, the width and the height of the texture should be placed at the memory addresses of src.w and src.h
			dst = SDL_Rect{ 0,0,src.w,src.h };
		}

		Sprite(SDL_Renderer* renderer, const char* filePathToLoad, int frameSizeX, int frameSizeY, int frameCount) : Sprite(renderer, filePathToLoad)
		{
			SetSpriteSheetFrameSize(frameSizeX, frameSizeY);
			SetSize(frameSizeX, frameSizeY);
			animationFrameCount = frameCount;
		}

		//This draw function can be called on individual variables of type Fund::Sprite, 
		//which will use their own variables to call SDL_RenderCopy. So, we can declare and draw new sprites with two lines:
		//Fund::Sprite myNewSprite = Sprite(pRenderer, "somefile.png");
		//myNewSprite.Draw(pRenderer);
		void Draw(SDL_Renderer* renderer)
		{
			dst.x = position.x;
			dst.y = position.y;
			src.x = src.w * (int)animationCurrentFrame;
			SDL_RenderCopyEx(renderer, pTexture, &src, &dst, rotation, NULL, flipState);
		}

		void NextFrame()
		{
			SetFrame(animationCurrentFrame + 1);
		}

		void SetFrame(int frame)
		{
			animationCurrentFrame = frame % animationFrameCount;
			src.x = src.w * animationCurrentFrame;
		}

		void AddFrameTime(float timeScale) // Call this in game update loop
		{
			//game FPS = 60
			//deltaTime = 1/60 seconds
			//sprite target FPS = 12
			//So animationCurrentFrame should go up by some amount each frame such that it increases by 1, 12 times per second
			//NextFrame();
			animationCurrentFrame += timeScale;
			if (animationCurrentFrame >= animationFrameCount)
			{
				animationCurrentFrame -= animationFrameCount;
			}
		}
	}; //struct Sprite

	class Bullet
	{
	public:
		Sprite sprite;
		Vec2 velocity; // in px per second

		//Move bullet
		void Update()
		{
			sprite.position.x += velocity.x * deltaTime;
			sprite.position.y += velocity.y * deltaTime;
		}
	};

	class Ship // A class that can move and shoot projectiles
	{
	public:
		//What data goes here?
		Sprite sprite;
		float moveSpeedPx = 100;
		float fireRepeatDelay = 0.5f;

	private:
		float fireRepeatTimer = 0.0f;

		//What functions should it have?
	public:
		void Move(Vec2 input)
		{
			sprite.position.x += input.x * (moveSpeedPx * deltaTime);
			sprite.position.y += input.y * (moveSpeedPx * deltaTime);
		}

		//Current version only handles shooting to the left or right
		void Shoot(bool towardRight, std::vector<Fund::Bullet>& container, Fund::Vec2 velocity)
		{
			//Create new bullet
			Fund::Sprite bulletSprite = Fund::Sprite(pRenderer, "../Assets/textures/bullet.png");

			//Start bullet at player sprite position
			bulletSprite.position.x = sprite.position.x;

			if (towardRight)
			{
				bulletSprite.position.x += sprite.GetSize().x;
			}

			bulletSprite.position.y = sprite.position.y + (sprite.GetSize().y / 2) - (bulletSprite.GetSize().y / 2);

			//Set up our Bullet class instance
			Bullet bullet;
			bullet.sprite = bulletSprite;
			bullet.velocity = velocity;

			//Add bullet to container (to the end of the array)
			container.push_back(bullet);

			//Reset cooldown
			fireRepeatTimer = fireRepeatDelay;
		}

		void Update()
		{
			fireRepeatTimer -= deltaTime;
		}

		bool CanShoot()
		{
			return (fireRepeatTimer <= 0.0f);
		}
	};

	//Part of AABB collision detection. 
	//Returns true if the bounds defined by minA and maxA overlap with the bounds defined by minB and maxB
	bool AreBoundsOverlapping(int minA, int maxA, int minB, int maxB)
	{
		bool isOverlapping = false;
		if (maxA >= minB && maxA <= maxB) // check if max of A is contained inside B
			isOverlapping = true;
		if (minA <= maxB && minA >= minB) // check if min of A is contained inside B
			isOverlapping = true;
		return isOverlapping;
	}

	//Check collision between two sprites
	bool AreSpritesOverlapping(const Sprite& A, const Sprite& B)
	{
		//get bounds of each sprite on x and y
		int minAx, maxAx, minBx, maxBx;
		int minAy, maxAy, minBy, maxBy;

		SDL_Rect boundsA = A.GetRect();
		SDL_Rect boundsB = B.GetRect();

		SDL_bool isColliding = SDL_HasIntersection(&boundsA, &boundsB);
		return (bool)isColliding;

		//minAx = boundsA.x;
		//minAy = boundsA.y;
		//minBx = boundsB.x;
		//minBy = boundsB.y;
		//
		//maxAx = boundsA.x + boundsA.w;
		//maxAy = boundsA.y + boundsA.h;
		//maxBx = boundsB.x + boundsB.w;
		//maxBy = boundsB.y + boundsB.h;
		//
		//bool overlapOnX = AreBoundsOverlapping(minAx, maxAx, minBx, maxBx);
		//bool overlapOnY = AreBoundsOverlapping(minAy, maxAy, minBy, maxBy);
		//
		////check if bounds overlap. Only when both axes have an overlap is there a collision
		//return overlapOnX && overlapOnY;
	}
}

//After the declaration of the Fund::Sprite struct, we can make our own variables of this Type!
Fund::Ship playerStarship;
std::vector<Fund::Bullet> playerBulletContainer; //std::vector is a class which allows changing size. This is a dynamic array of Fund::Bullet

std::vector<Fund::Ship> enemyContainer; //container of all enemy ships
std::vector<Fund::Bullet> enemyBulletContainer; //container of enemy projectiles

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// INIT ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Initialize SDL, open a window and set up renderer. Returns false if failed
bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL Init Failed: " << SDL_GetError();
		return false;
	}
	std::cout << "SDL Init Success\n";

	//Create and assign our SDL_Window pointer
	pWindow = SDL_CreateWindow("Joss's Lab Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, 0
	);

	if (pWindow == NULL) // Check if the last operation succeeded
	{
		std::cout << "Window creation failed: " << SDL_GetError();
		return false;
	}
	else
	{
		std::cout << "Window creation success\n";
	}

	//Create and assign our SDL_Renderer pointer
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	if (pRenderer == NULL) // If CreateRenderer failed...
	{
		std::cout << "Renderer creation failed: " << SDL_GetError();
		return false;
	}
	else
	{
		std::cout << "Renderer creation success\n";
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// LOAD ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Load()
{
	char* fileToLoad = "../Assets/textures/enterprise.png";

	playerStarship.sprite = Fund::Sprite(pRenderer, fileToLoad);

	Fund::Vec2 shipSize = playerStarship.sprite.GetSize();
	int shipWidth = shipSize.x / 4;
	int shipHeight = shipSize.y / 4;

	//Describe location to paste to on the screen
	playerStarship.sprite.SetSize(shipWidth, shipHeight);

	playerStarship.sprite.position.x = 50;
	playerStarship.sprite.position.y = (SCREEN_HEIGHT / 2) - (shipHeight / 2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// INPUT ///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Input variables
bool isUpPressed = false;
bool isDownPressed = false;
bool isShootPressed = false;

void Input()
{
	SDL_Event event; // Event data polled each time
	while (SDL_PollEvent(&event))  // poll until all events are handled!
	{
		// decide what to do with this event.
		switch (event.type)
		{
		case(SDL_KEYDOWN):
		{
			SDL_Scancode key = event.key.keysym.scancode;
			switch (key)
			{
			case(SDL_SCANCODE_W):
			{
				isUpPressed = true;
				break;
			}
			case(SDL_SCANCODE_S):
			{
				isDownPressed = true;
				break;
			}
			case(SDL_SCANCODE_SPACE):
			{
				isShootPressed = true;
				break;
			}
			break;
			}
			break;
		}
		case(SDL_KEYUP):
		{
			SDL_Scancode key = event.key.keysym.scancode;
			switch (key)
			{
			case(SDL_SCANCODE_W):
			{
				isUpPressed = false;
				break;
			}
			case(SDL_SCANCODE_S):
			{
				isDownPressed = false;
				break;
			}
			case(SDL_SCANCODE_SPACE):
			{
				isShootPressed = false;
				break;
			}
			}
			break;
		}
		}

	}
}


void SpawnEnemy()
{
	Fund::Sprite klingonShip1;
	klingonShip1 = Fund::Sprite(pRenderer, "../Assets/textures/d7_small.png");


	//random position along y, right side of screen along x
	klingonShip1.position = {
		SCREEN_WIDTH,
		(float)(rand() % (SCREEN_HEIGHT - (int)klingonShip1.GetSize().y))
	};

	klingonShip1.flipState = SDL_FLIP_HORIZONTAL;

	Fund::Ship enemy1;
	enemy1.sprite = klingonShip1;
	enemy1.fireRepeatDelay = 2.0;
	enemy1.moveSpeedPx = 80;

	//Add to list of enemies
	enemyContainer.push_back(enemy1);

	//reset timer
	enemySpawnTimer = enemySpawnDelay;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// UPDATE //////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdatePlayer()
{
	Fund::Vec2 inputVector;
	if (isUpPressed)
	{
		inputVector.y = -1;

		if (playerStarship.sprite.position.y < 0)
		{
			playerStarship.sprite.position.y = 0;
		}
	}

	if (isDownPressed)
	{
		inputVector.y = 1;

		const int lowestPointOnScreen = SCREEN_HEIGHT - playerStarship.sprite.GetSize().y;
		if (playerStarship.sprite.position.y > lowestPointOnScreen)
		{
			playerStarship.sprite.position.y = lowestPointOnScreen;
		}
	}

	//If shooting and our shooting is off cooldown
	if (isShootPressed && playerStarship.CanShoot())
	{
		bool toRight = true;
		Fund::Vec2 velocity = { 1000, 0 };
		//Passing bulletContainer by reference to add bullets to this container specifically
		playerStarship.Shoot(toRight, playerBulletContainer, velocity);
	}

	playerStarship.Move(inputVector);
	playerStarship.Update();
}

void DetectCollisions()
{
	//Collision Detection
	//enemy bullets and player
	for (std::vector<Fund::Bullet>::iterator it = enemyBulletContainer.begin(); it != enemyBulletContainer.end();)
	{
		Fund::Sprite& enemyBullet = it->sprite;
		if (Fund::AreSpritesOverlapping(playerStarship.sprite, enemyBullet))
		{
			std::cout << "Player was hit!" << std::endl;
			playerStarship.sprite.rotation += 90.0; // here's where you may want to decrement HP or lives depending on your game

			//Remove this element from the container. Since the size decreased, 
			//we should change our index as well to reflect the new size. The erase function is handy because it returns our new index
			it = enemyBulletContainer.erase(it);
		}
		if (it != enemyBulletContainer.end()) it++;
	}

	//For every player bullet...
	for (std::vector<Fund::Bullet>::iterator bulletIterator = playerBulletContainer.begin(); bulletIterator != playerBulletContainer.end();)
	{
		//For every enemy sprite...
		for (auto enemyIterator = enemyContainer.begin(); enemyIterator != enemyContainer.end();)
		{
			//Test for collision between player bullet and enemy
			if (Fund::AreSpritesOverlapping(bulletIterator->sprite, enemyIterator->sprite))
			{
				//Destroy bullet
				bulletIterator = playerBulletContainer.erase(bulletIterator);
				//Destroy enemy
				enemyIterator = enemyContainer.erase(enemyIterator);

				//If we destroy the last object in one of the containers, then stop comparing.
				if (bulletIterator == playerBulletContainer.end())
					break; // leave the for loop
			}

			if (enemyIterator != enemyContainer.end()) enemyIterator++;
		}
		if (bulletIterator != playerBulletContainer.end()) bulletIterator++; // as long as we are not at the end, then increment our iterator
	}
}

void Update() // called every frame at FPS
{
	UpdatePlayer();

	//Update player bullets
	for (int i = 0; i < playerBulletContainer.size(); i++)
	{
		//To access elements of an array, we use the array access operator []
		playerBulletContainer[i].Update();
	}

	//Update enemy bullets
	for (int i = 0; i < enemyBulletContainer.size(); i++)
	{
		enemyBulletContainer[i].Update();
	}

	//Update enemy ships
	for (int i = 0; i < enemyContainer.size(); i++)
	{
		//Get reference to enemy at index i (& makes it a reference variable)
		Fund::Ship& enemy = enemyContainer[i];

		enemy.Move({ -1, 0 });
		enemy.Update();
		if (enemy.CanShoot())
		{
			bool towardRight = false;
			Fund::Vec2 velocity = { -150, 0 };
			enemy.Shoot(towardRight, enemyBulletContainer, velocity);
		}
	}

	//Spawn enemies on timer and update timer
	if (enemySpawnTimer <= 0)
	{
		SpawnEnemy();
	}
	else
	{
		enemySpawnTimer -= deltaTime;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// DRAW ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Draw()
{
	SDL_SetRenderDrawColor(pRenderer, 5, 5, 15, 255);
	SDL_RenderClear(pRenderer);

	playerStarship.sprite.Draw(pRenderer);

	//Draw ALL bullets on screen
	for (int i = 0; i < playerBulletContainer.size(); i++)
	{
		playerBulletContainer[i].sprite.Draw(pRenderer);
	}

	//Draw ALL enemy bullets on screen
	for (int i = 0; i < enemyBulletContainer.size(); i++)
	{
		enemyBulletContainer[i].sprite.Draw(pRenderer);
	}

	//Draw ALL enemy Ships on screen
	for (int i = 0; i < enemyContainer.size(); i++)
	{
		enemyContainer[i].sprite.Draw(pRenderer);
	}

	// RenderPresent shows the hidden space we were drawing to called the BackBuffer. 
	// For more information why we use this, look up Double Buffering Rendering
	SDL_RenderPresent(pRenderer);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// MAIN  ///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* args[])
{
	// show and position the application console
	AllocConsole();
	auto console = freopen("CON", "w", stdout);
	const auto window_handle = GetConsoleWindow();
	MoveWindow(window_handle, 100, 700, 800, 200, TRUE);

	// Display Main SDL Window
	isGameRunning = Init();

	Load();

	// Main Game Loop, one iteration of this loop is one game frame
	while (isGameRunning)
	{

		//time at the start of the frame, in ms
		const auto frame_start = static_cast<float>(SDL_GetTicks());

		Input();  // take player input

		Update(); // update game state (presumably based on other conditions and input)

		Draw();  // draw to screen to show new game state to player

		//Figure out how long we need to wait for the next frame timing.
		//Current time - time at start of frame = time elapsed during this frame
		const float frame_time = static_cast<float>(SDL_GetTicks()) - frame_start;
		if (frame_time < DELAY_TIME) // if time passed is less than the time we have for each frame...
		{
			//Do nothing for a while until it's time for the next frame
			SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
		}

		// delta time. Time elapsed this frame, in seconds
		//deltaTime = (static_cast<float>(SDL_GetTicks()) - frame_start) / 1000.0f;
	}

	return 0;
}