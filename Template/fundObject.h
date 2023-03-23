#pragma once
#include"textFund.h"
#include<SDL.h>
#include "Vec2.h"
//#include "bulletManager.h"


class fundObject
{
public:

	fundObject(const char* filename,int x,int y);
	~fundObject() {}
	//Getter Function
	Vec2 getPos();


	void setSpriteFrame(int width, int height);


	void setFrame(int frame);

	void setSize(Vec2 widthHeight);
	void setSize(int x, int y);

	void update();
	void input();
	void shoot();
	void render(int rotation);

private:
	Vec2 position;
//	bulletManager bullet;
	SDL_Rect srcRect, dstRect;

	int yPos;
	int xPos;
	int rotation;

	bool upMove = false;
	bool downMove = false;
	bool leftMove = false;
	bool rightMove = false;
	bool shooting = false;

	int currentFrame = 0;

	float deltaTime = 1.0f / 60.0f;
	const float playerMoveSpeedPerSec = 500*deltaTime;

	const float shootCD = 0.1f;
	float shootingTimer = 0.0f;


	SDL_Texture* objectTexture;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	

	


};

