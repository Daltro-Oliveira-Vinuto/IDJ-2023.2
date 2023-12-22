
#include "InputManager.h"
#include "Vec2.h"
#include "GameObject.h"

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
	Camera() {}; // empty constructor
	~Camera() {}; // empty destructor

	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);

	static Vec2 pos;
	static Vec2 speed;
private:
	static GameObject* focus;
};

#endif



