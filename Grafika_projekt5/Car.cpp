#include "Car.h"


Car::Car()
{
}


glm::vec3 Car::PositionVec3(float current_frame)
{
	//{21.8072, 11.3534, -9.24598}
	//{-24.3647, 11.2711, 7.90922}
	//{-23.9164, 11.5306, -8.11911}
	//{23.9164, 11.5306, 8.11911}
	float currentFrame = (int)current_frame % 30 + (current_frame - (int)current_frame);
	//float currentFrame = 1;
	if (currentFrame < 9)
	{
		return glm::vec3{ -5.1*currentFrame+23, 11, -8 };
	}
	else if (currentFrame < 10)
	{
		float alpha = (currentFrame - 9) * glm::pi<float>() / 2;
		return glm::vec3{ -22.9 - sin(alpha), 11, -7 - cos(alpha) };
	}
	else if (currentFrame < 14)
	{
		return glm::vec3{ -23.9 , 11, 3.5f*(currentFrame - 10) - 7 };
	}
	else if (currentFrame < 15)
	{
		float alpha = (currentFrame - 14) * glm::pi<float>() / 2;
		return glm::vec3{ -22.9 - cos(alpha), 11, 7 + sin(alpha) };
	}
	else if (currentFrame < 24)
	{
		return glm::vec3{ -22.9 + 5.1f*(currentFrame - 15) , 11, 8 };
	}
	else if (currentFrame < 25)
	{
		float alpha = (currentFrame - 24) * glm::pi<float>() / 2;
		return glm::vec3{ 22.9+sin(alpha), 11, 7 + cos(alpha) };
	}
	else if (currentFrame < 29)
	{
		return glm::vec3{ 23.9, 11, 7 - 3.5f*(currentFrame - 25) };
	}
	else if (currentFrame < 30)
	{
		float alpha = (currentFrame - 29) * glm::pi<float>() / 2;
		return glm::vec3{ 22.9+cos(alpha), 11, -7 - sin(alpha) };
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