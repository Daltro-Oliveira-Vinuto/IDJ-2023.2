
#include <time.h>
#include <stdlib.h>

#include "Minion.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Game.h"

Minion::Minion(GameObject& associated,
			  std::weak_ptr< GameObject> alienCenter,
			  float arcOffsetDeg = 0): Component(associated), 
				alienCenter(alienCenter) {

			srand(time(0));

			float minionRandomSize = (rand()%10+1)/10.0 + 0.6;

			if (minionRandomSize >= 1.1) {
				minionRandomSize = 1.1;
			}

			this->arc = arcOffsetDeg;

			std::unique_ptr<Sprite> spriteMinion =
				 std::make_unique<Sprite>(associated,"assets/img/minion.png");

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
					radius+spriteMinion->GetWidth()*minionRandomSize/2.0,
					radius+spriteMinion->GetHeight()*minionRandomSize/2.0);

				Vec2 centerVec2 = alienCenter.lock()->box.GetCenter();

				baseVec2 = baseVec2.RotateInDegrees(arcOffsetDeg);

				Vec2 finalPosVec2 = centerVec2 + baseVec2;

		
				finalPosVec2 = 
					finalPosVec2 - 
						Vec2(
							spriteMinion->GetWidth()*minionRandomSize/2.0
							,spriteMinion->GetHeight()*minionRandomSize/2.0
												);
												 
				rectX = finalPosVec2.x;
				rectY = finalPosVec2.y;


			} else {
				associated.RequestDelete();
			}

			Rect rect(rectX, rectY,
						spriteMinion->GetWidth()*minionRandomSize
						, spriteMinion->GetHeight()*minionRandomSize);

			associated.box = rect;

			spriteMinion->SetClipDest(rect);

			//std::cout << associated.box << std::endl;

			associated.AddComponent(std::move(spriteMinion));
}

void Minion::Update(float dt) {
	associated.angleDeg += -(10*dt);

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
			radius+associated.box.w/2.0,
			radius+associated.box.h/2.0);

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

}


















