#include "DrawUtils.h"

void DrawUtils::Triangle(std::vector<float>& points, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2)
{
	glm::vec3 a(x0, y0, z0);
	glm::vec3 b(x1, y1, z1);
	glm::vec3 c(x2, y2, z2);
	auto normal = glm::cross(b - a, c - a);

	float nx = normal.x;
	float ny = normal.y;
	float nz = normal.z;


	points.push_back(x0);
	points.push_back(y0);
	points.push_back(z0);
	points.push_back(nx);
	points.push_back(ny);
	points.push_back(nz);

	points.push_back(x1);
	points.push_back(y1);
	points.push_back(z1);
	points.push_back(nx);
	points.push_back(ny);
	points.push_back(nz);

	points.push_back(x2);
	points.push_back(y2);
	points.push_back(z2);
	points.push_back(nx);
	points.push_back(ny);
	points.push_back(nz);
}

void DrawUtils::Rect(std::vector<float>& points, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
	Triangle(points,
		x0, y0, z0,
		x1, y1, z1,
		x2, y2, z2
	);
	Triangle(points,
		x0, y0, z0,
		x2, y2, z2,
		x3, y3, z3
	);
}

void DrawUtils::Cylinder(std::vector<float>& points,
	float x, float y, float z,
	float r, float h,
	int triangle_count)
{
	float y0 = 0;
	float y1 = h;
	for (int i = 0; i < triangle_count; i += 2)
	{
		float alpha = (float)2 * glm::pi<float>() * ((float)i / (float)triangle_count);
		float x0 = sin(alpha);
		float z0 = cos(alpha);
		alpha = 2 * glm::pi<float>() * (float)((i + 2) % triangle_count) / (float)triangle_count;
		float x1 = sin(alpha);
		float z1 = cos(alpha);

		{
			std::vector<float> tmp =
			{
				x+x0 * r, y+y0, z+z0* r, x0, 0, z0,
				x+x0 * r, y+y1, z+z0* r, x0, 0, z0,
				x+x1 * r, y+y1, z+z1* r, x1, 0, z1,
				
				x+x0 * r, y+y0, z+z0* r, x0, 0, z0,
				x+x1 * r, y+y1, z+z1* r, x1, 0, z1,
				x+x1 * r, y+y0, z+z1* r, x1, 0, z1
			};
			points.insert(std::end(points), std::begin(tmp), std::end(tmp));
		}
	}
}

void DrawUtils::PartCone(std::vector<float>& points, 
	float x, float y, float z, 
	float r0, float r1, float h,
	int triangle_count)
{
	float y0 = 0;
	float y1 = h;
	for (int i = 0; i < triangle_count; i += 2)
	{
		float alpha = (float)2 * glm::pi<float>() * ((float)i / (float)triangle_count);
		float x0 = sin(alpha);
		float z0 = cos(alpha);
		alpha = 2 * glm::pi<float>() * (float)((i + 2) % triangle_count) / (float)triangle_count;
		float x1 = sin(alpha);
		float z1 = cos(alpha);

		{
			std::vector<float> tmp =
			{
				x + x0 * r0, y + y0, z + z0 * r0, x0, 0, z0,
				x + x0 * r1, y + y1, z + z0 * r1, x0, 0, z0,
				x + x1 * r1, y + y1, z + z1 * r1, x1, 0, z1,

				x + x0 * r0, y + y0, z + z0 * r0, x0, 0, z0,
				x + x1 * r1, y + y1, z + z1 * r1, x1, 0, z1,
				x + x1 * r0, y + y0, z + z1 * r0, x1, 0, z1
			};
			points.insert(std::end(points), std::begin(tmp), std::end(tmp));
		}
	}
}

