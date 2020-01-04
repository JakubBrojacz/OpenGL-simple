#include "HousePos.h"

#include <iostream>

#include "DrawUtils.h"


const float HousePos::type0_z_offset = 0.02;
const float HousePos::type0_z_offset_window = 0.008;
const float HousePos::type0_z_offset_wall = HousePos::type0_z_offset - HousePos::type0_z_offset_window;
const float HousePos::type0_margin = 0.015;


std::vector<float> HousePos::Generate(
	HouseParams h, std::vector<float> m(
		const float, float, float,
		const float, float,
		const int))
{
	std::vector<float> points{};

	const float gap_v = h.gap_v();
	const float gap_h = h.gap_h();

	for (int i = 0; i < h.window_horizontal; i++)
	{
		for (int j = 0; j < h.window_vertical; j++)
		{
			auto tmp = m
			(
				i * (h.window_width + gap_v) + gap_v,
				h.door_height + j * (h.window_height + gap_h) + gap_h,
				0,
				h.window_width,
				h.window_height,
				h.window_type
			);
			points.insert(std::end(points), std::begin(tmp), std::end(tmp));
		}
	}

	return points;
}

std::vector<float> HousePos::GenerateWindows(HouseParams h)
{
	return Generate(h, GenerateWindow);
}

std::vector<float> HousePos::GenerateWindows2(HouseParams h)
{
	return Generate(h, GenerateWindow2);
}

std::vector<float> HousePos::GenerateWindow(
	float x, float y, float z,
	float window_width, float window_height,
	int window_type)
{
	std::vector<float> points{};
	z = z - type0_z_offset;

	DrawUtils::Rect(points,
		x + type0_margin, y + type0_margin, z,
		x + (window_width - type0_margin) / 2, y + type0_margin, z,
		x + (window_width - type0_margin) / 2, y + window_height - type0_margin, z,
		x+ type0_margin, y + window_height - type0_margin, z
	);
	DrawUtils::Rect(points,
		x + (window_width + type0_margin) / 2, y + type0_margin, z,
		x + window_width - type0_margin, y + type0_margin, z,
		x + window_width - type0_margin, y + window_height - type0_margin, z,
		x+ (window_width + type0_margin) / 2, y + window_height - type0_margin, z
	);
	return points;
}

std::vector<float> HousePos::GenerateWindow2(
	float x, float y, float z, 
	float window_width, float window_height, int window_type)
{
	//return GenerateWindow(x, y, z, window_width, window_height, window_type);
	std::vector<float> points{};
	z = z - type0_z_offset;

	//side inside
	DrawUtils::Rect(points,
		x, y, z,
		x + type0_margin, y, z,
		x + type0_margin, y + window_height,z,
		x, y + window_height, z
	);
	DrawUtils::Rect(points,
		x + window_width - type0_margin, y, z,
		x + window_width, y, z,
		x + window_width, y + window_height, z,
		x + window_width - type0_margin, y + window_height, z
	);

	//mid inside
	DrawUtils::Rect(points,
		x + (window_width - type0_margin)/2, y+ type0_margin, z,
		x + (window_width + type0_margin) / 2, y+ type0_margin, z,
		x + (window_width + type0_margin) / 2, y + window_height- type0_margin, z,
		x + (window_width - type0_margin) / 2, y + window_height- type0_margin, z
	);

	//bot top inside
	DrawUtils::Rect(points,
		x +  type0_margin, y, z,
		x + window_width - type0_margin, y, z,
		x + window_width - type0_margin, y +  type0_margin, z,
		x + type0_margin, y + type0_margin, z
	);
	DrawUtils::Rect(points,
		x + type0_margin, y+ window_height - type0_margin, z,
		x + window_width - type0_margin, y+ window_height - type0_margin, z,
		x + window_width - type0_margin, y + window_height, z,
		x + type0_margin, y + window_height, z
	);

	//sides left right bot top
	DrawUtils::Rect(points,
		x, y, z+ type0_z_offset_window,
		x, y, z,
		x, y + window_height, z,
		x, y + window_height, z+ type0_z_offset_window
	);
	DrawUtils::Rect(points,
		x + window_width, y + window_height, z + type0_z_offset_window,
		x + window_width, y + window_height, z,
		x + window_width, y, z,
		x + window_width, y, z + type0_z_offset_window
	);
	DrawUtils::Rect(points,
		x, y, z,
		x, y, z + type0_z_offset_window,
		x + window_width, y, z + type0_z_offset_window,
		x + window_width, y, z
	);
	DrawUtils::Rect(points,
		x, y + window_height, z + type0_z_offset_window,
		x, y + window_height, z,
		x + window_width, y + window_height, z,
		x + window_width, y + window_height, z + type0_z_offset_window
	);

	return points;
}

std::vector<float> HousePos::GenerateWindowWall(
	float x, float y, float z,
	float window_width, float window_height, int window_type)
{
	//return GenerateWindow(x, y, z, window_width, window_height, window_type);
	std::vector<float> points{};
	z = z - type0_z_offset_wall;

	//sides left right bot top
	DrawUtils::Rect(points,
		x, y, z + type0_z_offset_wall,
		x, y, z,
		x, y + window_height, z,
		x, y + window_height, z + type0_z_offset_wall
	);
	DrawUtils::Rect(points,
		x + window_width, y + window_height, z + type0_z_offset_wall,
		x + window_width, y + window_height, z,
		x + window_width, y, z,
		x + window_width, y, z + type0_z_offset_wall
	);
	DrawUtils::Rect(points,
		x, y, z,
		x, y, z + type0_z_offset_wall,
		x + window_width, y, z + type0_z_offset_wall,
		x + window_width, y, z
	);
	DrawUtils::Rect(points,
		x, y + window_height, z + type0_z_offset_wall,
		x, y + window_height, z,
		x + window_width, y + window_height, z,
		x + window_width, y + window_height, z + type0_z_offset_wall
	);

	return points;
}

std::vector<float> HousePos::GenerateWalls(HouseParams h)
{
	std::vector<float> points{};

	const float gap_v = h.gap_v();
	const float gap_h = h.gap_h();

	//veritical triangles on front
	for (int i = 0; i < h.window_horizontal + 1; i++)
	{

		std::vector<float> tmp
		{
			i * (h.window_width + gap_v), h.door_height, 0, 0, 0, 1,
			i * (h.window_width + gap_v), h.height, 0, 0, 0, 1,
			i * (h.window_width + gap_v) + gap_v, h.height, 0, 0, 0, 1,

			i * (h.window_width + gap_v), h.door_height, 0, 0, 0, 1,
			i * (h.window_width + gap_v) + gap_v, h.height, 0, 0, 0, 1,
			i * (h.window_width + gap_v) + gap_v, h.door_height, 0, 0, 0, 1,
		};
		points.insert(std::end(points), std::begin(tmp), std::end(tmp));
	}

	//hoorizontal triangles on front
	for (int i = 0; i < h.window_vertical + 1; i++)
	{

		std::vector<float> tmp
		{
			0, h.door_height + i * (h.window_height + gap_h), 0, 0, 0, 1,
			h.width, h.door_height + i * (h.window_height + gap_h), 0, 0, 0, 1,
			h.width, h.door_height + i * (h.window_height + gap_h) + gap_h, 0, 0, 0, 1,

			0, h.door_height + i * (h.window_height + gap_h), 0, 0, 0, 1,
			h.width, h.door_height + i * (h.window_height + gap_h) + gap_h, 0, 0, 0, 1,
			0, h.door_height + i * (h.window_height + gap_h) + gap_h, 0, 0, 0, 1,
		};
		points.insert(std::end(points), std::begin(tmp), std::end(tmp));
	}

	//front around door
	{
		std::vector<float> tmp
		{
			0, 0, 0, 0, 0, 1,
			0, h.door_height, 0, 0, 0, 1,
			(h.width - h.door_width) / 2 + h.door_offset, h.door_height, 0, 0, 0, 1,

			0, 0, 0, 0, 0, 1,
			(h.width - h.door_width) / 2 + h.door_offset, h.door_height, 0, 0, 0, 1,
			(h.width - h.door_width) / 2 + h.door_offset, 0, 0, 0, 0, 1,


			(h.width + h.door_width) / 2 + h.door_offset, 0, 0, 0, 0, 1,
			(h.width + h.door_width) / 2 + h.door_offset, h.door_height, 0, 0, 0, 1,
			h.width, h.door_height, 0, 0, 0, 1,

			(h.width + h.door_width) / 2 + h.door_offset, 0, 0, 0, 0, 1,
			h.width, h.door_height, 0, 0, 0, 1,
			h.width, 0, 0, 0, 0, 1,
		};
		points.insert(std::end(points), std::begin(tmp), std::end(tmp));
	}

	//non-front
	{
		std::vector<float> tmp
		{
			//left
			0, 0, 0, -1, 0, 0,
			0, h.height, 0, -1, 0, 0,
			0, h.height, -h.depth, -1, 0, 0,

			0, 0, 0, -1, 0, 0,
			0, h.height, -h.depth, -1, 0, 0,
			0, 0, -h.depth, -1, 0, 0,

			//right
			h.width, 0, 0, 1, 0, 0,
			h.width, h.height, 0, 1, 0, 0,
			h.width, h.height, -h.depth, 1, 0, 0,

			h.width, 0, 0, 1, 0, 0,
			h.width, h.height, -h.depth, 1, 0, 0,
			h.width, 0, -h.depth, 1, 0, 0,

			//back
			0, 0, -h.depth, 0, 0, -1,
			h.width, 0, -h.depth, 0, 0, -1,
			h.width, h.height, -h.depth, 0, 0, -1,

			0, 0, -h.depth, 0, 0, -1,
			h.width, h.height, -h.depth, 0, 0, -1,
			0, h.height, -h.depth, 0, 0, -1,

			//bot
			0, 0, 0, 0, -1, 0,
			h.width, 0, 0, 0, -1, 0,
			h.width, 0, -h.depth, 0, -1, 0,

			0, 0, 0, 0, -1, 0,
			h.width, 0, -h.depth, 0, -1, 0,
			0, 0, -h.depth, 0, -1, 0,

			//top
			0, h.height, 0, 0, 1, 0,
			h.width, h.height, 0, 0, 1, 0,
			h.width, h.height, -h.depth, 0, 1, 0,

			0, h.height, 0, 0, 1, 0,
			h.width, h.height, -h.depth, 0, 1, 0,
			0, h.height, -h.depth, 0, 1, 0,
		};
		points.insert(std::end(points), std::begin(tmp), std::end(tmp));
	}

	{
		std::vector<float> tmp = Generate(h, GenerateWindowWall);
		points.insert(std::end(points), std::begin(tmp), std::end(tmp));
	}

	return points;
}
