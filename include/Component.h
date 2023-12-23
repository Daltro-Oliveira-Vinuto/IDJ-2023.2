
#include <string>

#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component { // abstract class
public:
	Component(GameObject& associated): associated(associated) {};
	virtual ~Component() = default;
	Component(const Component&) = delete;
	const Component& operator=(const Component&) = delete;

	virtual void Update(float) = 0; // virtual pure
	virtual void Render() = 0; // virtual pure
	virtual bool Is(std::string) = 0; // virtual pure;
	virtual void Start() {printf("Component started!\n");}; // empy body
	bool started = false;
protected:
	GameObject& associated;
};

#endif