#include "Sprite.cpp"
#include "Music.cpp"

#ifndef __STATE_H__
#define __STATE_H__

class State {

public:
	State(SDL_Renderer*);

	void LoadAssets();
	void Update(float);
	void Render(SDL_Renderer*);
	bool QuitRequested();

private:
	Sprite bg;
	Music music;
	bool quitRequested;	

};

#endif