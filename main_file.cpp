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
#include "logic/filehandling.h"
#include "logic/movement.h"
#include "enumeration/worldElements.h"
#include <algorithm>

glm::mat4 M;
glm::mat4 V;
glm::mat4 P;
Player player;
std::vector<Crate> crate;
File_data file_data; 
float aspectRatio = 1;
//Error processing callback procedure
void error_callback(int error, const char* description) {
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
	initShaders();
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	//************Place any code here that needs to be executed once, at the program start************

}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
	//************Place any code here that needs to be executed once, after the main loop ends************
}

void drawScene(GLFWwindow* window, int **matrix,int **goals) {
	glClearColor(0.2, 0.4, 0.7, 0.5);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	V = glm::lookAt(glm::vec3(0.0f, 0.0f, 40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	P = glm::perspective(50.0f * PI / 180.0f, 1.0f, 1.0f, 5000.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, value_ptr(V));
	if(!player.lock){
        player.render();
        for(int i=0;i<crate.size();i++){
		    crate[i].render();
	    }
    }
	for(int i=0; i<MAX_MAP_SIZE; i++){
		for(int j=0; j<MAX_MAP_SIZE; j++){
				M = glm::mat4(1.0f);
				//M = glm::scale(M, glm::vec3(0.05f, 0.1f, 0.05f));
				M = glm::translate(M, glm::vec3(i*2-MAX_MAP_SIZE+1, j*2-MAX_MAP_SIZE+1, 0.0f));

			switch (matrix[i][j])
			{
			case 2:
			case worldElements::FLOOR:
				glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M));
				glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
				Models::cube.drawSolid();
				break;
			case worldElements::WALL:
				glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M));
				glUniform4f(spLambert->u("color"), 1.0, 0.6, 1.0, 0.8);
				Models::cube.drawSolid();
				break;
			}
            switch(goals[i][j]){
                case 1:
                    M = glm::translate(M, glm::vec3(0.f,0.f, 0.8f));
                    glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M));
				    glUniform4f(spLambert->u("color"), 0.0, 0.6, 1.0, 0.8);
				    Models::torus.drawSolid();
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

    }
}

int main(void)
{
	GLFWwindow* window; //Pointer to object that represents the application window
	glfwSetErrorCallback(error_callback);//Register error processing callback procedure


	if (!glfwInit()) { //Initialize GLFW library
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

	glfwMakeContextCurrent(window); //Since this moment OpenGL context corresponding to the window is active and all OpenGL calls will refer to this context.
	glfwSwapInterval(1); //During vsync wait for the first refresh

	GLenum err;
	if ((err = glewInit()) != GLEW_OK) { //Initialize GLEW library
		fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Call initialization procedure

	file_data = read_new_map();
	player = Player(3,3);
    for(int i=0;i<12;i++){
        for(int j=0;j<12;j++){
            if(file_data.matrix[i][j]==2){
                crate.push_back(Crate(i,j));
            }
        }
    }
//Main application loop
	while (!glfwWindowShouldClose(window)) //As long as the window shouldnt be closed yet...
	{
		drawScene(window, file_data.matrix,file_data.goals);
		glfwPollEvents(); //Process callback procedures corresponding to the events that took place up to now

	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Delete OpenGL context and the window.
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}
