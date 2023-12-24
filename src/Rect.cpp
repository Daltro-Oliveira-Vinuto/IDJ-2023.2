#include "Rect.h"


Rect::Rect() {
	x = 0; y = 0; w = 0; h = 0;
}

Rect::Rect(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rect::~Rect() {

}


std::ostream& operator << (std::ostream& output, const Rect& rect) {
	output << "(x, y, h, w) = (" << rect.x << " , " << rect.y << " , "
	 << rect.w << " , " << rect.h << ")" << std::endl;
	return output;

}

Rect Rect::AddVec2(const Vec2& vec2) {
	Vec2 v_result;
	Rect r_result(x,y, w, h);

	v_result.x = x + vec2.x;
	v_result.y = y + vec2.y;

	r_result.x = v_result.x;
	r_result.y = v_result.y;

	return r_result;
}

Vec2 Rect::GetCenter() {
	Vec2 v_result(x+w/2.0, y+h/2.0);

	return v_result;
}

double Rect::DistanceTo(Rect other) {
	Vec2 other_center = other.GetCenter();

	return this->GetCenter().DistanceTo(other_center);
}

bool Rect::ContainVec2(const Vec2& vec2) {
	bool contain = true;

	if (vec2.x < x || vec2.x > x+w) {
		contain = false;
	}

	if (vec2.y < y || vec2.y > y + h) {
		contain = false;
	}


	return contain;
}