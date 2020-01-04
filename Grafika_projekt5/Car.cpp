#include "Car.h"
#include "CarPos.h"
#include "WeelPos.h"


Car::Car()
{
	Utils::Bind(car, CarPos::Get());
	Utils::Bind(weel, WeelPos::Get());
}

void Car::Draw(glm::mat4& model, Shader& shader)
{
	shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	shader.setMat4("model", model);

	Utils::Draw(car);

	auto weel_model = glm::scale(model, glm::vec3{ 0.1, 0.1, 0.1 });
	weel_model = glm::translate(weel_model, glm::vec3{ 1.5, 1, 0});
	shader.setVec3("objectColor", 0.1f, 0.1f, 0.1f);
	shader.setMat4("model", weel_model);
	
	Utils::Draw(weel);


	weel_model = glm::translate(weel_model, glm::vec3{ 0, 0, 3 });
	shader.setMat4("model", weel_model);
	glDrawArrays(GL_TRIANGLES, 0, weel.points.size() * sizeof(float));


	weel_model = glm::translate(weel_model, glm::vec3{ 5, 0, 0 });
	shader.setMat4("model", weel_model);
	glDrawArrays(GL_TRIANGLES, 0, weel.points.size() * sizeof(float));


	weel_model = glm::translate(weel_model, glm::vec3{ 0, 0, -3 });
	shader.setMat4("model", weel_model);
	glDrawArrays(GL_TRIANGLES, 0, weel.points.size() * sizeof(float));
}



Car::~Car()
{

}