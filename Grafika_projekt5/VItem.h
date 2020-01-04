#pragma once

#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>


struct VItem
{
	std::vector<float> points;
	GLuint vao=0;
	GLuint vbo=0;
};