#include "Application.h"
#include <time.h>
//============================================== Sierpinski ===========================================
Application::Application() : BaseApplication(),
//384 if 768, 512 if 1024.
	centerX(WIDTH / 2),
	centerY(HEIGHT / 2),
	currentPosX(centerX),
	currentPosY(centerY),
	currentColor(255, 255, 255, 0), //White
	white(255, 255, 255, 0),
	black(0, 0, 0, 0),
	red(255, 0, 0, 0),
	green(0, 255, 0, 0),
	blue(0, 0, 255, 0),
	magenta(255, 0, 255, 0),
	yellow(255, 255, 0, 0)
{
}

void Application::setup() {
	v1_a.x = 300;
	v1_a.y = -300;
	v1_b.x = -300;
	v1_b.y = -300;
	v1_c.x = 0;
	v1_c.y = 200;
	SierpinskiGasket(v1_a, v1_b, v1_c, 3);
}

Application::~Application()
{
}

void Application::SetColor(Color c){
	currentColor = Color(c);
}
void Application::SetColor(const char &r, const char &g, const char &b, const char &alpha){
	currentColor = Color(r, g, b, alpha);
}

void Application::LineTo(const int &x1, const int &y1) {
	MidPointLine(currentPosX, currentPosY, centerX + x1, centerY - y1); //Call to MidPointLine <---------------------
	MoveTo(x1, y1);
}

void Application::MoveTo(const int &x, const int &y) {
	currentPosX = x + centerX;
	currentPosY = -y + centerY;
}

void Application::PutPixel(const int &x, const int &y) {
	BaseApplication::putPixel(x, y, currentColor);
}

void Application::ClearScreen() { //Rellenar toda la pantalla.
	for (int i = 0; i < WIDTH; ++i)
		for (int j = 0; j < HEIGHT; ++j)
			BaseApplication::putPixel(i, j, currentColor);
}

void Application::MidPointLine(const int&x, const int&y, const int&x1, const int &y1) {
	//Código de Alejandro Rangel.
	int xfinal = x1;
	int yfinal = y1;
	int xdelta;
	int ydelta;
	if (x1 > x) {
		xdelta = x;
		ydelta = y;
	}
	else {
		xdelta = x1;
		ydelta = y1;
		xfinal = x;
		yfinal = y;
	}
	int a = yfinal - ydelta;
	int b = xfinal - xdelta;
	int d = 2 * a - b;
	int incE = 2 * a;
	int incNE = 2 * (a - b);
	if (abs(a) > abs(b)){
		d = 2 * b - a;
		incE = 2 * b;
		incNE = 2 * (b - a);
		if (yfinal > ydelta){
			while (ydelta < yfinal){
				PutPixel(xdelta, ydelta);
				if (d > 0){
					++xdelta;
					d = d + incNE;
				}
				else
					d = d + incE;
				++ydelta;
			}
		}
		else{
			incNE = 2 * (a + b);
			while (ydelta >= yfinal){
				PutPixel(xdelta, ydelta);
				if (d > 0)
				{
					++xdelta;
					d += incNE;
				}
				else
					d += incE;
				--ydelta;
			}
		}
	}
	else {
		if (yfinal > ydelta){
			while (xdelta <= xfinal){
				PutPixel(xdelta, ydelta);
				if (d > 0){
					++ydelta;
					d = d + incNE;
				}
				else
					d = d + incE;
				++xdelta;
			}
		}
		else {
			incNE = 2 * (a + b);
			while (xdelta <= xfinal) {
				PutPixel(xdelta, ydelta);
				if (d < 0) {
					--ydelta;
					d += incNE;
				}
				else
					d += incE;
				++xdelta;
			}
		}
	}
}

void Application::Triangle(const Vector3D& v0, const Vector3D& v1, const Vector3D& v2) {
	MoveTo(v0.x, v0.y);
	LineTo(v1.x, v1.y);
	LineTo(v2.x, v2.y);
	LineTo(v0.x, v0.y);
}

//Convención de la clase Matriz: renglón y columna (x,y).
/*
Constructor de Matrix3 que inicializara en 0;
Matrix3 Matrix3::operator * (const Matrix3 & RH)
{
	
}

//Matrix a = Matrix3::Identity();
Matrix3 Matrix3::Identity()
{
	Matrix3 r;
	r.m[0][0] = r.m[1][1] = r.m[2][2] = 1;
	r.m[0][1] = r.m[0][2] =
	r.m[1][0] = r.m[1][2] =
	r.m[2][0] = r.m[2][1] = 0;
	return r;
}

Matrix3 Matrix3::operator = (const Matrix3 & RH)
{
	for (int row = 0; row < 3; ++row)
	for (int col = 0; col < 3; ++col)
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				result.m[row][col] += m[i][j] * RH[j][i];
}

Matrix3 Matrix3::Translate(const vec3 & v)
{
	Matrix r = Matrix 3::Identity();
	r.m[0][2] = v.x;
	r.m[1][2] = v.y;
	return r;
}

Rotación: [cos(ang*pi / 180), cos(ang*pi / 180), dx]
		  [cos(ang*pi / 180), cos(ang*pi / 180), dy]
		  [0,0,1]
		La única manera de rotar un objeto en 2 dimensiones es sobre Z.
*/

/*
Void Application::update()
{
	//Calulcar trans
	//pon aquí tus transformaciónes y guardar todo en Matrix3 accum;
	verticesTransformados.clear();
	for(vec3 v: vertices)
		verticesTransformados.push_back(accum * v);
}
*/

/*
Nov 20
vec4
{
public:
vec4(); //(0,0,0,1)
vec4(const float &x, const float &y, const float z), //x, y, z, 1)
float v[4];
float dot (const vec4 & rh); //producto punto
vec4 cross (const vec4 & rh); //producto cruz
void normalize (); // normaliza el vector (longitud = 1)
void homogenize(); // lleva el vector que tenga el w a 1
}

class Matrix4
{
public:
static Matrix4 RortateX(const float & ang);
static Matrix4 RortateX(const float & ang);
static Matrix4 RortateX(const float & ang);
static Matrix4 Translate(vec4 & v);
static Matrix4 Scale(vec4 & v);
Matrix4 operator * (const Matrix4 & RH);
vec4 operator * (const vec4 & RH);

private:
float m[4][4];	

}

*/

void Application::SierpinskiGasket(Vector3D a, Vector3D b, Vector3D c, int subDiv) {
	if (subDiv <= 0) {
		vertex.push_back(a);
		vertex.push_back(b);
		vertex.push_back(c);
	}
	else {
		Vector3D ab = PuntoMedioVec(a, b);
		Vector3D bc = PuntoMedioVec(b, c);
		Vector3D ca = PuntoMedioVec(c, a);
		SierpinskiGasket(a, ab, ca, subDiv - 1);
		SierpinskiGasket(ab, b, bc, subDiv - 1);
		SierpinskiGasket(ca, bc, c, subDiv - 1);
	}
}

Vector3D Application::PuntoMedioVec(Vector3D a, Vector3D b) {
	Vector3D res;
	res.x = (a.x + b.x) / 2;
	res.y = (a.y + b.y) / 2;
	return res;
}

void Application::draw() {
	SetColor(yellow);
	for (int i = 0; i < vertex.size(); i += 3)
		Triangle(vertex[i], vertex[i+1], vertex[i+2]);
}
