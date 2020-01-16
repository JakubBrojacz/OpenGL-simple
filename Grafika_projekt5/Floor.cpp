#include "Floor.h"

#include "DrawUtils.h"


Floor::Floor()
{
	std::vector<float> pos;
	DrawUtils::Triangle(pos,
		-50, 0, -50,
		-50, 0, 50,
		50, 0, 50);
	DrawUtils::Triangle(pos,
		-50, 0, -50,
		50, 0, 50,
		50, 0, -50);

	Utils::Bind(floor, pos);
}

void Floor::Draw(glm::mat4& model, Shader& shader)
{
	shader.setVec3("objectColor", 0.4f, 0.4f, 0.4f);
	shader.setMat4("model", model);

	Utils::Draw(floor);
}

Floor::~Floor()
{
}