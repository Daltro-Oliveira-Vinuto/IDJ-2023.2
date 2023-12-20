#include <string>
#include <unordered_map>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#ifndef RESOURCES_H
#define RESOURCES_H


class Resources {
public:
	Resources();
	~Resources();

	SDL_Texture* GetImage(std::string);
	void ClearImages();

	Mix_Music* GetMusic(std::string);
	void ClearMusics();

	Mix_Chunk* GetSound(std::string);
	void ClearSounds();

private:
	std::unordered_map<std::string, SDL_Texture*> imageTable;
	std::unordered_map<std::string, Mix_Music*> musicTable;
	std::unordered_map<std::string, Mix_Chunk*> soundTable;

};


#endif