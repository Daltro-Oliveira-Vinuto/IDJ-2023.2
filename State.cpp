#include "State.h"


State::State() {
	quitRequested = false;
	bg = Sprite(); // what parameters should I pass to Sprite?
	//this->LoadAssets();
}

void State::LoadAssets() {

}

void State::Update(float dt) {

	if (SDL_QuitRequested()) {
		quitRequested = true;
	}
}

void State::Render() {

	bg.Render(0,0);
}

bool State::QuitRequested() {

	return quitRequested;
}