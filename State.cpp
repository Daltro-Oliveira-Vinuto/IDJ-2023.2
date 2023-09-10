#include "State.h"

// calling correctly the constructor of a class member is SUPER IMPORTANT!
State::State(SDL_Renderer* renderer): bg(renderer, "assets/img/ocean.jpg") {
	quitRequested = false;
	//this->LoadAssets(renderer);
}

void State::LoadAssets() {
	
}

void State::Update(float dt) {

	if (SDL_QuitRequested()) {
		quitRequested = true;
	}
}

void State::Render(SDL_Renderer* renderer) {

	bg.SetClip(0, 0, bg.GetWidth(), bg.GetHeight());
	bg.Render(renderer, 0, 0);
}

bool State::QuitRequested() {

	return quitRequested;
}