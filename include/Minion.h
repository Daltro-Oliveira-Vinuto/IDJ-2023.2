#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#ifndef MINION_H
#define MINION_H

class Minion: public Component {
public:
	Minion(GameObject& associated,
			std::weak_ptr< GameObject > alienCenter,
			float arcOffsetDeg);

	void Update(float);
	void Render();
	bool Is(std::string);
	void Start();
	void Shoot(Vec2 target);

private:
	//GameObject& alienCenter;
	std::weak_ptr< GameObject> alienCenter;
	
	float arc;
	float scale;
};


#endif















