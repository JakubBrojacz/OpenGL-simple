#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>

#include "Car.h"

class Display
{
public:
	Display(int* argc, char** argv);

	~Display();

private:
	Car car;
	GLuint car_vbo;

	void display();
};