#include "LampPos.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "DrawUtils.h"


std::vector<float> LampPos::Get()
{
	float r0 = 0.1;
	float r1 = 0.4;
	float r2 = 0.15;
	float r3 = 0.225;
	float r4 = 0.6;
	float r5 = 0.35;
	float r6 = 0.15;
	float r7 = 0.005;

	float h0 = 5;
	float h1 = h0 + 0.1;
	float h2 = h1 + 0.5;
	float h3 = h2 + 0.15;
	float h4 = h3 + 0.05;
	float h5 = h4 + 0.1;

	std::vector<float> points{};

	DrawUtils::Cylinder(points,
		0, 0, 0,
		r0, h0,
		50);

	DrawUtils::PartCone(points,
		0, h0, 0,
		r0, r1, h1 - h0,
		50
	);

	DrawUtils::Cylinder(points,
		0, h1-0.05, 0,
		r2, h2-h1+0.2,
		50);

	DrawUtils::PartCone(points,
		0, h2, 0,
		r4, r5, h3 - h2,
		50
	);

	DrawUtils::PartCone(points,
		0, h4, 0,
		r5, r6, h5 - h4,
		50
	);

	return points;
}
