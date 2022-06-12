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


class ViewManaging{
    private:
        glm::mat4 M;
        glm::mat4 V;
        glm::mat4 P;
        float *vertices;
        float *normals;
        float *texCoords;
        int vertexCount;
    public:
        ShaderProgram *sp;
        void setSp(ShaderProgram *sp);
        GLuint readTexture(const char* filename);
        void setAttrib(GLuint tex);
        void spUse();
        void setPAndV(float cameraZoom);
        void setM(glm::mat4 M);
        void setVertices(float *vertices);
};

#endif
