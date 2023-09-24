
#include <string>

#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component { // abstract class
public:
	Component(GameObject& associated): associated(associated) {};
	virtual ~Component();

	virtual void Update(float) = 0; // virtual pure
	virtual void Render() = 0; // virtual pure
	virtual bool Is(std::string) = 0; // virtual pure;
protected:
	GameObject& associated;
};

#endif