#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Car.h"
#include "Block.h"
#include "Lamp.h"

#include "Shader_m.h"
#include "Camera_m.h"
#include "Model_m.h"

#include "DirectShadow.h"
#include "PointShadow.h"
#include "Floor.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


struct CameraMode
{
	enum Mode { Free, Car, Stationary, Following };
};
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
	Shader ourShader("1.model_loading.vs", "1.model_loading.fs");

	// load models
	// -----------
	Model Sponza("../models/sponza/sponza.obj");
	Model ridingCar("../models/formula1/Formula_1_mesh.obj");


	// set up point shadow
	// ------------------------------------
	PointShadow lamp_light(1024, 1024, 0.5, 12);

	// set up car reflector shadow
	// ------------------------------------
	DirectShadow car_reflector(1024, 1024, 0.1, 24, 60);

	// create models
	// ------------------------------------
	Car car;
	Block block;
	Lamp lamp;
	Floor floor;

	// init shader params
	ourShader.use();
	ourShader.setInt("depthMap", 1);
	ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	//ourShader.setVec4("ourColor", 0, 0, 1, 0);


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

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 0. Init per-loop variables
		// -----------------------------------------------
		auto car_model = car.Model(currentFrame);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
			(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		float near_plane = 0.1f;
		float far_plane = 12.0f;
		auto light_pos = lamp.LightPos;
		auto car_rotation = car.Rotation(currentFrame);
		auto car_light_direction = glm::vec3{ -cos(car_rotation),0,sin(car_rotation) };
		auto car_light_pos = car.PositionVec3(currentFrame) + glm::vec3{ 0,0,0 };
		car_light_pos += glm::vec3{ 0.2 * sin(car_rotation),0,0.2 * cos(car_rotation) };

		glm::mat4 sponza_model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		sponza_model = glm::scale(sponza_model, glm::vec3(0.02f, 0.02f, 0.02f));	// it's a bit too big for our scene, so scale it down
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

		// 1. render scene to depth cubemap
		// --------------------------------
		lamp_light.RenderToDepthMap(light_pos);
		lamp_light.depthShader.setMat4("model", sponza_model);
		Sponza.Draw(lamp_light.depthShader);
		/*lamp_light.depthShader.setMat4("model", car_model);
		ridingCar.Draw(lamp_light.depthShader);*/
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		// 1.5. render scene to depth car reflector map
		// --------------------------------
		//car_reflector.RenderToDepthMap(car_light_pos, car_light_direction);
		car_reflector.RenderToDepthMap(camera.Position, camera.Front);
		car_reflector.depthShader.setMat4("model", sponza_model);
		Sponza.Draw(car_reflector.depthShader);
		/*car_reflector.depthShader.setMat4("model", car_model);
		ridingCar.Draw(car_reflector.depthShader);*/
		glBindFramebuffer(GL_FRAMEBUFFER, 0);



		// 2. render scene as normal using the generated depth/shadow map  
		// --------------------------------------------------------------
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ourShader.use();



		// view/projection transformations
		projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		ourShader.setVec3("lightPos", light_pos);
		ourShader.setVec3("viewPos", camera.Position);
		// set light uniforms
		ourShader.setFloat("far_plane", far_plane);
		ourShader.setVec3("lightPosCar", car_light_pos);
		ourShader.setMat4("lightSpaceMatrix", car_reflector.lightSpaceMatrix);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, lamp_light.depthCubeMap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, car_reflector.depthMap);

		// render the loaded model
		ourShader.setMat4("model", sponza_model);
		Sponza.Draw(ourShader);
		ourShader.setMat4("model", car_model);
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

