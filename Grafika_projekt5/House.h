#pragma once

#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "HouseParams.h"
#include "Shader_m.h"
#include "VItem.h"


class House
{
public:
	House();
	House(HouseParams params);

	void Draw(glm::mat4& model, Shader& shader);

	~House();

	HouseParams params;

private:
	VItem window;
	VItem window2;
	VItem wall;
};