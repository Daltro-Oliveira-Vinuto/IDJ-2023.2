#include <string>
#include "SDL.h"
#include "State.h"
#include "Resources.h"
#include "InputManager.h"


#ifndef GAME_H
#define GAME_H

class Game {
public:

	//Game(const Game& obj) = delete;

	~Game();

	static Game& GetInstance(std::string title, int width, int height);
	
	void Update(float);
	void Render();
	void Run();

	State& GetState();
	SDL_Renderer* GetRenderer();
	Resources& GetResources();
	//InputManager& GetInput();

	static int FPS;
private:
	Game(std::string, int, int);

	static Game* instance;
	SDL_Window* window = NULL;
	SDL_Renderer *renderer = NULL;
	State* state = NULL;

	Resources* resources = NULL;
	//InputManager input;

};



#endif