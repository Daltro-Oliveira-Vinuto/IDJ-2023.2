
#include "Alien.h"
#include "Sprite.h"
#include "Game.h"
#include "InputManager.h"


Alien::Alien(GameObject& associated, int nMinions): Component(associated) {
	std::string alienFilePath = "assets/img/alien.png";
	std::unique_ptr<Sprite> spriteOfAlien = 
		std::make_unique<Sprite>(associated,alienFilePath);
	int windowWidth = Game::GetInstance("",0,0).GetWidth();
	int windowHeight = Game::GetInstance("",0,0).GetHeight();

	Rect clip(0,0, spriteOfAlien->GetWidth(), spriteOfAlien->GetHeight());
	spriteOfAlien->SetClip(clip);
	Rect rect(windowWidth/2.0 - spriteOfAlien->GetWidth()/2.0, 
		windowHeight/2.0 - spriteOfAlien->GetHeight()/2.0, 
		spriteOfAlien->GetWidth(), 
		spriteOfAlien->GetHeight());

	associated.box = rect;

	associated.AddComponent(std::move(spriteOfAlien));

	this->speed = Vec2(1,1);
	this->hp = 100;
	this->minionArray = {};

}

Alien::~Alien() {
	this->minionArray.clear();
}

void Alien::Start() {

}

void Alien::Update(float dt) {
	associated.angleDeg+= 20*dt;

	ActionType typeOfAction;

	int mouseX = InputManager::GetInstance().GetMouseX();
	int mouseY = InputManager::GetInstance().GetMouseY();
	
	int posX, posY;
	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		typeOfAction = ActionType::SHOOT;

		posX = mouseX - Camera::pos.x;
		posY = mouseY - Camera::pos.y;
		this->taskQueue.push(Action(typeOfAction, posX, posY));

	}
	if (InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
		typeOfAction = ActionType::MOVE;

		posX = mouseX - Camera::pos.x;
		posY = mouseY - Camera::pos.y;

		this->taskQueue.push(Action(typeOfAction, posX, posY));
	}

	while (!(this->taskQueue.empty()) ) {
		Action action = this->taskQueue.front();
		this->taskQueue.pop();

		if (action.type == ActionType::SHOOT) {

		} else if (action.type == ActionType::MOVE) {
			Vec2 spaceVariation = this->speed*dt;

			posX = mouseX - Camera::pos.x;
			posY = mouseY - Camera::pos.y;

			spaceVariation = spaceVariation + Vec2(posX, posY);

			associated.box.x = spaceVariation.x;
			associated.box.y = spaceVariation.y;

		}
	}

	if (this->hp <= 0) {
		associated.RequestDelete();
	}
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
	bool typeMatch = false;
	if ("Alien" == type) {
		typeMatch = true;
	} else {
		typeMatch = false;
	}

	return typeMatch;
}































