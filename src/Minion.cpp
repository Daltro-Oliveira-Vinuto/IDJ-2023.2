
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "Minion.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Game.h"
#include "Bullet.h"

Minion::Minion(GameObject& associated,
			  std::weak_ptr< GameObject> alienCenter,
			  float arcOffsetDeg = 0): Component(associated), 
				alienCenter(alienCenter) {

			float minionRandomScale = (rand()%100+1)/100.0 + 0.5;

			if (minionRandomScale >= 1.2) {
				minionRandomScale = 1.2;
			}

			this->scale = minionRandomScale;

			this->arc = arcOffsetDeg;

			std::unique_ptr<Sprite> spriteMinion =
				 std::make_unique<Sprite>(associated,"assets/img/minion.png");

			spriteMinion->SetScale(minionRandomScale,
								   minionRandomScale);

			Rect minionClip(0,0, 
				spriteMinion->GetWidth(), spriteMinion->GetHeight());

			spriteMinion->SetClip(minionClip);

			float rectX = 0, rectY = 0;

			if ( ! alienCenter.expired() ) {
				float radius;

				if (alienCenter.lock()->box.w >=
					alienCenter.lock()->box.h) {
					radius = alienCenter.lock()->box.w/2.0;
				} else {
					radius = alienCenter.lock()->box.h/2.0;
				}

				Vec2 baseVec2(
					radius+spriteMinion->GetWidth()*minionRandomScale/2.0,
					radius+spriteMinion->GetHeight()*minionRandomScale/2.0);

				Vec2 centerVec2 = alienCenter.lock()->box.GetCenter();

				baseVec2 = baseVec2.RotateInDegrees(arcOffsetDeg);

				Vec2 finalPosVec2 = centerVec2 + baseVec2;

		
				finalPosVec2 = 
					finalPosVec2 - 
						Vec2(
							(spriteMinion->GetWidth()*minionRandomScale)/2.0
							,(spriteMinion->GetHeight()*minionRandomScale)/2.0
												);
												 
				rectX = finalPosVec2.x;
				rectY = finalPosVec2.y;


			} else {
				associated.RequestDelete();
			}

			Rect rect(rectX, rectY,
						spriteMinion->GetWidth()*minionRandomScale
						, spriteMinion->GetHeight()*minionRandomScale);

			associated.box = rect;

			spriteMinion->SetClipDest(rect);

			//std::cout << associated.box << std::endl;

			associated.AddComponent(std::move(spriteMinion));
}

void Minion::Update(float dt) {
	
	associated.angleDeg += -(20*dt);

	if ( alienCenter.expired() ) {
		associated.RequestDelete();
	} else {
		
		float radius, rectX, rectY;

		if (alienCenter.lock()->box.w >=
			alienCenter.lock()->box.h) {
			radius = alienCenter.lock()->box.w/2.0;
		} else {
			radius = alienCenter.lock()->box.h/2.0;
		}

		Vec2 baseVec2(
			radius+(associated.box.w)/2.0,
			radius+(associated.box.h)/2.0);

		Vec2 centerVec2 = alienCenter.lock()->box.GetCenter();

		baseVec2 = baseVec2.RotateInDegrees(associated.angleDeg);
		baseVec2 = baseVec2.RotateInDegrees(this->arc);

		Vec2 finalPosVec2 = centerVec2 + baseVec2;


		finalPosVec2 = 
			finalPosVec2 - 
				Vec2(
					associated.box.w/2.0
					,associated.box.h/2.0
										);
										 
		rectX = finalPosVec2.x;
		rectY = finalPosVec2.y;

		associated.box.x = rectX;
		associated.box.y = rectY;
	}

}

void Minion::Start() {
	this->started = true;
}

void Minion::Render() {
	
}

bool Minion::Is(std::string type) {
	bool typeMatch = false;

	if ("Minion" == type) {
		typeMatch = true;
	} else {
		typeMatch = false;
	}

	return typeMatch;
}

void Minion::Shoot(Vec2 target) {
	//printf("shooted!\n");
	int damage = 100;
	int maxDistance = sqrt(Game::GetInstance("",0,0).GetWidth()*
						  Game::GetInstance("",0,0).GetWidth()
						  +
						  Game::GetInstance("",0,0).GetHeight()*
						  Game::GetInstance("",0,0).GetHeight()
						  );

		;
	float speed = 200;
	Vec2 bulletSpeed;
	std::string spritePath = "assets/img/minionbullet1.png";

	Vec2 vec2Difference = target - associated.box.GetCenter();
	vec2Difference = vec2Difference.GetNormalized();

	float shootAngle = vec2Difference.angle;

	bulletSpeed = vec2Difference*speed;

	shootAngle = Vec2::ConvertRadianToDegree(shootAngle);

	//std::cout << "shoot angle: " << 
	//	Vec2::ConvertRadianToDegree(shootAngle) << std::endl;

	GameObject* bulletGameObject = new GameObject();

	bulletGameObject->box.x = associated.box.GetCenter().x;
	bulletGameObject->box.y = associated.box.GetCenter().y;

	std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>(
		*bulletGameObject, 
		shootAngle,
		bulletSpeed,
		damage,
		maxDistance,
		spritePath);

	bulletGameObject->AddComponent(std::move(newBullet));

	Game::GetInstance("",0,0).GetState().AddObject(bulletGameObject);
}


















