

#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject& associated,
			   float angle,
			   Vec2 speed,
			   int damage,
			   float maxDistance,
			   std::string spritePath): Component(associated) {


	associated.angleDeg = angle;

	this->damage = damage;

	this->speed = speed;

	this->distanceLeft = maxDistance;

	std::unique_ptr<Sprite> newBulletSprite = 
		std::make_unique<Sprite>(associated, spritePath);

	newBulletSprite->SetClip(Rect(0,0,
							 newBulletSprite->GetWidth(),
							 newBulletSprite->GetHeight()
							 	)
							);


	associated.AddComponent(std::move(newBulletSprite));

}


void Bullet::Update(float dt) {
	
	Vec2 vec2Speed = 
			Vec2(this->speed.x*dt,
				 this->speed.y*dt);

	associated.box = associated.box.AddVec2(vec2Speed);

	//std::cout << "associated.angleDeg: " << associated.angleDeg <<
	//	std::endl;

	this->distanceLeft-= vec2Speed.mod;

	if (this->distanceLeft <= 0) {
		associated.RequestDelete();
	}
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























