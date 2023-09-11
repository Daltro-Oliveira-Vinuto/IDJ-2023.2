
#ifndef __SPRITE_H__
#define __SPRITE_H__

class Sprite {

public:
	Sprite();
	Sprite(SDL_Renderer*, std::string);
	~Sprite();

	void Open(SDL_Renderer*, std::string);
	void SetClip(int, int, int, int);

	void Render(SDL_Renderer*, int, int);

	int GetWidth();

	int GetHeight();

	bool IsOpen();

private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;

};


#endif