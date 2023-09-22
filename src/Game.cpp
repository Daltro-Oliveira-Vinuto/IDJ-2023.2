#include "Game.h"
#include "State.h"
#include <string>
#include "SDL_image.h"
#include "SDL_mixer.h"

Game* Game::instance = NULL;


void Game::Run() {
	//printf("Game loop is started(rate ~ frame/iteration)!---------------> \n");

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
		state->Update(0);

		// step 4: The objects are drawn in the screen
		state->Render();


		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}

}

Game::Game(std::string title, int width, int height) {
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
	delete state; state = NULL;

	SDL_DestroyRenderer(renderer); renderer = NULL;

	SDL_DestroyWindow(window); window = NULL;

	Mix_CloseAudio();

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

}

State& Game::GetState() {
	return *state;
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

