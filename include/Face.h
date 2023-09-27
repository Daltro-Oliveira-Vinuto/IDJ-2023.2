#include "GameObject.h"
#include <string>

#ifndef FACE_H
#define FACE_H


class Face : public Component {
public:
	Face(GameObject&);

	void Damage(int);

	void Update(float);
	void Render();
	bool Is(std::string);
private:
	int hitpoints;
};


#endif