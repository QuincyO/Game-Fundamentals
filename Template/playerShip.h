#pragma once
#include <SDL.h>
#include "fundObject.h"
class playerShip:public fundObject
{
public:
	playerShip(const char* texture) ;
	~playerShip() {};
	
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
	void input();
	void update();
	void shoot();
	void draw();


private:
	float deltaTime = 1.0f / 6.0f;

	SDL_Rect src, dst;
	SDL_Texture* pTex;
	SDL_Event* pEvent;

	Vec2 position;
	bool upMove = false;
	bool downMove = false;
	bool leftMove = false;
	bool rightMove = false;
	bool shooting = false;

	
	//Animation Vars
	int frameCount;
	int currentFrame;

	//Shooting Timers;
	const float fireRate = 0.1f * deltaTime; //10 Shots per Second;
	float fireTimer = 0.0f;






	


};

