#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "cmath"

#include "logic/filehandling.h"
#include "logic/movement.h"
#include "enumeration/worldElements.h"
#include "camera/camera.h"

glm::mat4 M;
glm::mat4 V;
glm::mat4 P;

struct CameraSpeed cameraSpeed;
struct CameraAngle cameraAngle;

// Error processing callback procedure
void error_callback(int error, const char *description)
{
	fputs(description, stderr);
}

// Initialization code procedure
void initOpenGLProgram(GLFWwindow *window)
{
	initShaders();
	//************Place any code here that needs to be executed once, at the program start************
}

// Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow *window)
{
	freeShaders();
	//************Place any code here that needs to be executed once, after the main loop ends************
}

void drawScene(GLFWwindow *window, int **matrix, struct CameraAngle cameraAngle)
{
	glClearColor(0.2, 0.4, 0.7, 0.5);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	V = glm::lookAt(glm::vec3(0.0f, 0.0f, cameraAngle.zoom), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	P = glm::perspective(50.0f * PI / 180.0f, 1.0f, 1.0f, 5000.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, value_ptr(V));

	M = glm::mat4(1.0f);
	M = glm::rotate(M, -cameraAngle.horizontal*PI/180, glm::vec3(0.0f,1.0f,0.0f));
	M = glm::rotate(M, -cameraAngle.vertical*PI/180, glm::vec3(1.0f,0.0f,0.0f));

	for (int i = 0; i < MAX_MAP_SIZE; i++)
	{
		for (int j = 0; j < MAX_MAP_SIZE; j++)
		{
			glm::mat4 M_copy = M;
			M_copy = glm::translate(M, glm::vec3(i * 2 - MAX_MAP_SIZE + 1, j * 2 - MAX_MAP_SIZE + 1, 0.0f));
			
			switch (matrix[i][j])
			{
			case worldElements::FLOOR:
				glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_copy));
				glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
				Models::cube.drawSolid();
				break;
			case worldElements::WALL:
				glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_copy));
				glUniform4f(spLambert->u("color"), 1.0, 0.6, 1.0, 0.8);
				Models::cube.drawSolid();
				M_copy = glm::translate(M_copy, glm::vec3(0.0f, 0.0f, 2.0f));
				glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_copy));
				Models::cube.drawSolid();
				break;
			case worldElements::TARGET:
				glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_copy));
				glUniform4f(spLambert->u("color"), 0.0, 0.6, 1.0, 0.8);
				Models::cube.drawSolid();
				break;
			default:
				break;
			}
		}
	}

	glfwSwapBuffers(window);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		cameraSpeed = changeCameraSpeedOnPress(key, cameraSpeed);
	}
	else if (action == GLFW_RELEASE) {
		cameraSpeed = changeCameraSpeedOnRelease(key, cameraSpeed);
	}
}

int main(void)
{
	GLFWwindow *window;					  // Pointer to object that represents the application window
	glfwSetErrorCallback(error_callback); // Register error processing callback procedure

	if (!glfwInit())
	{ // Initialize GLFW library
		fprintf(stderr, "Can't initialize GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL); // Create a window 500pxx500px titled "OpenGL" and an OpenGL context associated with it.
	glfwSetKeyCallback(window, key_callback);
	if (!window) // If no window is opened then close the program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); // Since this moment OpenGL context corresponding to the window is active and all OpenGL calls will refer to this context.
	glfwSwapInterval(1);			// During vsync wait for the first refresh

	GLenum err;
	if ((err = glewInit()) != GLEW_OK)
	{ // Initialize GLEW library
		fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); // Call initialization procedure

	File_data file_data = read_new_map();

	cameraSpeed = initCameraSpeed();
	cameraAngle = initCameraAngle();
	glfwSetTime(0);

	// Main application loop
	while (!glfwWindowShouldClose(window)) // As long as the window shouldnt be closed yet...
	{
		cameraAngle = changeCameraAngle(cameraAngle, cameraSpeed, glfwGetTime());

		glfwSetTime(0);
		drawScene(window, file_data.matrix, cameraAngle);
		glfwPollEvents(); // Process callback procedures corresponding to the events that took place up to now
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); // Delete OpenGL context and the window.
	glfwTerminate();		   // Free GLFW resources
	exit(EXIT_SUCCESS);
}