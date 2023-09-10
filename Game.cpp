#include "Game.h"
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>

Game* Game::instance = NULL;

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

void Game::Run() {
	printf("Game is running!---------------> \n");
}

Game& Game::GetInstance(std::string title, int width, int height) {

	if (instance != NULL) {
			return *instance;

	} else if (instance == NULL) {
			instance = new Game(title, width, height);

			return *instance;
	}
}
