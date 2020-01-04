#include "Lamp.h"

#include "LampPos.h"


Lamp::Lamp()
{
	Utils::Bind(metal, LampPos::Get());
}


void Lamp::Draw(glm::mat4& model, Shader& shader)
{
	auto tmp_model = glm::scale(model, glm::vec3{ 0.22,0.22,0.22 });
	tmp_model = glm::translate(tmp_model, glm::vec3{ 0.5,0,-1 });

	shader.setVec3("objectColor", 0.6f, 0.5f, 0.82f);
	shader.setMat4("model", tmp_model);

	Utils::Draw(metal);
}



Lamp::~Lamp()
{
}