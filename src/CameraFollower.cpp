#include "CameraFollower.h"
#include "Camera.h"


CameraFollower::CameraFollower(GameObject& associated): Component(associated) {

}

void CameraFollower::Update(float dt) {
	associated.box.x = -Camera::pos.x;
	associated.box.y = -Camera::pos.y;
	
	//printf("associated.box: %.2lf, %.2lf\n", associated.box.x, associated.box.y);
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














