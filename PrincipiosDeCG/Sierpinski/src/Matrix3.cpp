#include "Matrix3.h"

/*
Vector3D Matrix3::operator*(const Vector3D & RH)
{
	Vector3D result;

	result.x = m[0][0] * RH.x +
		m[0][1] * RH.y +
		m[0][2] * RH.w;

	result.x = m[0][0] * RH.x +
		m[1][1] * RH.y +
		m[1][2] * RH.w;

	result.x = m[0][0] * RH.x +
		m[2][1] * RH.y +
		m[2][2] * RH.w;

	return result;
}
*/

/*
Matrix3 & Matrix3::operator=(const Matrix3 & RH)
{
	//Duda del profesor: Debe llevar &? Matrix3 & Matrix3::operator... si no funciona.
	if (this != &RH) //this es dirección de memoria, al igual que &. 
		for (int row = 0; row < 3; ++row)
			for (int col = 0; col < 3; ++col)
				m[row][col] = RH.m[row][col];
	return *this; //* = valor, no dirección de memoria.
}
*/

Matrix3::Matrix3()
{
}

Matrix3::~Matrix3()
{
}

//Main de Matrix3:
//int main()
//{
///*
//	Matrix3 m1, m2;
//	Vector3D v;
//	v.x = 2; v.y = 3; v.w = 1;
//
//	m1.m[0][0] = m1.m[1][1] = m1.m[2][2] = 1;
//	m2.m[0][0] = 1234567;
//	m2 = m1;
//
//	Vec3 r = m1 * v; //test
//	*/
//	return 0;
//}