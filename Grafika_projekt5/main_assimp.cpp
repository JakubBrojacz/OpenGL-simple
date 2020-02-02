#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Car.h"
#include "Fog.h"

#include "Shader_m.h"
#include "Camera_m.h"
#include "Model_m.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// window
unsigned int act_width = SCR_WIDTH;
unsigned int act_height = SCR_HEIGHT;

// camera
Camera camera(glm::vec3(30, 30, 30));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Fog fog(5, 10, 20);


enum class CameraMode { Free, Car, Stationary, Following };

auto cameraMode = CameraMode::Free;



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

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);


	// build and compile shaders
	// -------------------------
	Shader ourShader("book.vs", "book.fs");

	// init shader params
	ourShader.use();

	// load models
	// -----------
	Model Sponza("../models/sponza/sponza.obj");
	Model ridingCar("../models/formula1/Formula_1_mesh.obj");

	Car car;

	// init mvp matrices
	// ------------------------------------
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		fog.Update(deltaTime);

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 0. Init per-loop variables
		// -----------------------------------------------
		auto car_model = glm::translate(car.Model(currentFrame), glm::vec3{ 0, -2.7, 0 });
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
			(float)act_width / (float)act_height, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		float near_plane = 0.1f;
		float far_plane = 12.0f;
		auto car_rotation = car.Rotation(currentFrame);
		auto car_light_direction = glm::vec3{ -cos(car_rotation),0,sin(car_rotation) };
		auto car_light_pos = car.PositionVec3(currentFrame) + glm::vec3{ 0,-1,0 };
		car_light_pos += glm::vec3{ 0.2 * sin(car_rotation),0,0.2 * cos(car_rotation) };

		glm::mat4 sponza_model = glm::mat4(1.0f);
		sponza_model = glm::scale(sponza_model, glm::vec3(0.02f, 0.02f, 0.02f));
		car_model = car_model * glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));

		// 0.5. Configure camera
		// -----------------------------------------------
		switch (cameraMode)
		{
		case CameraMode::Car:
			camera.Position = car_light_pos;
			camera.Front = car_light_direction;
			camera.Up = glm::vec3{ 0, 1, 0 };
			break;
		case CameraMode::Stationary:
			camera.Position = glm::vec3{ 24.3672, 15.0172, -10.9168 };
			camera.Front = glm::vec3{ -0.677837, -0.409923, 0.610328 };
			camera.Up = glm::vec3{ -0.304632, 0.91212, 0.274292 };
			break;
		case CameraMode::Following:
			camera.Position = glm::vec3{ 0, 13.3949, -1.03434 };
			view = glm::lookAt(camera.Position, car_light_pos, glm::vec3{ 0,1,0 });
			break;
		}	


		// 2. render scene as normal using the generated depth/shadow map  
		// --------------------------------------------------------------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ourShader.use();

		// render the loaded model
		ourShader.setMat4("ProjectionMatrix", projection);
		ourShader.setVec3("ViewPosition", camera.Position);

		ourShader.setFloat("FogStart", fog.start);
		ourShader.setFloat("FogEnd", fog.end);
		ourShader.setFloat("FogIntensity", fog.intensity);

		ourShader.setVec4("Spot.position", glm::vec4(car_light_pos, 1));
		ourShader.setVec3("Spot.intensity", 1.0f, 1.0f, 1.0f);
		ourShader.setVec3("Spot.direction", car_light_direction);
		ourShader.setFloat("Spot.exponent", 0.1);
		ourShader.setFloat("Spot.cutoff", 30);

		ourShader.setVec3("Kd", 0.2, 0.2, 0.2);
		ourShader.setVec3("Ka", 0.1, 0.1, 0.1);
		ourShader.setVec3("Ks", 0.3, 0.3, 0.3);
		ourShader.setFloat("Shininess", 0.1);

		ourShader.setMat4("ModelViewMatrix", sponza_model);
		ourShader.setMat3("NormalMatrix", glm::transpose(glm::inverse(glm::mat3(sponza_model))));
		ourShader.setMat4("MVP", projection * view * sponza_model);
		Sponza.Draw(ourShader);
		ourShader.setMat4("ModelViewMatrix", car_model);
		ourShader.setMat3("NormalMatrix", glm::transpose(glm::inverse(glm::mat3(car_model))));
		ourShader.setMat4("MVP", projection * view * car_model);
		ridingCar.Draw(ourShader);


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

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		std::cout << "{" << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << "}" << std::endl;
		std::cout << "{" << camera.Front.x << ", " << camera.Front.y << ", " << camera.Front.z << "}" << std::endl;
		std::cout << "{" << camera.Up.x << ", " << camera.Up.y << ", " << camera.Up.z << "}" << std::endl;
		std::cout << "deltatime: " << deltaTime << std::endl;

	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		std::cout << "Camera attached to car" << std::endl;
		cameraMode = CameraMode::Car;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		std::cout << "Camera stationary" << std::endl;
		cameraMode = CameraMode::Stationary;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		std::cout << "Camera following car" << std::endl;
		cameraMode = CameraMode::Following;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		std::cout << "Camera free /debug mode/" << std::endl;
		cameraMode = CameraMode::Free;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		std::cout << "Start fog" << std::endl;
		fog.Begin();
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		std::cout << "End fog" << std::endl;
		fog.End();
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	act_width = width;
	act_height = height;
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

