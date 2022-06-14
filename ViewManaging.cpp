#include "ViewManaging.h"
#include "myCube.h"

void ViewManaging::setSp(ShaderProgram *sp){
	this->sp = sp;
}

GLuint ViewManaging::readTexture(const char* filename) { //Deklaracja globalna
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image; //Alokuj wektor do wczytania obrazka
	unsigned width, height; //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);
	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return tex;
}

void ViewManaging::setAttrib(GLuint tex){
	glUniform1i(sp->u("textureMap0"), 0);

	glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myCubeVertices);

	glEnableVertexAttribArray(sp->a("normal"));
    glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, myCubeNormals);

	glEnableVertexAttribArray(sp->a("texCoord0"));
    glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myCubeTexCoords);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

    glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);
	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));
}

void ViewManaging::setAttribTorus(GLuint tex){
	Models::Torus torus;

	glUniform1i(sp->u("textureMap0"), 0);

	glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, torus.vertices);

	glEnableVertexAttribArray(sp->a("normal"));
    glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, torus.normals);

	glEnableVertexAttribArray(sp->a("texCoord0"));
    glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, torus.texCoords);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

    glDrawArrays(GL_TRIANGLES, 0, torus.vertexCount);
	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));
}

void ViewManaging::spUse(){
    sp->use();
}

void ViewManaging::setPAndV(struct CameraAngle cameraAngle){
    V = glm::lookAt(glm::vec3(cameraAngle.horizontal, cameraAngle.vertical, cameraAngle.zoom), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	P = glm::perspective(50.0f * PI / 180.0f, 1.0f, 1.0f, 5000.0f);

	glUniformMatrix4fv(sp->u("P"), 1, false, value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, value_ptr(V));
}

void ViewManaging::setM(glm::mat4 M){
    glUniformMatrix4fv(sp->u("M"), 1, false, value_ptr(M));
}