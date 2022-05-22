/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


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

using namespace glm;

mat4 M_sun;
mat4 M_torus;
mat4 M_cube;
mat4 M_wheel;
mat4 M;
mat4 V;
mat4 P;
float speed = 100.0;
float wheel_speed = 0;

//Error processing callback procedure
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Initialization code procedure
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	//************Place any code here that needs to be executed once, at the program start************

}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
	//************Place any code here that needs to be executed once, after the main loop ends************
}

//Drawing procedure
/* Obracajace sie slonca
void drawScene(GLFWwindow* window, float angle) {
	//************Place any code here that draws something inside the window******************l
	glClearColor(0.2, 0.4, 0.7, 0.5);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	V = lookAt(vec3(0.0f, 0.0f, -5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	P = perspective(50.0f * PI / 180.0f, 1.0f, 1.0f, 50.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, value_ptr(V));


	M_sun = mat4(1.0f);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_sun));
	glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
	static Models::Sphere sun(0.5, 36, 36);
	sun.drawSolid();

	M = rotate(M_sun, angle * PI / 180.0f, vec3(0.0f, 1.0f, 0.0f));
	M = translate(M, vec3(1.5f, 0.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M));
	glUniform4f(spLambert->u("color"), 0.8, 0.1, 0.45, 0.8);
	static Models::Sphere planet1(0.2, 36, 36);
	planet1.drawSolid();

	M = rotate(M, angle * PI / 180.0f, vec3(0.0f, 1.0f, 0.0f));
	M = translate(M, vec3(0.5f, 0.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M));
	glUniform4f(spLambert->u("color"), 0.8, 0.6, 0.45, 0.8);
	static Models::Sphere moon1(0.1, 36, 36);
	moon1.drawSolid();

	M = rotate(M_sun, angle * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
	M = translate(M, vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M));
	glUniform4f(spLambert->u("color"), 0.8, 0.1, 0.45, 0.8);
	static Models::Sphere planet2(0.25, 36, 36);
	planet2.drawSolid();

	M = rotate(M, angle * PI / 180.0f, vec3(1.0f, 0.0f, 0.0f));
	M = translate(M, vec3(0.0f, 0.3f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M));
	glUniform4f(spLambert->u("color"), 0.8, 0.6, 0.45, 0.8);
	static Models::Sphere moon2(0.07, 36, 36);
	moon2.drawSolid();

	glfwSwapBuffers(window);
}*/

/*void drawCog(mat4 M_torus, float angle, int is_left) {

	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_torus));
	glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
	Models::torus.drawSolid();

	for (int i = 0; i < 12; i++) {
		M = rotate(M_torus, 30 * i * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
		M = translate(M, vec3(1.1f, 0.0f, 0.0f));
		M = scale(M, vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M));
		glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
		Models::cube.drawSolid();
	}
}*/

void drawCog(mat4 M_torus) {

	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_torus));
	glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
	Models::torus.drawSolid();

	for (int i = 0; i < 12; i++) {
		M = rotate(M_torus, 30 * i * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
		M = translate(M, vec3(1.1f, 0.0f, 0.0f));
		M = scale(M, vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M));
		glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
		Models::cube.drawSolid();
	}
}


void drawScene(GLFWwindow* window, float angle) {
	//************Place any code here that draws something inside the window******************l
	glClearColor(0.2, 0.4, 0.7, 0.5);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	V = lookAt(vec3(0.0f, 0.0f, -5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	P = perspective(50.0f * PI / 180.0f, 1.0f, 1.0f, 500000.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, value_ptr(V));

	M_torus = mat4(1.0f);
	M_torus = translate(M_torus, vec3(-1.1f, 0.0f, 0.0f));
	M_torus = rotate(M_torus, angle * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
	drawCog(M_torus);
	
	/*M_torus = scale(M_torus, vec3(0.3f, 0.3f, 0.3f));
	M_torus = rotate(M_torus, -2*angle * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
	drawCog(M_torus);*/

	M_torus = mat4(1.0f);
	M_torus = translate(M_torus, vec3(1.1f, 0.0f, 0.0f));
	M_torus = rotate(M_torus, (-angle + 15) * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
	drawCog(M_torus);
	
	/*M_torus = scale(M_torus, vec3(0.3f, 0.3f, 0.3f));
	M_torus = rotate(M_torus, 2*angle * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
	drawCog(M_torus);*/

	/*M_torus = mat4(1.0f);
	M_torus = rotate(M_torus, 90 * PI / 180.0f, vec3(1.0f, 0.0f, 0.0f));
	M_torus = rotate(M_torus, -angle * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_torus));
	glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
	Models::torus.drawSolid();*/

	glfwSwapBuffers(window);
}

/* plaskie torusy
void drawScene(GLFWwindow* window, float angle) {
	//************Place any code here that draws something inside the window******************l
	glClearColor(0.2, 0.4, 0.7, 0.5);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	V = lookAt(vec3(0.0f, 0.0f, 8.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	P = perspective(50.0f * PI / 180.0f, 1.0f, 1.0f, 500000.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, value_ptr(V));

	bool rotateLeft = true;

	for (int i = 0; i < 6; i++) {
		M_torus = mat4(1.0f);
		M_torus = rotate(M_torus, 60*i * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
		M_torus = translate(M_torus, vec3(-1.0f, -2.0f, 0.0f));
		if (rotateLeft) {
			M_torus = rotate(M_torus,  15 + angle * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
			rotateLeft = false;
		}
		else {
			M_torus = rotate(M_torus, -angle * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
			rotateLeft = true;
		}
		drawCog(M_torus);
	}

	glfwSwapBuffers(window);
}*/

// pochylone torusy
/*void drawScene(GLFWwindow* window, float angle) {
	//************Place any code here that draws something inside the window******************l
	glClearColor(0.2, 0.4, 0.7, 0.5);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	V = lookAt(vec3(0.0f, 4.0f, 8.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	P = perspective(50.0f * PI / 180.0f, 1.0f, 1.0f, 500000.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, value_ptr(V));

	bool rotateLeft = true;

	for (int i = 0; i < 6; i++) {
		M_torus = mat4(1.0f);
		//ponizsza linia, zeby dodatkowo sie wszystko obracalo
		//M_torus = rotate(M_torus, angle * PI / 180.0f, vec3(0.0f, 1.0f, 0.0f));
		M_torus = rotate(M_torus, 60 * i * PI / 180.0f, vec3(0.0f, 1.0f, 0.0f));
		M_torus = translate(M_torus, vec3(0.0, 0.0f, -2.0f));
		if (rotateLeft) {
			M_torus = rotate(M_torus, 15 + angle * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
			rotateLeft = false;
		}
		else {
			M_torus = rotate(M_torus, -angle * PI / 180.0f, vec3(0.0f, 0.0f, 1.0f));
			rotateLeft = true;
		}
		drawCog(M_torus);
	}

	glfwSwapBuffers(window);
}*/

/*void drawScene(GLFWwindow* window, float angle, float wheel_angle, float const_wheel_angle) {
	//************Place any code here that draws something inside the window******************l
	glClearColor(0.2, 0.4, 0.7, 0.5);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	V = lookAt(vec3(-4.0f, 1.0f, 4.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	P = perspective(50.0f * PI / 180.0f, 1.0f, 1.0f, 500000.0f);

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, value_ptr(V));

	M = mat4(1.0f);
	M = rotate(M, angle * PI / 180.0f, vec3(0.0f, 1.0f, 0.0f));

	M_cube = scale(M, vec3(1.5f, 0.125f, 1.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_cube));
	glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
	Models::cube.drawSolid();

	static Models::Torus wheel(0.3, 0.1, 36, 36);

	M_wheel = translate(M, vec3(1.5f, 0.0f, 1.0f));
	M_wheel = rotate(M_wheel, const_wheel_angle * PI / 180.f, vec3(1.0f, 0.0f, 0.0f));
	M_wheel = rotate(M_wheel, wheel_angle * PI / 180.f, vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_wheel));
	glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
	wheel.drawSolid();

	M_wheel = translate(M, vec3(-1.5f, 0.0f, 1.0f));
	M_wheel = rotate(M_wheel, const_wheel_angle * PI / 180.f, vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_wheel));
	glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
	wheel.drawSolid();

	M_wheel = translate(M, vec3(1.5f, 0.0f, -1.0f));
	M_wheel = rotate(M_wheel, const_wheel_angle * PI / 180.f, vec3(1.0f, 0.0f, 0.0f));
	M_wheel = rotate(M_wheel, wheel_angle * PI / 180.f, vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_wheel));
	glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
	wheel.drawSolid();

	M_wheel = translate(M, vec3(-1.5f, 0.0f, -1.0f));
	M_wheel = rotate(M_wheel, const_wheel_angle * PI / 180.f, vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(M_wheel));
	glUniform4f(spLambert->u("color"), 0.2, 0.6, 0.45, 0.8);
	wheel.drawSolid();

	glfwSwapBuffers(window);
}*/

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT)
			speed = -30.14;
		else if (key == GLFW_KEY_RIGHT)
			speed = 30.14;
	}
	else if (action == GLFW_RELEASE) {
		speed = 0;
		
	}

	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_D)
			wheel_speed = -80.14;
		else if (key == GLFW_KEY_A)
			wheel_speed = 80.14;
	}
	else if (action == GLFW_RELEASE) {
		wheel_speed = 0;
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

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Create a window 500pxx500px titled "OpenGL" and an OpenGL context associated with it.
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

	float angle = 0;
	float wheel_angle = 0;
	float const_wheel_angle = 0;
	float const_wheel_speed = 100;
	glfwSetTime(0);

	//Main application loop
	while (!glfwWindowShouldClose(window)) //As long as the window shouldnt be closed yet...
	{
		angle += speed * glfwGetTime();
		wheel_angle += wheel_speed * glfwGetTime();
		const_wheel_angle += const_wheel_speed * glfwGetTime();
		glfwSetTime(0);
		//drawScene(window, angle, wheel_angle, const_wheel_angle); //Execute drawing procedure
		drawScene(window, angle);
		glfwPollEvents(); //Process callback procedures corresponding to the events that took place up to now

	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Delete OpenGL context and the window.
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}