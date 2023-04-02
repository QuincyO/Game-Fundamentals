#pragma once
#include <SDL.h>
#include "fundObject.h"
#include "bulletManager.h"
class playerShip:public fundObject
{
public:
	playerShip(const char* texture) ;
	~playerShip() {};
	


	//Functions Relating to Animation
	void setSpriteSheetInfo(int width_of_frame, int height_of_frame, int amount_of_frames);
	void setFrame(int frame);
	void nextFrame();
	void animate();

	//GameLoop
	void input();
	void move(Vec2 inputVector);
	void update();
	void shoot();
	void draw();


private:
	float deltaTime = 1.0f / 60.0f;
	SDL_Event pEvent;

	Vec2 inputVector;
	Vec2 position;
	bool upMove = false;
	bool downMove = false;
	bool leftMove = false;
	bool rightMove = false;
	bool shooting = false;

	float playerMoveSpeedPerSec = 300 ;

	bulletManager bullet;

	//Animation Vars
	int frameCount;
	int currentFrame;

	//Shooting Timers;
	const float fireRate = .1f; //10 Shots per Second;
	float fireTimer = 0.0f;






	


};

