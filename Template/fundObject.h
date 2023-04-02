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

	//Getter Functions
	Vec2 getPos();
	Vec2 getSize();
	//Setter Functions
	void setSize(Vec2 width_or_height);
	void setPos(Vec2 XposY);

	//Functions Relating to Animation
	void setSpriteSheetInfo(int width_of_frame, int height_of_frame, int amount_of_frames);
	void setFrame(int frame);
	void nextFrame();
	void animate();

	//GameLoop
	virtual void input() ;
	virtual void update();
	virtual void shoot();
	virtual void render(int rotation);





	void setSpriteFrame(int width, int height, int frameCount);

	Vec2 position = { 0,0 };
	SDL_Rect src, dst;
private:

	//Relating to Animation
	int currentFrame = 0;
	int frameCount;
	float animationTime = 0.1f;
	float animationTimer = 0.0f;


	float deltaTime = 1.0f / 60.0f;
	//Movement Speed

	//Shooting Delay + Timer
	const float shootCD = 0.1f;
	float shootingTimer = 0.0f;

	SDL_Texture* objectTexture;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};

