#pragma once
#include <array>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "VItem.h"


class DrawUtils
{
public:
	/*
					 x
		  ---------->
		 |	0	1
		 |
		 |		2
		 v
		y
	*/
	static void Triangle(
		std::vector<float>& points,
		float x0, float y0, float z0,
		float x1, float y1, float z1,
		float x2, float y2, float z2
	);

	/*
					 x
		  ---------->
		 |	0	1
		 |
		 |	3	2
		 v
		y
	*/
	static void Rect(
		std::vector<float>& points,
		float x0, float y0, float z0,
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3);


	static void Cylinder(
		std::vector<float>& points,
		float x, float y, float z,
		float r, float h,
		int triangle_count
	);

	static void PartCone(
		std::vector<float>& points,
		float x, float y, float z,
		float r0, float r1, float h,
		int triangle_count
	);
};

