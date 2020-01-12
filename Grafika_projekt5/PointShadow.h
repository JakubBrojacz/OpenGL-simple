#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader_m.h"
#include <vector>


class PointShadow
{
public:
	unsigned int fbo;
	unsigned int depthCubeMap;
	Shader depthShader;

	PointShadow(const int shadow_width, const int shadow_height,
		float near_plane, float far_plane);

	void RenderToDepthMap(glm::vec3 positon);
private:
	int shadow_width;
	int shadow_height;
	float near_plane;
	float far_plane;
	glm::mat4 shadow_projection;
};