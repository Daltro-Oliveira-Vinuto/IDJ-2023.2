#include "Face.h"
#include "Sound.h"



Face::Face(GameObject& associated) : Component(associated) {
	hitpoints = 10;
}

void Face::Damage(int damage) {
	hitpoints-= damage;
	if (hitpoints <= 0 ) {

		Sound* sound = (Sound*)associated.GetComponent("Sound");
		sound->Play(0);

		associated.RequestDelete();

	}
}


void Face::Update(float dt) {

}

void Face::Render() {

}

bool Face::Is(std::string type) {
	bool is = false;

	if (type == "Face") {
		is = true;
	}

	return is;
}