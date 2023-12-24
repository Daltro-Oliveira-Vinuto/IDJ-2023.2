
#include <time.h>

#include "Minion.h"
#include "Sprite.h"
#include "Vec2.h"

Minion::Minion(GameObject& associated,
			  std::weak_ptr< GameObject> alienCenter,
			  float arcOffsetDeg = 0): Component(associated), 
				alienCenter(*(alienCenter.lock().get()) ) {

			srand(time(NULL));

			float minionRandomSize = (rand()%10+1)/10.0 + 0.6;

			if (minionRandomSize >= 1.1) {
				minionRandomSize = 1.1;
			}


			//std::cout << minionRandomSize << std::endl;

			//std::cout << "&associated inside minion: " << &associated << std::endl;
			
			/*
			std::cout << " &alienCenter in minion: " <<
					&(this->alienCenter) << std::endl;
			*/
			this->arc = arcOffsetDeg;

			std::unique_ptr<Sprite> spriteMinion =
				 std::make_unique<Sprite>(associated,"assets/img/minion.png");

			Rect minionClip(0,0, 
				spriteMinion->GetWidth(), spriteMinion->GetHeight());

			spriteMinion->SetClip(minionClip);

			float x= 0, y= 0;

			x = this->alienCenter.box.x; y = this->alienCenter.box.y;

			Vec2 vec2Rotated(x,y);

			vec2Rotated = vec2Rotated.RotateInDegrees(arcOffsetDeg);

			x = vec2Rotated.x; y = vec2Rotated.y;

			Rect rect(x, y,
						spriteMinion->GetWidth()*minionRandomSize
						, spriteMinion->GetHeight()*minionRandomSize);

			associated.box = rect;

			spriteMinion->SetClipDest(rect);

			associated.AddComponent(std::move(spriteMinion));
}

void Minion::Update(float dt) {

	associated.box.x = alienCenter.box.x - alienCenter.box.w/2.0;
	associated.box.y = alienCenter.box.y - alienCenter.box.h/2.0;

	associated.angleDeg+= 20*dt;
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


















