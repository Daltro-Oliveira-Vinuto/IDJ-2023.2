
#include "Vec2.h"
#include "Rect.h"
#include <math.h>


Vec2::Vec2() {
	x = 0; y = 0;
	mod = 0; angle = 0;
}

Vec2::Vec2(int x, int y) {
	this->x = x; this->y = y;
	this->mod = this->GetMagnitude(this->x, this->y);
	this->angle = this->GetAngle(this->x, this->y);
}

Vec2::Vec2(double x, double y) {
	this->x = x; 
	this->y = y;
	this->mod = this->GetMagnitude(x, y);
	this->angle = this->GetAngle(this->x, this->y);

}

Vec2::~Vec2() {

}

double Vec2::GetMagnitude(double x, double y) {
	double magnitude = sqrt(x*x + y*y);
	//std::cout << "magnitude is: " << magnitude << std::endl;
	return magnitude;
}

double Vec2::GetAngle(double x, double y) {
	double angle;

	angle = atan2(y, x);

	return angle;
}


Vec2 Vec2::operator + (const Vec2& other) {
	float x, y;

	x = this->x + other.x;
	y = this->y + other.y;

	Vec2 v_result(x,y);
	
	return v_result;
}

Vec2 Vec2::operator - (const Vec2& other) {
	float x, y;
	
	x = this->x - other.x;
	y = this->y - other.y;

	Vec2 v_result(x, y);

	return v_result;
}

Vec2 Vec2::operator * (const double& value) {
	Vec2 v_result(value*x, value*y);

	return v_result;
}


std::ostream& operator << (std::ostream& output, const Vec2& vec2) {
	output << "(x, y, mod, angle) = ( " << vec2.x << " , " 
									   << vec2.y << " , " 
									   << vec2.mod << " , "
									   << vec2.angle << " )"
									   << std::endl;
	return output;
}

Vec2 Vec2::GetNormalized() {
	Vec2 v_normalized(this->x/this->mod, this->y/this->mod);

	//std::cout << "v_normalized: " << v_normalized << std::endl;
	return v_normalized;
}

double Vec2::DistanceTo(const Vec2& other) {
	double distance;

	distance = this->GetMagnitude(x-other.x, y-other.y);

	return distance;
}

Vec2 Vec2::Rotate(double angle) {
	float newX, newY;
	newX = this->x*cos(angle) - this->y*sin(angle);
	newY = this->y*cos(angle) + this->x*sin(angle);

	return Vec2(newX, newY);
}

double Vec2::DotProduct(const Vec2& other) {
	double dot_product = x*other.x + y*other.y;

	return dot_product;
}

double Vec2::AngleBetween(const Vec2& other) {
	double dot_product = this->DotProduct(other);
	double divisor = mod*other.mod;
	double quotient = 0;
	double angle;

	if (divisor != 0) {
		quotient = dot_product/divisor;
	} else printf("Error! Division by Zero!\n");

	angle = acos(quotient);

	return angle;
}


Vec2 Vec2::RotateInDegrees(double angle) {
	double radianAngle = Vec2::ConvertDegreeToRadian(angle);

	return Vec2(this->x, this->y).Rotate(radianAngle);
}















