#include "common_header.h"

#ifndef THREEDMODELS
#define THREEDMODELS
class Model3D{
    std::vector<glm::vec4> verts;
    std::vector<glm::vec4> norms;
    std::vector<glm::vec2> texCoords;
    std::vector<UINT> indices;
    public:
    Model3D(std::string model);
    void render(ShaderProgram *sp,GLuint tex ); 

};
#endif

