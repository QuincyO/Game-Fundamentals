#pragma once
#include"textFund.h"
#include<SDL.h>

class fundObject
{
public:

	fundObject(const char* filename,int x,int y);
	~fundObject() {}

	void update();
	void input();
	void shoot();
	void render(int rotation);

	SDL_Rect srcRect, dstRect;
private:

	int yPos;
	int xPos;
	int rotation;

	bool upMove = false;
	bool downMove = false;
	bool leftMove = false;
	bool rightMove = false;
	bool shooting = false;

	float deltaTime = 1.0f / 60.0f;
	const float playerMoveSpeedPerSec = 500*deltaTime;

	const float shootCD = 0.1f;
	float shootingTimer = 0.0f;


	SDL_Texture* objectTexture;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	

	


};

