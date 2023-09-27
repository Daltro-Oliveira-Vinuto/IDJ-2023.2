#include "SDL.h"
#include "SDL_image.h"
#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(GameObject& associated): Component(associated) {
	texture = NULL;
}

Sprite::Sprite(GameObject& associated, std::string file): Component(associated) {
	Open(file);
}

Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file) {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
	} else {
		texture = NULL;
	}
	

	texture = IMG_LoadTexture(Game::GetInstance("",0,0).GetRenderer(), file.c_str());

	if (texture == NULL) {
		printf("Texture not loaded! Error: %s\n", SDL_GetError());
	} else {
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);
		int x, y;
		x = associated.box.x;
		y = associated.box.y;

		clipRect = {x,y,width,height};

	}
}

void Sprite::SetClip(int x, int y, int width, int height) {
	clipRect = {x, y, width, height};

}

void Sprite::Update(float dt) {

}

void Sprite::Render() {
	int x, y;
	
	x = associated.box.x;
	y = associated.box.y;

	SDL_Rect destine_rect = {x, y, clipRect.w, clipRect.h};

	if (SDL_RenderCopy(Game::GetInstance("",0,0).GetRenderer(), texture, &clipRect, &destine_rect) != 0) {
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
	return width;
}

int Sprite::GetHeight() {
	return height;
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