#include "Sprite.h"
#include "Music.h"

#ifndef STATE_H
#define STATE_H

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