#pragma once
#include"textFund.h"
#include "Bullet.h"




class playerShip;
class fundObject
{
public:

	fundObject() {};
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


	//Bullets
	void createBullet(const char* filepath, SDL_Rect dst, Vec2 Velo);
	void updateBullets();
	void drawBullets();


	void setSpriteFrame(int width, int height, int frameCount);


//Child Classes Need to see this
//	std::vector<Bullet> bullets;
	Vec2 position = { 0,0 };
	SDL_Rect src, dst;
//	Bullet bullet;
	SDL_Texture* objectTexture;
private:

	//Relating to Animation
	int currentFrame = 0;
	int frameCount;
	float animationTime = 0.1f;
	float animationTimer = 0.0f;


	//Movement Speed



	SDL_RendererFlip flip = SDL_FLIP_NONE;
};


