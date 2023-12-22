#include "Face.h"
#include "Sound.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "Rect.h"


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
	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		//int mouseX = Game::GetInstance("",0,0).GetInput().GetMouseX();
		//int mouseY = Game::GetInstance("",0,0).GetInput().GetMouseY();

		int mouseX = InputManager::GetInstance().GetMouseX();
		int mouseY = InputManager::GetInstance().GetMouseY();
		//printf("Mouse clique at positon: (%d, %d)\n", mouseX, mouseY);

		//Vec2 vec2_cliqued(mouseX, mouseY);
		Vec2 vec2_cliqued(mouseX, mouseY);
		vec2_cliqued = vec2_cliqued - Camera::pos;
		//Rect boxAfterCamera = associated.box.AddVec2(Camera::pos*(1));
  		
  		//printf("associated.box: %.2lf, %.2lf\n", associated.box.x, associated.box.y);

		//printf("vector cliqued: (%.2lf, %2.lf)\n", vec2_cliqued.x, vec2_cliqued.y);
		if(associated.box.ContainVec2( vec2_cliqued) ) {
			
			this->Damage(int( std::rand() % 10 + 10 ) );

		}
				
	}



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