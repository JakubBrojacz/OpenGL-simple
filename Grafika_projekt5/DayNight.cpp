#include "DayNight.h"


// 0-7 : day
// 7-9 : down
// 9-16 : night
// 16-18 : dusk

DayNight::DayNight(float time) : speed(18.f/time), time(0)
{
}

void DayNight::Update(float delta)
{
	time = fmod(time+ delta * speed, 18);
}

glm::vec3 DayNight::Ambient()
{
	if (time < t1)
		return day_color / 5.f;
	if (time < t2)
		return day_color / 5.f - (day_color / 5.f - down_mid_color / 10.f) * (time - t1) / (t2 - t1);
	if (time < t3)
		return down_mid_color / 10.f - (down_mid_color / 10.f - day_color / 40.f) * (time - t2) / (t3 - t2);
	if (time < t4)
		return day_color / 40.f;
	if (time < t5)
		return day_color / 40.f - (day_color / 40.f - down_mid_color / 10.f) * (time - t4) / (t5 - t4);
	if (time < t6)
		return down_mid_color / 10.f - (down_mid_color / 10.f - day_color / 5.f) * (time - t5) / (t6 - t5);
}

glm::vec3 DayNight::Color()
{
	if(time< t1)
		return day_color;
	if(time< t2)
		return day_color - (day_color - down_mid_color) * (time - t1)/(t2-t1);
	if (time < t3)
		return down_mid_color - down_mid_color * (time - t2) / (t3 - t2);
	if (time < t4)
		return glm::vec3(0);
	if (time < t5)
		return down_mid_color * (time - t4) / (t5 - t4);
	if (time < t6)
		return down_mid_color + (day_color - down_mid_color) * (time - t5) / (t6 - t5);

	return day_color;
}

glm::vec3 DayNight::Direction()
{
	float alpha = (time / 18) * 2 * glm::pi<float>();
	return glm::vec3(-0.2, sin(alpha), cos(alpha));
}

DayNight::~DayNight()
{
}
