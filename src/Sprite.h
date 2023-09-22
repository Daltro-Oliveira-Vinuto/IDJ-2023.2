#include <string>
#include "SDL.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {

public:
	Sprite();
	Sprite(std::string);
	~Sprite();

	void Open(std::string);
	void SetClip(int, int, int, int);

	void Render(int, int);

	int GetWidth();

	int GetHeight();

	bool IsOpen();

private:
	SDL_Texture* texture = NULL;
	int width;
	int height;
	SDL_Rect clipRect;

};


#endif