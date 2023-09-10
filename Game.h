#include <string>
#include <SDL.h>
#include "State.h"

#ifndef __GAME_H__
#define __GAME_H__

class Game {
public:

	//Game(const Game& obj) = delete;

	~Game();

	static Game& GetInstance(std::string, int, int);
	
	void Run();

	State& GetState();
	SDL_Renderer* GetRenderer();


private:
	Game(std::string, int, int);

	static Game* instance;
	SDL_Window* window;
	SDL_Renderer *renderer;
	State* state;

};




#endif