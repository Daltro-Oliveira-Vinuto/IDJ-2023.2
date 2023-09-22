#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Game.h"


int main(int argc, char **argv) {
	const int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 600;
               
	Game game = Game::GetInstance("work 1", SCREEN_WIDTH, SCREEN_HEIGHT);

	game.Run();


	return 0;

}