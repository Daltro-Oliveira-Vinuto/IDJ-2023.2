#include "Camera.h"
#include "Game.h"

/*
Camera::Camera() {

}

Camera::~Camera() {

}
*/

void Camera::Follow(GameObject* newFocus) {
	Camera::focus = newFocus;
}

void Camera::Unfollow() {
	Camera::focus = nullptr;
}

void Camera::Update(float dt) {
	if (nullptr == Camera::focus) {
		Vec2 spaceVariation = Camera::speed*dt;

		if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
			Camera::pos.x+= spaceVariation.x;
		}
		if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
			Camera::pos.x-= spaceVariation.x;
		}
		if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
			Camera::pos.y+= spaceVariation.y;
		}
		if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
			Camera::pos.y-= spaceVariation.y;	
		}
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
Vec2 Camera::speed = Vec2(500,500); // static variable
GameObject* Camera::focus = nullptr; // static variable
















