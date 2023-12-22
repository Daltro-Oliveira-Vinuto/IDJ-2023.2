#include "Component.h"
#include "GameObject.h"
#include <string>

#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

class CameraFollower: public Component {
public:
	CameraFollower(GameObject& associated);

	void Update(float dt);
	void Render();
	bool Is(std::string type);

private:

};


#endif


