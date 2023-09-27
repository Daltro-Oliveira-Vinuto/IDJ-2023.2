
#include "GameObject.h"
#include "Component.h"
#include "Sound.h"
#include "Game.h"
#include <vector>
#include "SDL.h"


GameObject::GameObject() {
	isDead = false;
}

GameObject::~GameObject() {
	//std::vector<std::unique_ptr<Component>>::iterator iter = components.begin();
	//int sound_time = 0;
	//int delay = 1000.0/Game::GetInstance("",0,0).GetFPS();
	//Component* component;

	/*
	for(int i = components.size()-1; i >= 0; --i) {
		component = (Component*)(components[i].get());
		if (component->Is("Sound") ){
			Sound* sound = (Sound*)component;
			if (  sound->sound_time < TIME_LIMIT ){
				sound->sound_time+= delay;
				sound_time = sound->sound_time;
			}
		}
	}

	if (sound_time >= TIME_LIMIT) {
		// not necessary once components become a vector of unique_ptr 
		
		for(int i = components.size()-1; i>=0; --i) {
			delete *(iter+i);
		}
	

		components.clear();
	}
	*/

	components.clear();


}

void GameObject::Update(float dt) {
	for(unsigned int i = 0; i < components.size(); i++) {
		Component* component = (Component*)(components[i].get());
		component->Update(0);
	}
}

void GameObject::Render() {
	/*
	for(std::vector<Component*>::iterator it=components.begin(); it!=components.end(); it++) {
		(*it)->Render();
	}
	*/
	for(unsigned int i = 0; i < components.size(); i++) {
		Component* component = (Component*)(components[i].get());
		component->Render();
	}
}

bool GameObject::IsDead() {
	return isDead;
}

void GameObject::RequestDelete() {
	isDead = true;
}

void GameObject::AddComponent(std::unique_ptr<Component> component) {
	components.emplace_back(std::move(component));
}

void GameObject::RemoveComponent(Component* component) {
	std::vector<std::unique_ptr<Component>>::iterator begin = components.begin();

	for(unsigned i = 0; i != components.size(); i++) {
		if ( (Component*)(components[i].get() ) == component ) {
			components.erase(begin+i);
			break;
		}
	}
}

Component* GameObject::GetComponent(std::string type) {
	Component* component = NULL;
	std::vector<std::unique_ptr<Component>>::iterator it;

	for(unsigned i = 0; i != components.size(); i++) {
		if ((components[i])->Is(type)) {
			component = (Component*)(components[i].get());
		}
	}

	return component;
}


Component* GameObject::ReleaseComponent(std::string type) {
	Component* component = NULL;
	for(unsigned i = 0; i < components.size(); i++) {
		if (components[i]->Is(type)) {
			component = components[i].release();
		}
	}

	return component;
}