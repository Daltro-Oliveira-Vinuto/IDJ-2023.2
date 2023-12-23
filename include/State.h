#include <memory>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "GameObject.h"
#include "Music.h"
#include "SDL.h"
#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "Alien.h"


#ifndef STATE_H
#define STATE_H

class State {

public:
	State();
	~State();

	void Start();
	std::weak_ptr<GameObject> AddObject(GameObject*);
	std::weak_ptr<GameObject> GetObjectPtr(GameObject*);

	void LoadAssets();
	void Update(float);
	void Render();
	bool QuitRequested();

	void RequestToQuit();

	//void Input();
	//void AddObject(int, int);

private:
	Music music;
	bool quitRequested;	

	//std::vector< std::unique_ptr<GameObject> >  objectArray;
	std::vector< std::shared_ptr<GameObject> > objectArray;

	std::vector< std::unique_ptr<Component> > soundsArray;

	bool started;
};

#endif