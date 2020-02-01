#pragma once

class Fog
{
public:
	Fog(float time, float start, float end);

	void Begin();
	void Update(float delta);
	void End();

	~Fog();

	bool running;

	float start;
	float end;
	float intensity;

	float speed;
};