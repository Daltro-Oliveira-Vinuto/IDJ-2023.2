#include "Game.h"
#include "State.h"
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

Game* Game::instance = NULL;
int Game::FPS = 30;

void Game::Update(float dt) {
	//input.Update();
	InputManager::GetInstance().Update();
	state->Update(dt);
}

void Game::Render() {
	state->Render();
}

void Game::Run() {
	//printf("Game loop is started(rate ~ frame/iteration)!---------------> \n");

	int delay = 1000.0/FPS;

	//InputManager::GetInstance().Update();
	//this->CalculaDeltaTime();
	//state->Update(this->dt);
	
	if (state == NULL) {
		printf("State not started!\n");
		exit(0);
	}
	
	state->Start();
	
	while(state->QuitRequested()==false) {
		/*
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff,0xff);
		SDL_RenderClear(renderer);
		SDL_Rect rect = {50,50, 200, 200};
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
		SDL_RenderDrawRect(renderer, &rect);
		*/

		// step 1: Verify, control and load the game's screens;

		// step 2: Input date readed and processed

		// UNFINISHED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// step 3: State of the objects are updated

		this->CalculaDeltaTime();

		this->Update(this->dt);

		// step 4: The objects are drawn in the screen
		this->Render();


		SDL_RenderPresent(renderer);
		SDL_Delay(delay);


		/*
		SDL_Event event;

		while(SDL_PollEvent(&event)!=0) {
			switch(event.type) {
				case (SDL_QUIT):
					state->RequestToQuit();
					break;
				
				case (SDL_KEYDOWN):
					if (event.key.keysym.sym == SDLK_ESCAPE){
						state->RequestToQuit();
					}

					break;
				}
		}
		*/
	}
}

Game::Game(std::string title, int width, int height) {
	this->width = width;
	this->height = height;

	InputManager::GetInstance();

	this->resources = new Resources();
	//printf("address of resources allocated: %p\n", resources);

	//printf("Object Game started!\n");
	FPS = 30;
	if (instance != NULL) {
		printf("Error! Game constructor should be called only once!\n");
	} else {
		instance = this;

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
			printf("SDL not initialized!. Error: %s\n", SDL_GetError());
		} else {
			if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF ) == 0) {
				printf("IMG not initialized!. Error: %s\n", IMG_GetError());
			} else {
				// wav format is available by default
				if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
					printf("Mix not initialized!. Error: %s\n", Mix_GetError());
				} else {
					if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,  
									  MIX_DEFAULT_FORMAT,
									  MIX_DEFAULT_CHANNELS,1024) != 0) {
						printf("Mix_OpenAudio don't worked! Error: %s\n", Mix_GetError());
					} else {
						const int NUM_CHANNELS = 32;
						Mix_AllocateChannels(NUM_CHANNELS);

						// At this point SDL, IMG and Mix had been initialized successfully!
						window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
														 SDL_WINDOWPOS_CENTERED,
														 width, height,	0);

						if (window == NULL) {
							printf("Window not created! Error: %s\n", SDL_GetError());
						} else {
							renderer = SDL_CreateRenderer(window, -1,
														  SDL_RENDERER_ACCELERATED);

							if (renderer == NULL) {
								printf("Renderer not created! Error: %s\n", SDL_GetError());
							} else {

								//printf("Address of rendered created: %p\n", renderer);
								// At this point window and renderer had been successfully created
								state = new State();

								
							}

						}

					}
				}
			}
		}
	}

	this->frameStart = 0;
	this->dt = 0.0;

	//printf("Game initialized!\n");
}

Game& Game::GetInstance(std::string title, int width, int height) {
	Game* aux_instance = NULL;

	if (instance != NULL) {
			aux_instance = instance;

	} else if (instance == NULL) {
			instance = new Game(title, width, height);

			aux_instance = instance;
	}

	return *aux_instance;
}

Game::~Game() {

	delete this->resources; // call destructor of the class Resources

	delete state; state = NULL;

	SDL_DestroyRenderer(renderer); renderer = NULL;

	SDL_DestroyWindow(window); window = NULL;

	Mix_CloseAudio();

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	// call the destructor of InputManager
}

State& Game::GetState() {
	return *state;
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}


Resources& Game::GetResources() {
	//printf("address of resources passed: %p\n", resources);
	return *resources;
}

/*
InputManager& Game::GetInput() {

	return input;
}
*/

float Game::GetDeltaTime() {
	return this->dt;
}

void Game::CalculaDeltaTime() {
	int frameAtual;

	frameAtual = SDL_GetTicks();

	this->dt = (frameAtual - this->frameStart)/1000.0;
	this->frameStart = frameAtual;

}

int Game::GetWidth() {
	return this->width;
}

int Game::GetHeight() {
	return this->height;
}
