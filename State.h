#include "Sprite.cpp"
#include "Music.cpp"

#ifndef __STATE_H__
#define __STATE_H__

class State {

public:
	State();

	void LoadAssets();
	void Update(float);
	void Render();
	bool QuitRequested();

private:
	Sprite bg;
	Music music;
	bool quitRequested;	

};

#endif