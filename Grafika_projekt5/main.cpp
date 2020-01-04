#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>

#include "Car.h"
#include "Block.h"
#include "Lamp.h"
#include "Shader_m.h"
#include "Camera_m.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


glm::mat4 car_pos(float current_frame)
{
	glm::mat4 car_model = glm::mat4(1.0f);
	float currentFrame = (int)current_frame % 30 + (current_frame - (int)current_frame);
	if (currentFrame < 9)
	{
		car_model = glm::translate(car_model, glm::vec3{ -currentFrame, 0, 0 });
	}
	else if (currentFrame < 10)
	{
		float alpha = (currentFrame - 9) * glm::pi<float>() / 2;
		car_model = glm::translate(car_model, glm::vec3{ -9 - sin(alpha), 0, 1 - cos(alpha) });
		car_model = glm::rotate(car_model, alpha, glm::vec3{ 0,1,0 });
	}
	else if (currentFrame < 14)
	{
		car_model = glm::translate(car_model, glm::vec3{ -10 , 0, currentFrame - 9 });
		car_model = glm::rotate(car_model, glm::pi<float>() / 2, glm::vec3{ 0,1,0 });
	}
	else if (currentFrame < 15)
	{
		float alpha = (currentFrame - 14) * glm::pi<float>() / 2;
		car_model = glm::translate(car_model, glm::vec3{ -9 - cos(alpha), 0, 5 + sin(alpha) });
		car_model = glm::rotate(car_model, glm::pi<float>() / 2 + alpha, glm::vec3{ 0,1,0 });
	}
	else if (currentFrame < 24)
	{
		car_model = glm::translate(car_model, glm::vec3{ -9 + currentFrame - 15 , 0, 6 });
		car_model = glm::rotate(car_model, glm::pi<float>(), glm::vec3{ 0,1,0 });
	}
	else if (currentFrame < 25)
	{
		float alpha = (currentFrame - 24) * glm::pi<float>() / 2;
		car_model = glm::translate(car_model, glm::vec3{ sin(alpha)  , 0, 5 + cos(alpha) });
		car_model = glm::rotate(car_model, glm::pi<float>() + alpha, glm::vec3{ 0,1,0 });
	}
	else if (currentFrame < 29)
	{
		car_model = glm::translate(car_model, glm::vec3{ 1, 0, 5 - (currentFrame - 25) });
		car_model = glm::rotate(car_model, glm::pi<float>() * 3 / 2, glm::vec3{ 0,1,0 });
	}
	else if (currentFrame < 30)
	{
		float alpha = (currentFrame - 29) * glm::pi<float>() / 2;
		car_model = glm::translate(car_model, glm::vec3{ cos(alpha), 0, 1 - sin(alpha) });
		car_model = glm::rotate(car_model, glm::pi<float>() * 3 / 2 + alpha, glm::vec3{ 0,1,0 });
	}

	return car_model;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);


	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("mvp.vs", "mvp.fs");

	Car car;
	Block block;
	Lamp lamp;


	ourShader.use();

	ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	//ourShader.setVec4("ourColor", 0, 0, 1, 0);
	

	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per frame logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		auto car_model = glm::mat4(1.0f);
		car_model = car_pos(currentFrame);


		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = camera.GetViewMatrix();
		projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		ourShader.setMat4("projection", projection); 
		// note: currently we set the projection matrix each frame,
		//but since the projection matrix rarely changes it's often best practice 
		//to set it outside the main loop only once.
		ourShader.setMat4("view", view);
		ourShader.setVec3("lightPos", lamp.LightPos);
		ourShader.setVec3("viewPos", camera.Position);

		car.Draw(car_model, ourShader);
		block.Draw(model, ourShader);
		lamp.Draw(model, ourShader);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}