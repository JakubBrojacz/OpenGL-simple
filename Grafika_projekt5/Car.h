#pragma once
#include <array>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader_m.h"


class Car
{
public:
	Car();

	glm::vec3 PositionVec3(float current_frame);

	float Rotation(float current_frame);

	glm::mat4 Model(float current_frame);

	~Car();
};