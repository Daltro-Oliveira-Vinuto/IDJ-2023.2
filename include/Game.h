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
	float GetDeltaTime();

	static int FPS;
	static int delay;

	int GetWidth();
	int GetHeight();
	
private:
	Game(std::string, int, int);
	int width;
	int height;
	void CalculaDeltaTime();

	static Game* instance;
	SDL_Window* window = NULL;
	SDL_Renderer *renderer = NULL;
	State* state = NULL;

	Resources* resources = NULL;
	//InputManager input;

	int frameStart;
	float dt;


};



#endif