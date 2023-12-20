#include "Music.h"
#include "Game.h"

Music::Music() {
	music = NULL;;
}

Music::Music(std::string file) {
	Open(file);
}

Music::~Music() {
	//Mix_FreeMusic(music);
	// released by the destructor of Resources of the game object
}

void Music::Open(std::string file) {
	//music = Mix_LoadMUS(file.c_str());
	this->music = Game::GetInstance("",0,0).GetResources().GetMusic(file);
	if (music == NULL) {
		printf("Error to load music: %s\n", Mix_GetError());
	}
}

void Music::Play(int times=-1) {
	if (music != NULL)
		Mix_PlayMusic(music, times);
	else {
		printf("Error music not open yet! %s\n",Mix_GetError());
	}
}

void Music::Stop(int msToStop = 1500) {
	Mix_FadeOutMusic(msToStop);
}

bool Music::IsOpen() {
	bool open;

	if (music == NULL) {
		open = false;
	} else {
		open = true;
	}

	return open;
}