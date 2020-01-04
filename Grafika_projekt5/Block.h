#pragma once
#include <array>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "HouseParams.h"
#include "Shader_m.h"
#include "House.h"


class Block
{
public:
	Block();

	void Draw(glm::mat4& model, Shader& shader);

	~Block();

private:
	

	std::array<House, 15> houses;
};