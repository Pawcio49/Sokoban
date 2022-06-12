
#include "3D_models.h"
#include "common_header.h"
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/vector3.h>
Model3D::Model3D(std::string model){
        Assimp::Importer importer;
        const aiScene * scene = importer.ReadFile(model,aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
        aiMesh* mesh = scene->mMeshes[0];
        for(int i=0;i<mesh->mNumVertices; i++){
            aiVector3D vertex = mesh-> mVertices[i];
            this->verts.push_back(glm::vec4(vertex.x,vertex.y,vertex.z,1));

            aiVector3D normal = mesh->mNormals[i];
            this->norms.push_back(glm::vec4(normal.x,normal.y,normal.z,0));

            UINT liczba_zest = mesh->GetNumUVChannels();

            UINT wymiar_wsp_tex=mesh->mNumUVComponents[0];

            aiVector3D texCoord = mesh -> mTextureCoords[0][i];
            this->texCoords.push_back(glm::vec2(texCoord.x,texCoord.y));
        }
        for(int i=0;i<mesh->mNumFaces;i++){
            aiFace& face = mesh->mFaces[i];
            for(int j = 0;j<face.mNumIndices;j++){
                this->indices.push_back(face.mIndices[j]);
            }
        }
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        for(int i=0;i<material->GetTextureCount(aiTextureType_DIFFUSE);i++){
            aiString str;

            material->GetTexture(aiTextureType_DIFFUSE,i,&str);

        }
    }
void Model3D::render(ShaderProgram *sp,GLuint tex){

	glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, this->verts.data());

	glEnableVertexAttribArray(sp->a("normal"));
    glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, this->norms.data());

	glEnableVertexAttribArray(sp->a("texCoord0"));
    glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, this->texCoords.data());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(sp->u("tex"),0);
	// glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT,this->indices.data());
	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0")); 
}
