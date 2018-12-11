#include "Application.h"
#include <time.h>
#include "Matrix3.h"
//============================================== Transform ===========================================
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

	//Transform
	des1.x = -400;
	des1.y = 400;
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

void Application::Figure(const int &lados, const int &r, int _x, int _y) {
	float inc = 360.0 / (float)lados; //lados instead of randSides;
	MoveTo(_x + r, _y); //Moveto (r,0);

	for (float ang = inc; ang < 360; ang += inc) {
		int x = r * cos(ang * Pi / 180.0),
			y = r * sin(ang * Pi / 180.0);
		LineTo(_x + x, _y + y);
	}
	LineTo(_x + r, _y);
}

void Application::Triangle(const Vector3D& v0, const Vector3D& v1, const Vector3D& v2) {
	MoveTo(v0.x, v0.y);
	LineTo(v1.x, v1.y);
	LineTo(v2.x, v2.y);
	LineTo(v0.x, v0.y);
}

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

void Application::update() {
	Matrix3 mA, mB, accum;

	mA = Matrix3::Translate(des1);
	mB = Matrix3::Identity();
	//Estos  son solo ejemplos de como debe ser.. Para la tarea tienes que usar escala, traslacion y rotacion
	accum = mA * mB; //Escala
	//accum = mA + mB; //Traslación
	verticesTransformados.clear();
	for (Vector3D v : vertex)
		verticesTransformados.push_back(accum * v);
}

void Application::draw() { //Transform
	SetColor(black);
	ClearScreen();
	SetColor(green);
	for (int i = 0; i < verticesTransformados.size(); i += 3) { //Sierpinski Gasket:
			Triangle(verticesTransformados[i], verticesTransformados[i + 1], verticesTransformados[i + 2]);
	}
}
