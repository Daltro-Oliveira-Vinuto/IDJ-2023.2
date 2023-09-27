#include <string>

#include "SDL_mixer.h"

#include "Component.h"


#ifndef SOUND_H
#define SOUND_H

class Sound : public Component {
public:
	Sound(GameObject&);
	Sound(GameObject&, std::string);
	~Sound();

	void Play(int);
	void Stop();
	void Open(std::string);
	bool IsOpen();

	void Update(float);
	void Render();
	bool Is(std::string);

private:
	Mix_Chunk* chunk = NULL;
	int channel;
};


#endif