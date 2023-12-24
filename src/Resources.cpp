#include <unordered_map>
#include <iostream>
#include "Resources.h"
#include "Game.h"

Resources::Resources() {

}

Resources::~Resources() {
	this->ClearImages();
	this->ClearMusics();
	this->ClearSounds();
	//printf("The game resources had been released\n");
}

SDL_Texture* Resources::GetImage(std::string file) {
	std::unordered_map<std::string, SDL_Texture*>::iterator it;

	it = this->imageTable.find(file);
	if (it == imageTable.end()) {

		SDL_Texture* new_texture = NULL;

		new_texture = IMG_LoadTexture(Game::GetInstance("",0,0).GetRenderer(), file.c_str() );

		//std::cout << "new_texture: " << new_texture << std::endl;
		if (new_texture == NULL) {	
			printf("Error to load texture! %s\n", SDL_GetError());
		} else {
			imageTable[file] = new_texture;
			return imageTable.find(file)->second;
		}	
	} else {

		return imageTable.find(file)->second;
	}

	printf("Error! to access image Table!\n");
	return NULL;
}

Mix_Music* Resources::GetMusic(std::string file) {
	std::unordered_map<std::string, Mix_Music*>::iterator it;

	it = musicTable.find(file);

	if (it == musicTable.end()) {

		Mix_Music* music;

		music = Mix_LoadMUS(file.c_str());

		//std::cout << "Music loaded!" << std::endl;
		if (music == NULL) {
			printf("Music not opened!, Error: %s\n", Mix_GetError());
		} else {
			musicTable[file] = music;
			return musicTable.find(file)->second;
		}

	} else {

		return musicTable.find(file)->second;
	}

	printf("Error! to acess music table!");

	return NULL;

}

Mix_Chunk* Resources::GetSound(std::string file) {
	std::unordered_map<std::string, Mix_Chunk*>::iterator it;

	it = soundTable.find(file);

	if (it == soundTable.end()) {
		Mix_Chunk* chunk = NULL;

		chunk = Mix_LoadWAV(file.c_str());

		//std::cout << "new chunk allocated "<< std::endl;
		if (chunk == NULL) {
			printf("Sound not loaded! Error: %s\n", Mix_GetError());
		} else {
			soundTable[file] = chunk;
		}
	}

	return (*soundTable.find(file)).second;
	
}

void Resources::ClearImages() {
	std::unordered_map<std::string, SDL_Texture*>::iterator it;
	for(it = imageTable.begin(); it != imageTable.end(); it++) {
		SDL_DestroyTexture(it->second);
	}

	imageTable.clear();

}

void Resources::ClearMusics() {
	std::unordered_map<std::string, Mix_Music*>::iterator it;

	for(it = musicTable.begin(); it != musicTable.end(); it++) {
		Mix_FreeMusic(it->second);
	}

}

void Resources::ClearSounds() {
	std::unordered_map<std::string, Mix_Chunk*>::iterator it;

	for(it = soundTable.begin(); it != soundTable.end(); it++) {
		Mix_FreeChunk((*it).second);
	}

}