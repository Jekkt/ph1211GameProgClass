#pragma once

#ifndef vectorClass
#define vectorClass

class Vector3
{
public:
	Vector3();
	~Vector3();

	Vector3(float pX, float pY, float pZ);

	float length;
	float x;
	float y;
	float z;

	Vector3 makeVector(float x, float y, float z);
	Vector3 addVector(Vector3 vectorA, Vector3 vectorB);
	Vector3 normalize(Vector3 vector);
};

#endif