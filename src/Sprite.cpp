#include <stdlib.h>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "Sprite.h"
#include "Game.h"
#include "Rect.h"
#include "Vec2.h"


Sprite::Sprite(GameObject& associated): Component(associated) {
	this->texture = NULL;
	this->clipSource = {0,0,0,0};
	this->clipDestine = {0,0,0,0};
	this->scale = Vec2(1,1);
}

Sprite::Sprite(GameObject& associated, std::string file): Component(associated) {
	this->texture = NULL;
	this->clipSource = {0,0,0,0};
	this->clipDestine = {0,0,0,0};
	this->scale = Vec2(1,1);
	Open(file);
}

Sprite::~Sprite() {
	//SDL_DestroyTexture(texture);
	// ClearImages() of game will do this
}

void Sprite::Open(std::string file) {

	this->texture = Game::GetInstance("",0,0).GetResources().GetImage(file.c_str());
	//texture = IMG_LoadTexture(Game::GetInstance("",0,0).GetRenderer(), file.c_str());

	if (texture == NULL) {
		printf("Texture not loaded! Error: %s\n", SDL_GetError());
	} else {
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);
		this->clipSource = {0,0, width, height};
		this->clipDestine = this->clipSource;
	}
}

void Sprite::SetClip(const Rect& clip) {
	this->clipSource = {int(clip.x), int(clip.y), int(clip.w), int(clip.h)};
	this->clipDestine = this->clipSource;
}

void Sprite::Update(float dt) {
}

void Sprite::Render() {
	int x, y;
	
	x = associated.box.x + Camera::pos.x;
	y = associated.box.y + Camera::pos.y;

	Render(x, y);	
}

void Sprite::Render(int x, int y) {
	SDL_Rect rect_destine = {
		x, 
		y,
		clipDestine.w*int(this->scale.x),
		clipDestine.h*int(this->scale.y)
			};

	/*
	std::cout << "scale: " << this->scale.x << " , " << this->scale.y <<
				std::endl;
	std::cout << rect_destine.w << " , "<< 
				rect_destine.h << std::endl;
	*/
	/*
	if (SDL_RenderCopy(Game::GetInstance("",0,0).GetRenderer(), texture, &clipRect, &destine_rect) != 0) {
		printf("Error to render, %s\n", SDL_GetError());
	}
	*/
	SDL_Point* center = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;


	if (SDL_RenderCopyEx(Game::GetInstance("",0,0).GetRenderer(), 
				this->texture, 
				&(this->clipSource), 
				&rect_destine,
				this->associated.angleDeg,
				center,
				flip) != 0) {
		printf("Error to render, %s\n", SDL_GetError());
	} 
}

bool Sprite::Is(std::string type) {
	bool is = false;

	if (type == "Sprite") {
		is = true;
	}

	return is;
}

int Sprite::GetWidth() {
	int spriteWidth = this->width;
	return spriteWidth;
}

int Sprite::GetHeight() {
	int spriteHeight = this->height;
	return spriteHeight;
}

bool Sprite::IsOpen() {
	bool open;

	if (texture == NULL) {
		open = false;
	} else {
		open = true;
	}

	return open;
}

void Sprite::SetScale(float scaleX, float scaleY) {
	int newScaleX = scaleX;
	int newScaleY = scaleY;

	if (newScaleX == 0) {
		newScaleX = 1;
	}

	if (newScaleY == 0) {
		newScaleY = 1;
	}

	this->scale = Vec2(newScaleX, newScaleY);
}

Vec2 Sprite::GetScale() {

	return this->scale;
}


void Sprite::SetClipDest(const Rect& rect) {
	this->clipDestine = {
			int(rect.x), 
			int(rect.y), 
			int(rect.w),
			int(rect.h)};
}










