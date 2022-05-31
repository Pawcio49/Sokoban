#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"

#ifndef LLC_GAME_MOVEMENT_H
#define LLC_GAME_MOVEMENT_H

class Crate{
    private:
        glm::mat4 position;
        float target_x;
        float target_y;
    public:
        int x;
        int y;
        Crate();
        Crate(int x,int y);
        void move(int x,int y, int **matrix);
        void render();
};
class Player{
    private:
		glm::mat4 position;
	    int x;
        int y;
        int direction;
        float target_x;
        float target_y;
    public:
    bool lock;

    Player();
	Player(int x, int y);
	void render();
	void move_forward(int **matrix,std::vector<Crate> &crate);
	void rotate_left();
	void rotate_right();
};

#endif 
