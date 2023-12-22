#include "CameraFollower.h"
#include "Camera.h"


CameraFollower::CameraFollower(GameObject& go): Component(go) {

}

void CameraFollower::Update(float dt) {
	this->associated.box.x = Camera::pos.x * dt;
	this->associated.box.y = Camera::pos.y * dt;
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(std::string type) {
	bool typeMatch = false;

	if ("CameraFollower" == type) {
		typeMatch = true;
	}else {
		typeMatch = false;
	}

	return typeMatch;
}














