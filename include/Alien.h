#include <memory>
#include <queue>
#include <vector>
#include <string>

#include "GameObject.h"
#include "Vec2.h"
#include "Component.h"
#include "Minion.h"

#ifndef ALIEN_H
#define ALIEN_H

class Alien: public Component {
public:
	Alien(GameObject& associated, int nMnions);
	~Alien();

	void Start();
	void Update(float);
	void Render();
	bool Is(std::string);


private:
	enum class ActionType {MOVE, SHOOT};

	class Action {
		public:
			Action (ActionType actionType, float x, float y) {
				pos = Vec2(x, y);
				type = actionType;
			};


			ActionType type;
			Vec2 pos;
	};

	std::queue<Action> taskQueue;

	Vec2 speed;
	int hp;

	std::vector< std::weak_ptr<GameObject> > minionArray;
	int numberOfMinions;
};

#endif


















