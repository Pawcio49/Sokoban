#include "torus.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <vector>
#define GLM_FORCE_RADIANS

#include "common_header.h"
#include "logic/filehandling.h"
#include "logic/movement.h"
#include "enumeration/worldElements.h"
#include "camera/camera.h"
#include "unistd.h"
#include "ViewManaging.h"
#include "3D_models.h"

glm::mat4 M;
Player player;
ViewManaging viewManaging;
std::vector<Crate> crate;
File_data file_data; 
float aspectRatio = 1;

struct CameraSpeed cameraSpeed;
struct CameraAngle cameraAngle;
ShaderProgram *sp;
GLuint tex[3];
std::vector<GLuint> model_tex;
std::vector<Model3D> models_3d;

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
	tex[2] = viewManaging.readTexture("target.png");
    Model3D* model = new Model3D("lamp.obj"); 
    model_tex.push_back(viewManaging.readTexture("lampa.png"));
    model_tex.push_back(viewManaging.readTexture("venom.png"));
    models_3d.push_back(*model);
    model = new Model3D("venom.obj"); 
    models_3d.push_back(*model);

}

// Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow *window)
{
	glDeleteTextures(2, tex);
	delete sp;
}

void drawScene(GLFWwindow *window, int **matrix, struct CameraAngle cameraAngle, int **goals)
{
	glClearColor(0.2, 0.4, 0.7, 0.5);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewManaging.spUse();
	viewManaging.setPAndV(cameraAngle);


	if(!player.lock){
        player.render(cameraAngle,models_3d.at(1));
        for(int i=0;i<crate.size();i++){
		    crate[i].render();
	    }
    }
 
	M = glm::mat4(1.0f);

	glm::mat4 M_copy;

	for(int i=0; i<MAX_MAP_SIZE; i++){
		for(int j=0; j<MAX_MAP_SIZE; j++){
			M_copy = M;
			M_copy = glm::translate(M, glm::vec3(i * 2 - MAX_MAP_SIZE + 1, j * 2 - MAX_MAP_SIZE + 1, 0.0f));
            if((i==0 && j==0)||(i==11&j==11)||(i==0&&j==11)||(i==11&&j==0)){
                glm::mat4 temp = glm::rotate(M_copy, 90*PI/180, glm::vec3(1.0f,0.0f,0.0f));
                temp = glm::translate(temp, glm::vec3(0.f,3.f, 0.0f));
                temp = glm::scale(temp, glm::vec3(3.f,3.f,3.f));
			    viewManaging.setM(temp);
                models_3d.at(0).render(sp, model_tex.at(0));
            }
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
                    glUniform1i(sp->u("textureMap0"), 0);

                    M_copy = glm::translate(M_copy, glm::vec3(0.f,0.f, 1.f));
                   //M_copy = glm::scale(M_copy, glm::vec3(0.5f,0.5f,0.5f));
					viewManaging.setM(M_copy);
                    glActiveTexture(GL_TEXTURE0);
	                glBindTexture(GL_TEXTURE_2D, tex[2]);

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
