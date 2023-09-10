#include "Sprite.h"

Sprite::Sprite() {
	texture = NULL;
}

Sprite::Sprite(SDL_Renderer* renderer, std::string file) {
	Open(renderer, file);
}

Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
}

void Sprite::Open(SDL_Renderer* renderer, std::string file) {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
	} else {
		texture = NULL;
	}
	

	texture = IMG_LoadTexture(renderer, file.c_str());

	if (texture == NULL) {
		printf("Texture not loaded! Error: %s\n", SDL_GetError());
	} else {
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	}
}

void Sprite::SetClip(int x, int y, int width, int height) {
	clipRect = {x, y, width, height};

}

void Sprite::Render(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect destine_rect = {x, y, clipRect.w, clipRect.h};

	if (SDL_RenderCopy(renderer,  texture, &clipRect, &destine_rect) != 0) {
		printf("Error to render, %s\n", SDL_GetError());
	} 
	

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