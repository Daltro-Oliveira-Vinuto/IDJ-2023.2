#include <memory>

#include "Alien.h"
#include "Sprite.h"
#include "Game.h"
#include "InputManager.h"
#include "State.h"
#include "Game.h"


Alien::Alien(GameObject& associated, int nMinions): Component(associated) {

	std::string alienFilePath = "assets/img/alien.png";

	std::unique_ptr<Sprite> spriteOfAlien = 
		std::make_unique<Sprite>(associated,alienFilePath);

	Rect clip(0,0, spriteOfAlien->GetWidth(), spriteOfAlien->GetHeight());

	spriteOfAlien->SetClip(clip);

	/*
	int windowWidth = Game::GetInstance("",0,0).GetWidth();
	int windowHeight = Game::GetInstance("",0,0).GetHeight();
	Rect rect(windowWidth/2.0 - spriteOfAlien->GetWidth()/2.0, 
		windowHeight/2.0 - spriteOfAlien->GetHeight()/2.0, 
		spriteOfAlien->GetWidth(), 
		spriteOfAlien->GetHeight());
	*/
	Rect rect(512,300, 
		spriteOfAlien->GetWidth(), spriteOfAlien->GetHeight());

	associated.box = rect;

	associated.AddComponent(std::move(spriteOfAlien));

	this->speed = Vec2(100,100);
	this->hp = 100;
	this->minionArray = {};

}

Alien::~Alien() {
	this->minionArray.clear();
}

void Alien::Start() {
	// add one minion to the alien
	/*
	GameObject* minionGameObjectRawPtr = new GameObject();

	float arcOffSetDeg = 0;
	std::weak_ptr<GameObject> alienCenter =
			Game::GetInstance("",0,0).GetState().GetObjectPtr(&associated);

	std::unique_ptr<Minion> newMinion = 
		std::make_unique<Minion>(*minionGameObjectRawPtr, alienCenter, arcOffSetDeg);

	minionGameObjectRawPtr->AddComponent(std::move(newMinion));

	std::shared_ptr<GameObject> minionGameObject(
			Game::GetInstance("",0,0).GetState().AddObject(
				minionGameObjectRawPtr)
			);

	std::weak_ptr<GameObject> minionGameObjectWeak(minionGameObject);

	this->minionArray.push_back(minionGameObjectWeak);
	*/

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

	if (!(this->taskQueue.empty()) ) {
		Action action = this->taskQueue.front();

		if (action.type == ActionType::SHOOT) {
			this->taskQueue.pop();
		} else if (action.type == ActionType::MOVE) {
			Vec2 spaceVariation = this->speed*dt;
			float minimumDelta = 5.0;

			float distance = associated.box.GetCenter().DistanceTo(action.pos); 
			if (distance > minimumDelta) { 
				if(associated.box.GetCenter().x < action.pos.x) { 
					associated.box.x+=spaceVariation.x; }
				else if (associated.box.GetCenter().x > action.pos.x){
					 associated.box.x-= spaceVariation.x;

				} if(associated.box.GetCenter().y <	action.pos.y) { 
					associated.box.y+= spaceVariation.y;
				}else if (associated.box.GetCenter().y > action.pos.y) { 
					associated.box.y-=spaceVariation.y;
				} 
			} else 	{ 
				this->taskQueue.pop(); 
			}

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































