#pragma once
#include "Vector3D.h"
class Matrix3
{
private:
	float m[3][3];
public:
	Vector3D operator*(const Vector3D& RH) const; //no & porque el return es modificado. const = no altera el m.
	//Matrix3& operator=(const Matrix3& RH);
	Matrix3();
	~Matrix3();
};

