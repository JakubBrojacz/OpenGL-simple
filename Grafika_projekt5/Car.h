#pragma once
#include <array>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "WeelPos.h"
#include "CarPos.h"
#include "Shader_m.h"
#include "Utils.h"
#include "VItem.h"


class Car
{
public:
	Car();

	void Draw(glm::mat4& model, Shader& shader);

	~Car();

	VItem car;
	VItem weel;
};