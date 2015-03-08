#pragma once
#include <string>
class Vector3
{
private:
	double x, y, z;

public:
	Vector3();
	Vector3(double, double, double);
	~Vector3();

	Vector3 operator+(const Vector3&);
	Vector3 operator-(const Vector3&);

	void negate();
	void scale(double);
	double dot(const Vector3&, const Vector3&);
	Vector3 cross(const Vector3&, const Vector3&);
	double length();
	void normalize();
	void print(std::string);

	double getX() const;
	double getY() const;
	double getZ() const;
};

