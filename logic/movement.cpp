#include "movement.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include "../common_header.h"
Player::Player(){
	this->position = glm::mat4(1.0f);
}
Player::Player(ShaderProgram *sp, int x, int y){
    this->viewManaging.setSp(sp);
    this->tex = viewManaging.readTexture("venom.png");
	this->position = glm::mat4(1.0f);
    this->x=x;
    this->y=y;
    this->target_x=0;
    this->target_y=0;
    this->direction=0;
	this->position = glm::translate(this->position,glm::vec3(x*2-MAX_MAP_SIZE+1, y*2-MAX_MAP_SIZE+1,1.f));

	this->position = glm::rotate(this->position,90.f*PI/180.f,glm::vec3(1.f,0.f,0.f));
}
void Player::render(struct CameraAngle cameraAngle,Model3D model){    this->viewManaging.spUse();
    //TODO: skorzystaj z cameraAngle przy zmianie pozycji (tak jak w main_file)
    if(this->target_x!=0.0f){
        if(this->target_x<0){
            this->position = glm::translate(this->position, glm::vec3(-0.2f, 0.0f, 0.0f));
            this->target_x+=0.2f;
        }else{
            this->position = glm::translate(this->position, glm::vec3(0.2f, 0.0f, 0.0f));
            this->target_x-=0.2f;
        }
    }
    if(this->target_x>-0.2f && this->target_x<0.2f){
        this->target_x=0;
    }
    if(this->target_y!=0.0f){
        if(this->target_y<0){
            this->position = glm::translate(this->position, glm::vec3(-0.2f, 0.0f, 0.0f));
            this->target_y+=0.2f;
        }else{
            this->position = glm::translate(this->position, glm::vec3(0.2f, 0.0f, 0.0f));
            this->target_y-=0.2f;
        }
    }
    if(this->target_y>-0.2f && this->target_y<0.2f){
        this->target_y=0;
    }

    //viewManaging.setM(position);
    glm::mat4 M = glm::rotate(position, 90*PI/180, glm::vec3(0.0f,1.0f,0.0f));
    M= glm::scale(M,glm::vec3(0.03f,0.03f,0.03f));
    M = glm::translate(M, glm::vec3(0.0f,0.0f,25.f));
    M = glm::translate(M, glm::vec3(0.0f,1.0f,0.f));
    glUniformMatrix4fv(this->viewManaging.sp->u("M"), 1, false, value_ptr(M));
    // glUniformMatrix4fv(sp->u("M"), 1, false, value_ptr(position));
	// glUniform4f(sp->u("color"), 1, 0.11, 1, 0.8);
	//Models::teapot.drawSolid();
    //viewManaging.setAttrib(tex);
    model.render(this->viewManaging.sp,this->tex);
}
void Player::move_forward(int **matrix,std::vector<Crate> &crate){
    int temp_x=0;
    int temp_y=0;

    int temp_x_crate=0;
    int temp_y_crate=0;
    this->lock=true;
    switch(this->direction){
        case 0:
            temp_x=this->x+1;
            temp_y=this->y;
            temp_x_crate=this->x+2;
            temp_y_crate=this->y;
            
            this->target_x+=2.2f;
            break;
        case 1:
            temp_x=this->x;
            temp_y=this->y-1;
            temp_x_crate=this->x;
            temp_y_crate=this->y-2;
            
            this->target_y+=2.2f;
            break;
        case 2:
            temp_x=this->x-1;
            temp_y=this->y;
            temp_x_crate=this->x-2;
            temp_y_crate=this->y;
            
            this->target_x+=2.2f;
            break;
        case 3:
            temp_x=this->x;
            temp_y=this->y+1;
            temp_x_crate=this->x;
            temp_y_crate=this->y+2;
            
            this->target_y+=2.2f;
            break;
 
    }
        this->lock=false;
    
    if(matrix[temp_x][temp_y]==3){
        this->target_x=0.f;
        this->target_y=0.f;
        return;
    }
    if(matrix[temp_x][temp_y]==2){
        if(matrix[temp_x_crate][temp_y_crate]!=1){
            this->target_x=0.f;
            this->target_y=0.f;   
            return;
        }else{
            for(int i=0;i<crate.size();i++){
                if(crate[i].x==temp_x && crate[i].y==temp_y){
                    crate[i].move(temp_x_crate,temp_y_crate,matrix);
                    break;
                } 
            }
        }
    }
    this->x=temp_x;
    this->y=temp_y;
	
}
void Player::rotate_left(){
    if(this->lock){
        return;
    }
    if(this->direction==0){
        this->direction=3;
    }else{
        this->direction=this->direction-1;
    }
	this->position = glm::rotate(this->position,90.0f*PI/180.0f,glm::vec3(0.0f,1.0f,0.0f));	
}
void Player::rotate_right(){
    if(this->lock){
        return;
    }
	this->direction=(this->direction+1)%4;
    this->position = glm::rotate(this->position,-90.0f*PI/180.0f,glm::vec3(0.0f,1.0f,0.0f));	
}


Crate::Crate(){
	this->position = glm::mat4(1.0f);
}
Crate::Crate(ShaderProgram *sp, int x, int y){
    this->viewManaging.setSp(sp);
    this->tex = viewManaging.readTexture("bricks.png");
    this->x=x;
    this->y=y;
    this->target_x=0;
    this->target_y=0;
	this->position = glm::mat4(1.0f);
	this->position = glm::translate(this->position,glm::vec3(this->x*2-MAX_MAP_SIZE+1, this->y*2-MAX_MAP_SIZE+1,1.f));

}
void Crate::move(int x,int y,int **matrix){
    matrix[this->x][this->y]=1;
    matrix[x][y]=2;
    if(x-this->x>0){
        this->target_x+=2.2f;
    }
    if(x-this->x<0){
        this->target_x+=-2.2f;
    }
    if(y-this->y>0){
        this->target_y+=2.2f;
    }
    if(y-this->y<0){
        this->target_y+=-2.2f;
    }
    this->x=x;
    this->y=y;
    
}
void Crate::render(){
    // sp->use();
    this->viewManaging.spUse();
    if(this->target_x!=0.0f){
        if(this->target_x<0){
            this->position = glm::translate(this->position, glm::vec3(-0.2f, 0.0f, 0.f));
            this->target_x+=0.2f;
        }else{
            this->position = glm::translate(this->position, glm::vec3(0.2f, 0.0f, 0.f));
            this->target_x-=0.2f;
        }
    }
    if(this->target_x>-0.2f && this->target_x<0.2f){
        this->target_x=0;
    }
    if(this->target_y!=0.0f){
        if(this->target_y<0){
            this->position = glm::translate(this->position, glm::vec3(0.0f, -0.2f, 0.0f));
            this->target_y+=0.2f;
        }else{
            this->position = glm::translate(this->position, glm::vec3(0.0f, 0.2f, 0.0f));
            this->target_y-=0.2f;
        }

    }
    if(this->target_y>-0.2f && this->target_y<0.2f){
        this->target_y=0;
    }
	
 //   glm::mat4 temp = glm::translate(this->position,glm::vec3(0.0f,0.0f,1.f));
    glm::mat4 temp = glm::scale(this->position,glm::vec3(0.65f,0.65f,0.65f));
	// glUniformMatrix4fv(sp->u("M"), 1, false, value_ptr(temp));
    viewManaging.setM(temp);
	// glUniform4f(sp->u("color"), 1, 0.11, 1, 0.8);
	viewManaging.setAttrib(tex);
}
