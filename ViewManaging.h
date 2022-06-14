#ifndef OPENGL_GAME_VIEW_MANAGING_H
#define OPENGL_GAME_VIEW_MANAGING_H

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
#include "camera/camera.h"
#include "torus.h"


class ViewManaging{
    private:
        glm::mat4 M;
        glm::mat4 V;
        glm::mat4 P;
    public:
        ShaderProgram *sp;
        void setSp(ShaderProgram *sp);
        GLuint readTexture(const char* filename);
        void setAttrib(GLuint tex);
        void setAttribTorus(GLuint tex);
        void spUse();
        void setPAndV(struct CameraAngle CameraAngle);
        void setM(glm::mat4 M);
};

#endif
