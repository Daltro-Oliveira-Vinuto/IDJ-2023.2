#include <vector>
#include <memory>
#include "Component.h"
#include "Rect.h"


#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
public:
	GameObject();
	~GameObject();
	//GameObject(const GameObject&) = delete;
	//const GameObject& operator=(const GameObject&) = delete;
	void Start();

	void Update(float);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(std::unique_ptr<Component>);
	void RemoveComponent(Component*);
	Component* GetComponent(std::string);
	Component* ReleaseComponent(std::string);

	Rect box;
	bool started;
	double angleDeg;
	
private:
	std::vector<std::unique_ptr<Component>> components;
	bool isDead;

};


#endif