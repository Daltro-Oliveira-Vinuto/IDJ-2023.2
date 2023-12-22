#include "Camera.h"
#include "Game.h"


void Camera::Follow(GameObject* newFocus) {
	Camera::focus = newFocus;
}

void Camera::Unfollow() {
	Camera::focus = nullptr;
}

void Camera::Update(float dt) {
	if (nullptr == Camera::focus) {
		Vec2 spaceVariation = Camera::speed*(dt*300);
		//printf("Space variation: (%.2lf, %.2lf)\n", spaceVariation.x, spaceVariation.y);

		if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
			Camera::pos.x = Camera::pos.x + spaceVariation.x;
		}
		if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
			Camera::pos.x = Camera::pos.x - spaceVariation.x;
		}
		if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
			Camera::pos.y = Camera::pos.y + spaceVariation.y;
		}
		if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
			Camera::pos.y = Camera::pos.y - spaceVariation.y;	
		}

		//printf("Camera::pos: (%.2lf, %.2lf)\n", Camera::pos.x, Camera::pos.y);
	}
	else {
		Camera::pos.x = 
		Game::GetInstance("",0,0).GetWidth()/2.0 -
			Camera::focus->box.w/2.0;
		Camera::pos.y = 
		Game::GetInstance("",0,0).GetHeight()/2.0 -
			Camera::focus->box.h/2.0;
	}
	
}

Vec2 Camera::pos = Vec2(0,0); // static variable
Vec2 Camera::speed = Vec2(1,1); // static variable
GameObject* Camera::focus = nullptr; // static variable
















