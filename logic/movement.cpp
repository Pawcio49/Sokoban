#include "movement.h"
#include <glm/ext/matrix_transform.hpp>

Player::Player(){
	this->position = glm::mat4(1.0f);	
}
Player::Player(int x, int y){
	this->position = glm::mat4(1.0f);
    this->x=x;
    this->y=y;
    this->target_x=0;
    this->target_y=0;
    this->direction=0;
	this->position = glm::translate(this->position,glm::vec3(x*2-MAX_MAP_SIZE+1, y*2-MAX_MAP_SIZE+1,1.f));

	this->position = glm::rotate(this->position,90.f*PI/180.f,glm::vec3(1.f,0.f,0.f));
}
void Player::render(){
	spLambert->use();
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

    glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(position));
	glUniform4f(spLambert->u("color"), 1, 0.11, 1, 0.8);
	Models::teapot.drawSolid();	
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
Crate::Crate(int x, int y){
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
    spLambert->use();
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
	glUniformMatrix4fv(spLambert->u("M"), 1, false, value_ptr(temp));
	glUniform4f(spLambert->u("color"), 1, 0.11, 1, 0.8);
	Models::cube.drawSolid();	
}
