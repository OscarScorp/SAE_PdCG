#include "Matrix3.h"

Matrix3 Matrix3::Translate(const Vector3D & v) { //Preparando a la matriz para rotar a los objetos.
	Matrix3 r = Matrix3::Identity();
	r.m[0][2] = v.x;
	r.m[1][2] = v.y; //De un vector, regresa una matriz.
	return r; //Regresa una matriz lista para traslación.
}

Matrix3 Matrix3::Identity() {
	Matrix3 r;
	r.m[0][0] = r.m[1][1] = r.m[2][2] = 1;
	r.m[0][1] = r.m[0][2] =
		r.m[1][0] = r.m[1][2] =
		r.m[2][0] = r.m[2][1] = 0;
	return r;
}

Matrix3 Matrix3::Rotation(const Vector3D & v) {  ///bueno aqui obvio debes descomentar y corregir si es que es necesario
	
	//No comprendo cómo arreglar este código comentado, o cómo implementarlo a lo que ya tengo.
	/*[cos(ang*pi / 180), cos(ang*pi / 180), dx]
	[cos(ang*pi / 180), cos(ang*pi / 180), dy]
	[0,0,1]*/
	//La única manera de rotar un objeto en 2 dimensiones es sobre Z.
	return Matrix3();
}

Vector3D Matrix3::operator*(const Vector3D & RH) const {
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

//Convención de la clase Matriz: renglón y columna (x,y).
//Constructor de Matrix3 que inicializara en 0;
Matrix3 & Matrix3::operator * (const Matrix3 & RH) {
	Matrix3 result;

	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j)
					result.m[row][col] += m[i][j] * RH.m[j][i];
	return result;
}

Matrix3 & Matrix3::operator = (const Matrix3 & RH) {
	if (this != &RH) //this es dirección de memoria, al igual que &. 
		for (int row = 0; row < 3; ++row)
			for (int col = 0; col < 3; ++col)
				m[row][col] = RH.m[row][col];
	return *this; //* = valor, no dirección de memoria.
}

Matrix3::Matrix3()
{
}

Matrix3::~Matrix3()
{
}