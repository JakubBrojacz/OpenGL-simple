#include "DirectShadow.h"

DirectShadow::DirectShadow(const int shadow_width, const int shadow_height,
	float near_plane, float far_plane,
	float angle) :
	shadow_width(shadow_width), shadow_height(shadow_height),
	near_plane(near_plane), far_plane(far_plane),
	angle(angle),
	depthShader("car_shadow_mvp.vs", "car_shadow_mvp.fs"),
	lightSpaceMatrix(0.f)
{
	//lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	light_projection = glm::perspective(glm::radians(angle),
		(GLfloat)shadow_width / (GLfloat)shadow_height,
		near_plane, far_plane);


	glGenFramebuffers(1, &fbo);
	// create depth cubemap texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DirectShadow::RenderToDepthMap(glm::vec3 positon, glm::vec3 direction)
{
	glm::mat4 lightView;
	lightView = glm::lookAt(positon, positon + direction, glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = light_projection * lightView;
	
	depthShader.use();
	depthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

	glViewport(0, 0, shadow_width, shadow_height);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClear(GL_DEPTH_BUFFER_BIT);
}
