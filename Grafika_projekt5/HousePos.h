#pragma once

#include<vector>

#include "HouseParams.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class HousePos
{
public:
	static std::vector<float> GenerateWindows(
		HouseParams h
	);

	static std::vector<float> GenerateWindows2(
		HouseParams h
	);

	static std::vector<float> GenerateWalls(
		HouseParams h
	);
private:
	static std::vector<float> Generate(
		HouseParams h, std::vector<float> m(
			float, float, float,
			float, float,
			int));

	static std::vector<float> GenerateWindow(
		float x, float y, float z,
		float window_width, float window_height,
		int window_type
	);

	static std::vector<float> GenerateWindow2(
		float x, float y, float z,
		float window_width, float window_height,
		int window_type
	);

	static std::vector<float> GenerateWindowWall(
		float x, float y, float z,
		float window_width, float window_height,
		int window_type
	);

	static const float type0_z_offset;
	static const float type0_margin;
	static const float type0_z_offset_window;
	static const float type0_z_offset_wall;
};