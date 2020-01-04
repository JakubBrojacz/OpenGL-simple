#pragma once
#include <array>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "LampPos.h"
#include "Shader_m.h"
#include "Utils.h"
#include "VItem.h"


class Lamp
{
public:
	Lamp();

	void Draw(glm::mat4& model, Shader& shader);
	glm::vec3 LightPos{ 0.1, 1.166, -0.2 };

	~Lamp();

	VItem metal;
};