#include <string>
#include "SDL_mixer.h"

#ifndef MUSIC_H
#define MUSIC_H


class Music {
public:
	Music();
	~Music();
	Music(std::string);

	void Open(std::string);
	void Play(int);
	void Stop(int);
	bool IsOpen();
private:
	Mix_Music* music;

};


#endif