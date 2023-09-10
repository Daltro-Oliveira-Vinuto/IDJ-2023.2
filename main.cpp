#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


int main(int argc, char **argv) {

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);// wav is default
	TTF_Init();


	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	
	return 0;

}