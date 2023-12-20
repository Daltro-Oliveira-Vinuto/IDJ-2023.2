#include "Sound.h"
#include "Game.h"


Sound::Sound(GameObject& associated) : Component(associated) {
	chunk = NULL;
}

Sound::Sound(GameObject& associated, std::string file) : Component(associated) {
	chunk = NULL;
	Open(file);
}

Sound::~Sound() {
	if (chunk != NULL) {
		Mix_HaltChannel(channel);
		//Mix_FreeChunk(chunk);
		// Chunk is released by the destructor of Resources of the Game object
	}
}


void Sound::Play(int times = 1) {

	channel = Mix_PlayChannel(-1, chunk, times);
	//printf("Sound played\n");
}

void Sound::Stop() {
	if (chunk != NULL) {
		Mix_HaltChannel(channel);
	}

}

void Sound::Open(std::string file) {
	//chunk = Mix_LoadWAV(file.c_str());
	this->chunk = Game::GetInstance("",0,0).GetResources().GetSound(file);

	if (chunk == NULL) {
		printf("Error! %s not opened! %s\n", file.c_str(), Mix_GetError());
	}
}

bool Sound::IsOpen() {
	bool is = false;

	if (chunk != NULL) {
		is = true;
	}

	return is;
}




void Sound::Update(float dt) {

}

void Sound::Render() {

}

bool Sound::Is(std::string type) {
	bool is = false;  

	if (type == "Sound") {
		is = true;
	}

	return is;
}


























