
#include "InputManager.h"
#include "SDL.h"
#include <iostream>

InputManager::InputManager() {
	// start mouse state and update
	const unsigned numberOfMouseStates = 6;
	for(unsigned i = 0; i <numberOfMouseStates; i++) {
		this->mouseState[i] = false;
		this->mouseUpdate[i] = 0;
	}

	this->quitRequested = false;
	this->updateCounter = 0;
	this->mouseX = 0;
	this->mouseY = 0;
}


InputManager::~InputManager() {
	keyState.clear();
	keyUpdate.clear();
}

void InputManager::Update() {
	SDL_Event event;

	this->updateCounter++;
	while(SDL_PollEvent(&event)) {

		SDL_GetMouseState(&(this->mouseX), &(this->mouseY));
		this->quitRequested = false;

		switch(event.type) {
			case SDL_QUIT:
				this->quitRequested = true;
				break;

			case SDL_KEYDOWN:
				if (event.key.repeat != 1) {
					//printf("sdl_keydown\n");
					this->keyState[event.key.keysym.sym] = true;
					this->keyUpdate[event.key.keysym.sym] = updateCounter;

				}

				break;

			case SDL_KEYUP:
				//printf("sdl_keyup\n");
				this->keyState[event.key.keysym.sym] = false;
				this->keyUpdate[event.key.keysym.sym] = updateCounter;
				//this->updateCounter = 0;

				break;

			case SDL_MOUSEBUTTONDOWN:
				//printf("sdl_mousebuttondown\n");
				if (event.button.clicks==1) {
					this->mouseState[event.button.button] = true;
					this->mouseUpdate[event.button.button] = updateCounter;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				//printf("sdl_mousebuttonup\n");
				this->mouseState[event.button.button] = false;
				this->mouseUpdate[event.button.button] = updateCounter;
				//this->updateCounter = 0;
				break;

			default:
				//printf("Invalid event.type!\n");
				break;
		}

		if (this->quitRequested) {
			break;
		}
	}

}

bool InputManager::KeyPress(int key) {
	bool keyWasPressed;

	std::unordered_map<int,int>::iterator it;
	it = this->keyUpdate.find(key);

	if (it == this->keyUpdate.end()) {
		keyWasPressed = false;
	} else {
		if (it->second == this->updateCounter &&
			keyState.find(key)->second == true) {
			keyWasPressed = true;
		} else {
			keyWasPressed = false;
		}
	}

	return keyWasPressed;
}

bool InputManager::KeyRelease(int key) {
	bool keyWasReleased;

	std::unordered_map<int,int>::iterator it;
	it = this->keyUpdate.find(key);

	if (it == this->keyUpdate.end()) {
		keyWasReleased = false;
	} else {
		if (it->second == this->updateCounter &&
			keyState.find(key)->second == false) {
			keyWasReleased = true;
		} else {
			keyWasReleased = false;
		}
	}

	return keyWasReleased;
}

bool InputManager::IsKeyDown(int key) {
	bool keyIsDown = false;

	std::unordered_map<int,bool>::iterator it;
	it = this->keyState.find(key);

	if (it == this->keyState.end()) {
		keyIsDown = false;
	} else {
		keyIsDown = it->second;
	}

	return keyIsDown;
}


bool InputManager::MousePress(int button) {
	bool mouseWasPressed;

	if (this->mouseUpdate[button] == this->updateCounter &&
		this->mouseState[button] == true) {
		mouseWasPressed = true;
	} else {
		mouseWasPressed = false;
	}

	return mouseWasPressed;
}

bool InputManager::MouseRelease(int button) {
	bool mouseWasReleased;

	if (this->mouseUpdate[button] == this->updateCounter &&
		this->mouseState[button] == false) {
		mouseWasReleased = true;
	} else {
		mouseWasReleased = false;
	}

	return mouseWasReleased;
}

bool InputManager::IsMouseDown(int button) {
	bool mouse = false;

	mouse = this->mouseState[button];

	return mouse;
}


int InputManager::GetMouseX() {
	
	return this->mouseX;
}

int InputManager::GetMouseY() {
	
	return this->mouseY;
}

bool InputManager::QuitRequested() {

	return this->quitRequested;
}

InputManager& InputManager::GetInstance() {
	static InputManager input =  InputManager();

	//std::cout <<"Input address: " << &input << std::endl;
	return input;
}








































