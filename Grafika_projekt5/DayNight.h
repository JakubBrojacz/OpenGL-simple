#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class DayNight
{
public:
	DayNight(float time);

	void Update(float delta);
	glm::vec3 Ambient();
	glm::vec3 Color();
	glm::vec3 Direction();

	~DayNight();

	// 0-7 : day
	// 7-9 : down
	// 9-16 : night
	// 16-18 : dusk
	float time;

	float speed;

private:
	float t1 = 6; // begin down
	float t2 = 8; // mid of down
	float t3 = 9; // begin of night
	float t4 = 15; // begin of dusk
	float t5 = 17; // mid of dusk
	float t6 = 18; //begin of day

	glm::vec3 day_color{ 1,1,1 };
	glm::vec3 down_mid_color{ 1, 0.5, 0.3 };
};
