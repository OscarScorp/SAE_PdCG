#include "pch.h"
#include "Application.h"
#include <time.h>
//============================================== MidPointLine ===========================================
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

void Application::MidPointLine(const int&x, const int&y, const int&x1, const int &y1)
{ //Código de Alejandro Rangel.
	int xfinal = x1;
	int yfinal = y1;
	int xdelta;
	int ydelta;
	if (x1 > x)
	{
		xdelta = x;
		ydelta = y;
	}
	else
	{
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
	else
	{
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
		else{
			incNE = 2 * (a + b);
			while (xdelta <= xfinal){
				PutPixel(xdelta, ydelta);
				if (d < 0){
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

void Application::draw()
{
	MoveTo(0, 0);
	LineTo(300, 0);

	//DrawCircle(200);
}