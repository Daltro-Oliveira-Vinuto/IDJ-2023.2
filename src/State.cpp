#include "State.h"
#include "SDL.h"

// calling correctly the constructor of a class member is SUPER IMPORTANT!
State::State(): bg("./assets/img/ocean.jpg"), music("./assets/audio/stageState.ogg") {
	quitRequested = false;
	//this->LoadAssets(renderer);
	music.Play(-1);
}

void State::LoadAssets() {
	
}

void State::Update(float dt) {

	if (SDL_QuitRequested()) {
		quitRequested = true;
	}
}

void State::Render() {

	bg.SetClip(0, 0, bg.GetWidth(), bg.GetHeight());
	bg.Render( 0, 0);
}

bool State::QuitRequested() {

	return quitRequested;
}