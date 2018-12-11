#pragma once
#include "BaseApplication.h"
#include "Vector3D.h"

class Application : public BaseApplication
{
private:
	int currentPosX{ 0 }, currentPosY{ 0 },
		centerX{ 0 }, centerY{ 0 };
	float Pi = 3.14159265359;
	Color currentColor, white, black, red, green, blue, magenta, yellow;
	void MidPointLine(const int& X1, const int&  Y1, const int&  X2, const int&  Y2); //const int &x0, const int &y0, const int &x1, const int &y1
	void Figure(const int &lados, const int &r, int _x, int _y);
	void Triangle(const Vector3D& v0, const Vector3D& v1, const Vector3D& v2);
	void DrawCircle(int r);
	void GenerateTriangles();
	bool runOnce = false;

public:
	Application();
	~Application();
	void MoveTo(const int &x, const int &y);
	void LineTo(const int &x1, const int &y1);
	void PutPixel(const int &x, const int &y);
	void SetColor(Color c);
	void SetColor(const char &r, const char &g, const char &b, const char &alpha);
	void ClearScreen();
	void draw() override; //Va a causar error.
	int once = 0;

	//Shapes
	int randSides1{ 4 }, randSides2{ 4 }, randSides3{ 4 }, randSides4{ 4 }, randSides5{ 4 };
	void drawSquare(const int &size);
	void drawTriangle(const int &base, const int &height);

	//Triangles
	int randMinus{ 1 }, randNum{ 0 }, canvas{ 0 };
	Vector3D v1_a, v1_b, v1_c, v2_a, v2_b, v2_c, v3_a, v3_b, v3_c;
};

