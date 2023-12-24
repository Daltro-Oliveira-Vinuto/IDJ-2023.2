

#include "Minion.h"
#include "Sprite.h"

Minion::Minion(GameObject& associated,
			  std::weak_ptr< GameObject> alienCenter,
			  float arcOffsetDeg = 0): Component(associated), 
				alienCenter(*(alienCenter.lock().get()) ) {

			
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

			Rect rect(this->alienCenter.box.x, this->alienCenter.box.y,
						spriteMinion->GetWidth(), spriteMinion->GetHeight());

			associated.box = rect;

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


















