#include <memory>
#include <iostream>

#include "GameObject.h"

#include "Music.h"
#include "TileSet.h"


#ifndef STATE_H
#define STATE_H

class State {

public:
	State();
	~State();

	void LoadAssets();
	void Update(float);
	void Render();
	bool QuitRequested();

	void RequestToQuit();

	//void Input();
	void AddObject(int, int);

private:
	Music music;
	bool quitRequested;	

	std::vector< std::unique_ptr<GameObject> >	objectArray;
	std::vector< std::unique_ptr<Component> > soundsArray;

};

#endif