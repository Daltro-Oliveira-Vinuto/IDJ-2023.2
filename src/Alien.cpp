#include <memory>
#include <time.h>
#include <stdlib.h>

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

	this->speed = Vec2(200,200);
	this->hp = 100;
	this->minionArray = {};
	this->numberOfMinions = nMinions;

}

Alien::~Alien() {
	this->minionArray.clear();
}

void Alien::Start() {
	
	GameObject* auxGO = &associated;

	std::weak_ptr<GameObject> alienCenter = 
				Game::GetInstance("",0,0).GetState().GetObjectPtr(auxGO);

	
	float arcOffsetDeg = 0;
	int incrementOfArc = (360.0/this->numberOfMinions);
	for(int i = 0; i < this->numberOfMinions; i++) {

		arcOffsetDeg = -incrementOfArc*i;

		GameObject* minionGameObject = new GameObject();
			
		std::unique_ptr<Minion> minionComponent = 
			std::make_unique<Minion>(*minionGameObject,
									alienCenter, arcOffsetDeg);

		minionGameObject->AddComponent(std::move(minionComponent));
		
		std::weak_ptr<GameObject> newWeakMinionGO =
			Game::GetInstance("",0,0).GetState().AddObject(minionGameObject);
		
		this->minionArray.push_back(newWeakMinionGO);
	}

	this->started = true;
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
			bool reachedDestination = false;

			Vec2 vec2Difference = action.pos - associated.box.GetCenter();


			Vec2 vec2DiffNormalized = vec2Difference.GetNormalized();

			Vec2 vec2Speed = vec2DiffNormalized*dt;

			vec2Speed =
				 Vec2(
				 	vec2Speed.x*(this->speed.x), 
				 	vec2Speed.y*(this->speed.y));
						 
			float distance = 
				action.pos.DistanceTo(
								associated.box.GetCenter());

			if (distance > 1.0) { 

				if (distance > vec2Speed.x && distance > vec2Speed.y) {
					associated.box = associated.box.AddVec2(vec2Speed);
					
				} else {
					associated.box.x = action.pos.x - associated.box.w/2.0;
					associated.box.y = action.pos.y - associated.box.h/2.0;

				}

				// update the position of the minions
				for(unsigned i = 0; i < this->minionArray.size(); i++) {
					if ( ! (*(this->minionArray.begin()+i)).expired() ) {
						(*(this->minionArray.begin()+i)).lock()->box =
							(*(this->minionArray.begin()+i)).lock()->box.
							AddVec2(vec2Speed);
					}
				}
				
			} else { 
				
				reachedDestination = true;
			}

			if (reachedDestination) {
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































