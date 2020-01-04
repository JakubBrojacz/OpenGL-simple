#include "CarPos.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

std::vector<float> CarPos::Get()
{
	float x0 = 0.0;
	float x1 = 0.0; //first up
	float x2 = 0.2; //weel
	float x3 = 0.2; //second up
	float x4 = 0.3; //roof
	float x5 = 0.5; //weel
	float x6 = 0.6; //down
	float x7 = 0.7; //down end
	float x8 = 0.8; //end

	float y0 = 0.0; //wheel down
	float y1 = 0.1; //wheel mid
	float y2 = 0.2; //wheel up

	float y3 = 0.1; //car down
	float y4 = 0.2; //hood
	float y5 = 0.25f; //trunk
	float y6 = 0.4; //roof

	float z0 = 0.0;
	float z1 = 0.4;

	std::vector<float> points_pos
	{
		//left
		x0, y3, z0,
		x0, y4, z0,
		x8, y3, z0,
		x8, y4, z0,
		x8, y3, z0,
		x0, y4, z0,

		x3, y5, z0,
		x3, y4, z0,
		x1, y4, z0,

		x8, y4, z0,
		x3, y4, z0,
		x3, y5, z0,
		x3, y5, z0,
		x8, y5, z0,
		x8, y4, z0,

		x3, y5, z0,
		x4, y6, z0,
		x4, y5, z0,

		x6, y5, z0,
		x4, y5, z0,
		x4, y6, z0,
		x6, y6, z0,
		x6, y5, z0,
		x4, y6, z0,

		x7, y5, z0,
		x6, y5, z0,
		x6, y6, z0,

		//right
		x8, y3, z1,
		x0, y4, z1,
		x0, y3, z1,
		x0, y4, z1,
		x8, y3, z1,
		x8, y4, z1,

		x1, y4, z1,
		x3, y4, z1,
		x3, y5, z1,

		x3, y5, z1,
		x3, y4, z1,
		x8, y4, z1,
		x8, y4, z1,
		x8, y5, z1,
		x3, y5, z1,

		x4, y5, z1,
		x4, y6, z1,
		x3, y5, z1,

		x4, y6, z1,
		x4, y5, z1,
		x6, y5, z1,
		x4, y6, z1,
		x6, y5, z1,
		x6, y6, z1,

		x6, y6, z1,
		x6, y5, z1,
		x7, y5, z1,

		//top & bot
		x0, y3, z0,
		x0, y3, z1,
		x0, y4, z1,
		x0, y4, z1,
		x0, y4, z0,
		x0, y3, z0,

		x0, y4, z0,
		x0, y4, z1,
		x1, y4, z1,
		x1, y4, z1,
		x1, y4, z0,
		x0, y4, z0,

		x1, y4, z0,
		x1, y4, z1,
		x3, y5, z1,
		x3, y5, z1,
		x3, y5, z0,
		x1, y4, z0,

		x3, y5, z0,
		x3, y5, z1,
		x4, y6, z1,
		x4, y6, z1,
		x4, y6, z0,
		x3, y5, z0,

		x4, y6, z0,
		x4, y6, z1,
		x6, y6, z1,
		x6, y6, z1,
		x6, y6, z0,
		x4, y6, z0,

		x6, y6, z0,
		x6, y6, z1,
		x7, y5, z1,
		x7, y5, z1,
		x7, y5, z0,
		x6, y6, z0,

		x7, y5, z0,
		x7, y5, z1,
		x8, y5, z1,
		x8, y5, z1,
		x8, y5, z0,
		x7, y5, z0,

		x8, y5, z0,
		x8, y5, z1,
		x8, y3, z1,
		x8, y3, z1,
		x8, y3, z0,
		x8, y5, z0,

		x0, y3, z1,
		x8, y3, z1,
		x8, y3, z0,
		x8, y3, z0,
		x0, y3, z0,
		x0, y3, z1,
	};

	std::vector<float> points={};

	for (int i = 0; i < points_pos.size(); i += 3)
	{
		points.push_back( points_pos[i]);
		points.push_back(points_pos[i + 1]);
		points.push_back(points_pos[i + 2]);
		points.push_back(0);
		points.push_back(0);
		points.push_back(0);
	}
	for (int i = 0; i < points_pos.size(); i += 9)
	{

		glm::vec3 a(points_pos[i], points_pos[i + 1], points_pos[i + 2]);
		glm::vec3 b(points_pos[i + 3], points_pos[i + 4], points_pos[i + 5]);
		glm::vec3 c(points_pos[i + 6], points_pos[i + 7], points_pos[i + 8]);
		auto normal = glm::cross(b - a, c - a);
		for (int j = 0; j < 18; j += 6)
		{
			points[i * 2 + j + 3] = normal.x;
			points[i * 2 + j + 4] = normal.y;
			points[i * 2 + j + 5] = normal.z;
		}

	}
	return points;
}
