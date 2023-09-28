#include <string>
#include "SDL.h"
#include "GameObject.h"
#include "Rect.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite: public Component {

public:

	Sprite(GameObject&);
	Sprite(GameObject&, std::string);
	~Sprite();

	void Open(std::string);
	void SetClip(const Rect&);

	void Update(float);
	void Render();
	bool Is(std::string);
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