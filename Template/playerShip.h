#pragma once
#include <SDL.h>
#include"textFund.h"





class playerShip 
{
public:

	playerShip() {};
	playerShip(const char* texture) ;
	~playerShip() {};
	


	//Functions Relating to Animation
	void setSpriteSheetInfo(int width_of_frame, int height_of_frame, int amount_of_frames);
	void setFrame(int frame);
	void nextFrame();
	void animate();

	void setPos(Vec2 position);
	//GameLoop
	void input();
	void move(Vec2 inputVector);
	void update();
	void shoot();
	void drawBullets();
	void draw(int rotation);



private:

	Vec2 position;
	SDL_Rect src, dst;
	SDL_Event pEvent;
	SDL_Texture* pTex = nullptr;
	Vec2 inputVec;
	Vec2 bulletVelocity = { 0,-750 };

	
	//Bullet bullet;
	//std::vector<Bullet> bullets;



	bool upMove = false;
	bool downMove = false;
	bool leftMove = false;
	bool rightMove = false;
	bool shooting = false;

	float playerMoveSpeedPerSec;



	//Animation Vars
	int frameCount=0;
	int currentFrame=0;

	//Shooting Timers;
	const float fireRate = .8f; //10 Shots per Second;
	float fireTimer = 0.0f;


	int audioVol = 50;



	


};

