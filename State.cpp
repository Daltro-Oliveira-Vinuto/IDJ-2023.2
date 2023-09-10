#include "State.h"


State::State() {
	quitRequested = false;
	bg = Sprite(); // what parameters should I pass to Sprite?
}

void State::LoadAssets() {

}

void State::Update(float dt) {

	if (QuitRequested()) {
		quitRequested = true;
	}
}

void State::Render() {

	bg.Render(0,0);
}

bool State::QuitRequested() {

	return quitRequested;
}