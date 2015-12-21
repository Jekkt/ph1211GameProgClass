#include "Vector3.h"
#include <math.h>


Vector3::Vector3()
{
}

Vector3::Vector3(float pX, float pY, float pZ) {
	x = pX;
	y = pY;
	z = pZ;
}


Vector3::~Vector3(){

	}

Vector3 Vector3::makeVector(float x, float y, float z) {
	Vector3  newVector;

	newVector.x = x;
	newVector.y = y;
	newVector.z = z;

	return newVector;
}

Vector3 Vector3::addVector(Vector3 vectorA, Vector3 vectorB) {
	Vector3 newVector;
	newVector.x = vectorA.x + vectorB.x;
	newVector.y = vectorA.y + vectorB.y;
	newVector.z = vectorA.z + vectorB.z;

	return newVector;
}

Vector3 Vector3::normalize(Vector3 vector) {
		
	float length = sqrtf((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
	
	Vector3 unitVector;
	unitVector.x = vector.x / length;
	unitVector.y = vector.y / length;
	unitVector.z = vector.z / length;

	return unitVector;
	}
