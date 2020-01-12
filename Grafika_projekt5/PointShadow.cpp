#include "PointShadow.h"


PointShadow::PointShadow(const int shadow_width, const int shadow_height,
	float near_plane, float far_plane) :
	shadow_width(shadow_width), shadow_height(shadow_height),
	near_plane(near_plane), far_plane(far_plane),
	depthShader("shadow_mvp.vs", "shadow_mvp.fs", "shadow_mvp.gs")
{
	shadow_projection = glm::perspective(glm::radians(90.0f), (float)shadow_width / (float)shadow_height, near_plane, far_plane);

	depthCubeMap = 0;
	glGenFramebuffers(1, &fbo);
	// create depth cubemap texture
	unsigned int depthCubemap;
	glGenTextures(1, &depthCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
	for (unsigned int i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 
			shadow_width, shadow_height, 
			0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubeMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PointShadow::RenderToDepthMap(glm::vec3 positon)
{
	std::vector<glm::mat4> shadow_transforms;
	shadow_transforms.push_back(shadow_projection * glm::lookAt(positon, positon + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadow_transforms.push_back(shadow_projection * glm::lookAt(positon, positon + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadow_transforms.push_back(shadow_projection * glm::lookAt(positon, positon + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadow_transforms.push_back(shadow_projection * glm::lookAt(positon, positon + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadow_transforms.push_back(shadow_projection * glm::lookAt(positon, positon + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadow_transforms.push_back(shadow_projection * glm::lookAt(positon, positon + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	glViewport(0, 0, shadow_width, shadow_width);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClear(GL_DEPTH_BUFFER_BIT);
	depthShader.use();
	for (unsigned int i = 0; i < 6; ++i)
		depthShader.setMat4("shadowMatrices[" + std::to_string(i) + "]", shadow_transforms[i]);
	depthShader.setFloat("far_plane", far_plane);
	depthShader.setVec3("lightPos", positon);
}
