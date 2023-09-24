#include <iostream>
#include "Vec2.h"


#ifndef RECT_H
#define RECT_H

class Rect {
public:
	Rect();
	Rect(int, int, int, int);

	~Rect();

	friend std::ostream& operator << (std::ostream& , const Rect&);


	Rect AddVec2(const Vec2&);
	Vec2 GetCenter();
	double DistanceTo(Rect);
	bool ContainVec2(const Vec2&);

	int x, y, w, h;
};

#endif 