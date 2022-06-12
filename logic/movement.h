#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../constants.h"
#include "../allmodels.h"
#include "../lodepng.h"
#include "../ViewManaging.h"
#include "../camera/camera.h"
#include "../3D_models.h"
#include "../common_header.h"

#ifndef OPENGL_GAME_MOVEMENT_H
#define OPENGL_GAME_MOVEMENT_H

class Crate{
    private:
        ViewManaging viewManaging;
        GLuint tex;
        glm::mat4 position;
        float target_x;
        float target_y;
    public:
        int x;
        int y;
        Crate();
        Crate(ShaderProgram *sp, int x,int y);
        void move(int x,int y, int **matrix);
        void render();
};
class Player{
    private:
        ViewManaging viewManaging;
        GLuint tex;
		glm::mat4 position;
	    int x;
        int y;
        int direction;
        float target_x;
        float target_y;
    public:
    bool lock;

    Player();
	Player(ShaderProgram *sp, int x, int y);
	void render(struct CameraAngle cameraAngle, Model3D model);
	void move_forward(int **matrix,std::vector<Crate> &crate);
	void rotate_left();
	void rotate_right();
};
#endif 
