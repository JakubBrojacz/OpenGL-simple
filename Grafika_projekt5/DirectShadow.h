#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader_m.h"


class DirectShadow
{
public:
	unsigned int fbo;
	unsigned int depthMap;
	Shader depthShader;
	glm::mat4 lightSpaceMatrix;

	DirectShadow(const int shadow_width, const int shadow_height,
		float near_plane, float far_plane,
		float angle);

	void RenderToDepthMap(glm::vec3 positon, glm::vec3 direction);
private:
	int shadow_width;
	int shadow_height;
	float near_plane;
	float far_plane;
	float angle;
	glm::mat4 light_projection;
};