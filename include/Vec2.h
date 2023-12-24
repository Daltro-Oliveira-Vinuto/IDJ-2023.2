#include <iostream>
#include <cmath>



#ifndef VEC2_H
#define VEC2_H

class Vec2 {
public:
	Vec2();
	Vec2(int, int);
	Vec2(double, double);
	~Vec2();

	Vec2 operator + (const Vec2&);
	Vec2 operator - (const Vec2&);
	Vec2 operator * (const double&);

	friend std::ostream& operator << (std::ostream&, const Vec2&);

	Vec2 GetNormalized();
	double DistanceTo(const Vec2&);
	double GetAngleInDegrees();
	Vec2 Rotate(double);
	Vec2 RotateInDegrees(double);
	double DotProduct(const Vec2&);
	double AngleBetween(const Vec2&);

	static double ConvertRadianToDegree(double angle) {
	return (angle*180.0)/M_PI;
	}

	static double ConvertDegreeToRadian(double angle) {
		return (M_PI*angle)/180.0;
	}

	double x, y;
	double mod;
	double angle;

private:
	double GetMagnitude(double,double);
	double GetAngle(double, double);

};


#endif