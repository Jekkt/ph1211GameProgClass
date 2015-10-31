#pragma once
class Vector
{
public:
	Vector();
	~Vector();

	Vector(float pX, float pY, float pZ);

	float length;
	float x;
	float y;
	float z;

	void normalize();
};

