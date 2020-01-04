#pragma once
#include <array>
#include <vector>

class WeelPos
{
public:
	static const int triangle_n_perim = 50; // n%2==0
	static const int circle_n_end = 20;
	static std::vector<float> Get();
};