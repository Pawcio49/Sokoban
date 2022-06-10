#include <glm/ext/matrix_clip_space.hpp>
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
#include "unistd.h"
#include "ViewManaging.h"

glm::mat4 M;
Player player;
ViewManaging viewManaging;
std::vector<Crate> crate;
File_data file_data; 
float aspectRatio = 1;

struct CameraSpeed cameraSpeed;
struct CameraAngle cameraAngle;

ShaderProgram *sp;
GLuint tex[2];

// Error processing callback procedure
void error_callback(int error, const char *description)
{
	fputs(description, stderr);
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height<500 || width<500){
        return;
    }

	glViewport(0, 0, width, height);

}

//Initialization code procedure
void initOpenGLProgram(GLFWwindow* window) {
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	//************Place any code here that needs to be executed once, at the program start************

	sp=new ShaderProgram("v_simplest.glsl",NULL,"f_simplest.glsl");
	viewManaging.setSp(sp);

	tex[0] = viewManaging.readTexture("bricks.png");
	tex[1] = viewManaging.readTexture("stone-wall.png");
}

// Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow *window)
{
	glDeleteTextures(2, tex);
	// delete sp; TODO: Destruktor viewManaging
}

void drawScene(GLFWwindow *window, int **matrix, struct CameraAngle cameraAngle, int **goals)
{
	glClearColor(0.2, 0.4, 0.7, 0.5);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewManaging.spUse();
	viewManaging.setPAndV(cameraAngle.zoom);


	if(!player.lock){
        player.render(cameraAngle);
        for(int i=0;i<crate.size();i++){
		    crate[i].render();
	    }
    }
 
	M = glm::mat4(1.0f);
	M = glm::rotate(M, -cameraAngle.horizontal*PI/180, glm::vec3(0.0f,1.0f,0.0f));
	M = glm::rotate(M, -cameraAngle.vertical*PI/180, glm::vec3(1.0f,0.0f,0.0f));

	glm::mat4 M_copy;

	for(int i=0; i<MAX_MAP_SIZE; i++){
		for(int j=0; j<MAX_MAP_SIZE; j++){
			M_copy = M;
			M_copy = glm::translate(M, glm::vec3(i * 2 - MAX_MAP_SIZE + 1, j * 2 - MAX_MAP_SIZE + 1, 0.0f));
			viewManaging.setM(M_copy);

			switch (matrix[i][j])
			{
			case 2:
			case worldElements::FLOOR:
				viewManaging.setAttrib(tex[1]);
				break;
			case worldElements::WALL:
				viewManaging.setAttrib(tex[0]);
				M_copy = glm::translate(M_copy, glm::vec3(0.0f, 0.0f, 2.0f));
				viewManaging.setM(M_copy);
				viewManaging.setAttrib(tex[0]);
				break;
			}
            switch(goals[i][j]){
                case 1:
                    M_copy = glm::translate(M, glm::vec3(0.f,0.f, 0.8f));
					viewManaging.setM(M_copy);
				break;
            }
		}
	}

	glfwSwapBuffers(window);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(!player.lock){
        if(action == GLFW_REPEAT || action == GLFW_PRESS){
			if(key == GLFW_KEY_LEFT){
				player.rotate_left();
			}
			if(key == GLFW_KEY_RIGHT){
				player.rotate_right();
			}
			if(key == GLFW_KEY_UP){
				player.move_forward(file_data.matrix,crate);
			}
        }
		if (action == GLFW_PRESS) {
			cameraSpeed = changeCameraSpeedOnPress(key, cameraSpeed);
		}
		else if (action == GLFW_RELEASE) {
			cameraSpeed = changeCameraSpeedOnRelease(key, cameraSpeed);
		}
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
	window = glfwCreateWindow(900, 900, "Sokoban", NULL, NULL);  //Create a window 500pxx500px titled "OpenGL" and an OpenGL context associated with it.
	glfwSetKeyCallback(window, key_callback);
	

    if (!window) //If no window is opened then close the program
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

	file_data = read_new_map();
	player = Player(sp, 3,3);
    for(int i=0;i<12;i++){
        for(int j=0;j<12;j++){
            if(file_data.matrix[i][j]==2){
                crate.push_back(Crate(sp, i,j));
            }
        }
    }
//Main application loop
	cameraSpeed = initCameraSpeed();
	cameraAngle = initCameraAngle();
	glfwSetTime(0);
	while (!glfwWindowShouldClose(window)) // As long as the window shouldnt be closed yet...
	{
		cameraAngle = changeCameraAngle(cameraAngle, cameraSpeed, glfwGetTime());
		glfwSetTime(0);
		drawScene(window, file_data.matrix,cameraAngle,file_data.goals);
		glfwPollEvents(); // Process callback procedures corresponding to the events that took place up to now
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); // Delete OpenGL context and the window.
	glfwTerminate();		   // Free GLFW resources
	exit(EXIT_SUCCESS);
}
