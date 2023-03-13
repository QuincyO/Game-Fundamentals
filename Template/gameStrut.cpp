#pragma once
#include<SDL_image.h>
#include <SDL.h>
#include <iostream>
#include "Renderer.h"


struct spriteObject
{

public:
	SDL_Texture* pTexture;
	SDL_Rect src;
	SDL_Rect dst;
	SDL_RendererFlip Flip = SDL_FLIP_NONE;
	float sAngle;
	//Default Consturctor with no arguments
	spriteObject()
	{
		pTexture = nullptr;
		sAngle = 0;
		src = { 0,0,0,0 };
		dst = { 0,0,0,0 };

	}
	//Constructor with arguments
	spriteObject(SDL_Renderer* renderer, const char* fileName, int angle)
	{
		pTexture = IMG_LoadTexture(renderer, fileName);
		if (pTexture == NULL) {
			std::cout << "Image Failed to Load: ";
			std::cout << fileName << std::endl;
		}
		else std::cout << "Image Load Succesful\n";
		SDL_QueryTexture(pTexture, NULL, NULL, &src.w, &src.h);

		src.x = 0;
		src.y = 0;
		dst.w = src.w;
		dst.h = src.h;
		sAngle = angle;
	}

	//Member Function of spriteObject Struct
	void draw(SDL_Renderer* renderer)
	{
		SDL_RenderCopyEx(renderer, pTexture, &src, &dst, sAngle, NULL, Flip);
	}



private:


};