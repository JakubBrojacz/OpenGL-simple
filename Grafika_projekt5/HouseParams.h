#pragma once

struct HouseParams
{
	float width; float height; float depth;
	int window_horizontal; int window_vertical;
	float window_width; float window_height;
	float door_width; float door_height;
	float door_offset;
	bool window_bot;
	bool smaller_window_over_door;
	int window_type;
	float x;
	float y=0;
	float z;
	float y_rot;

	float gap_v()
	{
		return (width - window_horizontal * window_width) / (window_horizontal + 1);
	}
	float gap_h()
	{
		return (height - window_vertical * window_height - door_height) / (window_vertical + 1);
	}
};