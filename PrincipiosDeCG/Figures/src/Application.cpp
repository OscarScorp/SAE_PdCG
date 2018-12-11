#include "Application.h"
#include <time.h>
//============================================== Figures ===========================================
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
	canvas = 400;
	srand(time(NULL));
	randMinus = rand() % 2; if (randMinus != 1) randMinus = -1;
	v1_a.x = rand() % canvas * randMinus;
	v1_a.y = rand() % canvas * randMinus;
	v1_b.x = rand() % canvas * randMinus;
	v1_b.y = rand() % canvas * randMinus;
	v1_c.x = rand() % canvas * randMinus;
	v1_c.y = rand() % canvas * randMinus;

	randMinus = rand() % 2; if (randMinus != 1) randMinus = -1;
	v2_a.x = rand() % canvas * randMinus;
	v2_a.y = rand() % canvas * randMinus;
	v2_b.x = rand() % canvas * randMinus;
	v2_b.y = rand() % canvas * randMinus;
	v2_c.x = rand() % canvas * randMinus;
	v2_c.y = rand() % canvas * randMinus;

	randMinus = rand() % 2; if (randMinus != 1) randMinus = -1;
	v3_a.x = rand() % canvas * randMinus;
	v3_a.y = rand() % canvas * randMinus;
	v3_b.x = rand() % canvas * randMinus;
	v3_b.y = rand() % canvas * randMinus;
	v3_c.x = rand() % canvas * randMinus;
	v3_c.y = rand() % canvas * randMinus;

	randSides = rand() % 9 + 3;
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

void Application::Figure(const int &lados, const int &r, int _x, int _y){
	float inc = 360.0 / (float)lados; //lados instead of randSides;
		MoveTo(_x + r, _y); //Moveto (r,0);

		for (float ang = inc; ang < 360; ang += inc) {
			int x = r * cos(ang * Pi / 180.0),
				y = r * sin(ang * Pi / 180.0);
			LineTo(_x + x , _y + y);
		}
		LineTo(_x + r, _y);
}

void Application::Triangle(const Vector3D& v0, const Vector3D& v1, const Vector3D& v2) {
	MoveTo(v0.x, v0.y);
	LineTo(v1.x, v1.y);
	LineTo(v2.x, v2.y);
	LineTo(v0.x, v0.y);
}

void Application::GenerateTriangles() {
	Triangle(v1_a, v1_b, v1_c);
	Triangle(v2_a, v2_b, v2_c);
	Triangle(v3_a, v3_b, v3_c);
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
void Application::DrawCircle(int r) {
	SetColor(magenta);

	MoveTo(r, 0);
	for (int deg = 0; deg < 360; ++deg)
	{
		float x = r * cos(deg * Pi / 180.0f),
			y = r * sin(deg * Pi / 180.0f);
		LineTo(x, y);
	}
}

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

void Application::draw()
{
	SetColor(green);
	if (runOnce == false) {
		for (int i = 0; i < 5; ++i) {
			randMinus = rand() % 2; if (randMinus != 1) randMinus = -1;
			Figure(randSides, 100, (50 * i) * randMinus, (50 * i) * randMinus);
		}
		runOnce = true;
	}
	
	SetColor(yellow);
	GenerateTriangles();
}