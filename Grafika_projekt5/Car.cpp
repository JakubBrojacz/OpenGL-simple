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
	weel_model = glm::translate(weel_model, glm::vec3{ 1.5, 1, 0 });
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

glm::vec3 Car::PositionVec3(float current_frame)
{
	float currentFrame = (int)current_frame % 30 + (current_frame - (int)current_frame);
	if (currentFrame < 9)
	{
		return glm::vec3{ -currentFrame, 0, 0 };
	}
	else if (currentFrame < 10)
	{
		float alpha = (currentFrame - 9) * glm::pi<float>() / 2;
		return glm::vec3{ -9 - sin(alpha), 0, 1 - cos(alpha) };
	}
	else if (currentFrame < 14)
	{
		return glm::vec3{ -10 , 0, currentFrame - 9 };
	}
	else if (currentFrame < 15)
	{
		float alpha = (currentFrame - 14) * glm::pi<float>() / 2;
		return glm::vec3{ -9 - cos(alpha), 0, 5 + sin(alpha) };
	}
	else if (currentFrame < 24)
	{
		return glm::vec3{ -9 + currentFrame - 15 , 0, 6 };
	}
	else if (currentFrame < 25)
	{
		float alpha = (currentFrame - 24) * glm::pi<float>() / 2;
		return glm::vec3{ sin(alpha), 0, 5 + cos(alpha) };
	}
	else if (currentFrame < 29)
	{
		return glm::vec3{ 1, 0, 5 - (currentFrame - 25) };
	}
	else if (currentFrame < 30)
	{
		float alpha = (currentFrame - 29) * glm::pi<float>() / 2;
		return glm::vec3{ cos(alpha), 0, 1 - sin(alpha) };
	}
	return glm::vec3{ 0,0,0 };
}

float Car::Rotation(float current_frame)
{
	float currentFrame = (int)current_frame % 30 + (current_frame - (int)current_frame);
	if (currentFrame < 9)
	{
		return 0;
	}
	else if (currentFrame < 10)
	{
		return (currentFrame - 9) * glm::pi<float>() / 2;
	}
	else if (currentFrame < 14)
	{
		return glm::pi<float>() / 2;
	}
	else if (currentFrame < 15)
	{
		return glm::pi<float>() / 2 + (currentFrame - 14) * glm::pi<float>() / 2;
	}
	else if (currentFrame < 24)
	{
		return glm::pi<float>();
	}
	else if (currentFrame < 25)
	{
		return glm::pi<float>() + (currentFrame - 24) * glm::pi<float>() / 2;
	}
	else if (currentFrame < 29)
	{
		return glm::pi<float>() * 3 / 2;
	}
	else if (currentFrame < 30)
	{
		return glm::pi<float>() * 3 / 2 + (currentFrame - 29) * glm::pi<float>() / 2;
	}

	return 0;
}

glm::mat4 Car::Model(float current_frame)
{
	glm::mat4 car_model = glm::mat4(1.0f);
	car_model = glm::translate(car_model, PositionVec3(current_frame));
	float alpha = Rotation(current_frame);
	car_model = glm::rotate(car_model, alpha, glm::vec3{ 0,1,0 });
	return car_model;
}



Car::~Car()
{

}