#include <vector>
#include "Component.h"


#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
public:
	GameObject();
	~GameObject();

private:
	std::vector<Component*> components;
	bool isDead;
};


#endif