#include "House.h"
#include "HousePos.h"

#include "Utils.h"

House::~House()
{
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	//glDeleteVertexArrays(1, &window_vao);
	//glDeleteBuffers(1, &window_vbo);

	//glDeleteVertexArrays(1, &wall_vao);
	//glDeleteBuffers(1, &wall_vbo);
}

House::House()
{
}

House::House(HouseParams params) : params(params)
{
	Utils::Bind(window, HousePos::GenerateWindows(params));
	Utils::Bind(window2, HousePos::GenerateWindows2(params));
	Utils::Bind(wall, HousePos::GenerateWalls(params));
}

void House::Draw(glm::mat4& model, Shader& shader)
{
	shader.setMat4("model", model);

	shader.setVec3("objectColor", 0, 0, 1);
	Utils::Draw(window);

	shader.setVec3("objectColor", 0, 1, 1);
	Utils::Draw(wall);

	shader.setVec3("objectColor", 0.5, 0.5, 0.5);
	Utils::Draw(window2);
}
