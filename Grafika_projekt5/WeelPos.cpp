#include "WeelPos.h"
#include <glm\ext\scalar_constants.hpp>

std::vector<float> WeelPos::Get()
{
	float r = 1;
	float r1 = 0.8f;
	float rdif = r - r1;

	float z0 = 0;
	float z1 = 1;

	std::vector<float> points = {};
	int id = 0;
	for (int i = 0; i < WeelPos::triangle_n_perim; i+=2)
	{
		float alpha = (float)2 * glm::pi<float>() * ((float)i/(float)triangle_n_perim);
		float x0 = sin(alpha);
		float y0 = cos(alpha);
		alpha = 2 * glm::pi<float>() * (float)((i+2) % triangle_n_perim) / (float)triangle_n_perim;
		float x1 = sin(alpha);
		float y1 = cos(alpha);

		{
			std::array<float, 2 * 3 * 6> tmp =
			{
				x0 * r, y0 * r, z0, x0, y0, 0,
				x0 * r, y0 * r, z1, x0, y0, 0,
				x1 * r, y1 * r, z1, x1, y1, 0,

				x0 * r, y0 * r, z0, x0, y0, 0,
				x1 * r, y1 * r, z1, x1, y1, 0,
				x1 * r, y1 * r, z0, x1, y1, 0,
			};
			points.insert(std::end(points), std::begin(tmp), std::end(tmp));
		}

		{
			std::array<float, 2 * 3 * 6> tmp =
			{
				0, 0, z0-rdif, 0, 0, -1,
				x0 * r1, y0 * r1, z0 - rdif, 0, 0, -1,
				x1 * r1, y1 * r1, z0 - rdif, 0, 0, -1,

				0, 0, z1 + rdif, 0, 0, 1,
				x0* r1, y0* r1, z1 + rdif, 0, 0, 1,
				x1* r1, y1* r1, z1 + rdif, 0, 0, 1,
			};
			points.insert(std::end(points), std::begin(tmp), std::end(tmp));
		}

		{
			for (int j = 0; j < circle_n_end; j++)
			{
				float t_alpha = (glm::pi<float>() / 2) * ((float)j / circle_n_end);
				float sin0 = sin(t_alpha);
				float t_dif0 = rdif * sin0;
				float cos0 = cos(t_alpha);
				float t_r0 = r1+rdif * cos0;
				t_alpha = (glm::pi<float>() / 2) * ((float)(j+1) / circle_n_end);
				float sin1 = sin(t_alpha);
				float t_dif1 = rdif * sin1;
				float cos1 = cos(t_alpha);
				float t_r1 = r1 + rdif * cos1;

				//x0 * tr0, y0*tr0; x1*tr0, y1*tr0  <- tz0
				//x0 * tr1, y0*tr1; x1*tr1, y1*tr1  <- tz1
				std::array<float, 4 * 3 * 6> tmp =
				{
					x0* t_r0, y0*t_r0, z0 - t_dif0, x0* cos0, y0* cos0, -sin0,
					x1* t_r0, y1* t_r0, z0 - t_dif0, x1* cos0, y1* cos0, -sin0,
					x0* t_r1, y0* t_r1, z0 - t_dif1, x0* cos1, y0* cos1, -sin1,

					x1* t_r0, y1* t_r0, z0 - t_dif0, x1* cos0, y1* cos0, -sin0,
					x1* t_r1, y1* t_r1, z0 - t_dif1, x1* cos1, y1* cos1, -sin1,
					x0* t_r1, y0* t_r1, z0 - t_dif1, x0* cos1, y0* cos1, -sin1,

					x0* t_r0, y0* t_r0, z1 + t_dif0, x0* cos0, y0* cos0, sin0,
					x1* t_r0, y1* t_r0, z1 + t_dif0, x1* cos0, y1* cos0, sin0,
					x0* t_r1, y0* t_r1, z1 + t_dif1, x0* cos1, y0* cos1, sin1,
										 
					x1* t_r0, y1* t_r0, z1 + t_dif0, x1* cos0, y1* cos0, sin0,
					x1* t_r1, y1* t_r1, z1 + t_dif1, x1* cos1, y1* cos1, sin1,
					x0* t_r1, y0* t_r1, z1 + t_dif1, x0* cos1, y0* cos1, sin1,
				};
				points.insert(std::end(points), std::begin(tmp), std::end(tmp));
			}
		}
	}
	return points;

}
