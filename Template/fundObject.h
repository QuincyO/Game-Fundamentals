#pragma once
#include"textFund.h"
#include<SDL.h>
#include "Vec2.h"
//#include "bulletManager.h"


class fundObject
{
public:


	fundObject(const char* filename);
	~fundObject() {}
	//Getter Function
	Vec2 getPos();
	Vec2 getSize();

	void setPosition(int x, int y);


	void setSpriteFrame(int width, int height, int frameCount);
	void animate();


	void setFrame(int frame);
	void nextFrame();
	
	
	void scaleSize(float Scale);
	void setSize(int w, int h);
	



	void update();
	void input();
	void shoot();
	void render(int rotation);

private:
	SDL_Rect srcRect, dstRect;

	//Relating to Position
	Vec2 position ;
	int yPos;
	int xPos;
	int rotation;
	
	//Relating to Movement + Shooting
	bool upMove = false;
	bool downMove = false;
	bool leftMove = false;
	bool rightMove = false;
	bool shooting = false;

	//Relating to Animation
	int currentFrame = 0;
	int frameCount;
	float animationTime = 0.1f;
	float animationTimer = 0.0f;


	float deltaTime = 1.0f / 60.0f;
	//Movement Speed
	const float playerMoveSpeedPerSec = 500*deltaTime;

	//Shooting Delay + Timer
	const float shootCD = 0.1f;
	float shootingTimer = 0.0f;

	SDL_Texture* objectTexture;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};

