#include "Fog.h"

Fog::Fog(float time, float start, float end) :
	start(start), end(end), intensity(0), running(false)
{
	speed = 1 / time;
}

void Fog::Begin()
{
	running = true;
}

void Fog::Update(float delta)
{
	if (running)
	{
		if (intensity < 1)
			intensity += speed * delta;
	}
	else
	{
		if (intensity > 0)
			intensity -= speed * delta;
	}
}

void Fog::End()
{
	running = false;
}

Fog::~Fog()
{
}
