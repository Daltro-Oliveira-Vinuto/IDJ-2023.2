

#include "Bullet.h"

Bullet::Bullet(GameObject& associated,
			   float angle,
			   float speed,
			   int damage,
			   float maxDistance,
			   std::string sprite): Component(associated) {

}


void Bullet::Update(float dt) {

}

void Bullet::Render() {

}

bool Bullet::Is(std::string type) {
	bool typeMatch = false;

	if ("Bullet" == type) {
		typeMatch = true;
	} else {
		typeMatch = false;
	}

	return typeMatch;
}

int Bullet::GetDamage() {

	return this->damage;
}























