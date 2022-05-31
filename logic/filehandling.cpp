//
// Created by joulupukki on 10.05.2021.
//
#include "stdio.h"
#include "filehandling.h"

File_data read_new_map(){
    FILE *f;
    f = fopen("./files/playmap.txt","r");
    return read_map(f);
}

File_data read_saved_map(){
    FILE *f;
    f = fopen("./files/loadmap.txt","r");
    return read_map(f);
}

File_data read_map(FILE *f){
    File_data file_data;
    if(!f){
        file_data.correct_file = 0;
    }
    else {
        file_data.matrix = new int *[12];
        file_data.goals = new int *[12];
        
        for(int i=0;i<12;i++)
            file_data.matrix[i] = new int [12];
        for(int i=0;i<12;i++)
            file_data.goals[i] = new int [12];
        for(int i = 0; i<12; i++){
            fscanf(f, "%d %d %d %d %d %d %d %d %d %d %d %d", &file_data.matrix[i][0], &file_data.matrix[i][1], &file_data.matrix[i][2], &file_data.matrix[i][3], &file_data.matrix[i][4], &file_data.matrix[i][5], &file_data.matrix[i][6], &file_data.matrix[i][7], &file_data.matrix[i][8], &file_data.matrix[i][9], &file_data.matrix[i][10], &file_data.matrix[i][11]);
            }
        for(int i = 0; i<12; i++){
            fscanf(f, "%d %d %d %d %d %d %d %d %d %d %d %d", &file_data.goals[i][0], &file_data.goals[i][1], &file_data.goals[i][2], &file_data.goals[i][3], &file_data.goals[i][4], &file_data.goals[i][5], &file_data.goals[i][6], &file_data.goals[i][7], &file_data.goals[i][8], &file_data.goals[i][9], &file_data.goals[i][10], &file_data.goals[i][11]);
        }
 
        fscanf(f, "%d %d", &file_data.steps, &file_data.game_time);
        file_data.correct_file = 1;
    }
    fclose(f);
    return file_data;
}

int save_map(File_data file_data){
    FILE *f;
    f = fopen("./files/loadmap.txt","w");
    if(!f){
        return 0;
    }
    else {
        for(int i = 0; i<12; i++){
            fprintf(f, "%d %d %d %d %d %d %d %d %d %d %d %d\n", file_data.matrix[i][0], file_data.matrix[i][1], file_data.matrix[i][2], file_data.matrix[i][3], file_data.matrix[i][4], file_data.matrix[i][5], file_data.matrix[i][6], file_data.matrix[i][7], file_data.matrix[i][8], file_data.matrix[i][9], file_data.matrix[i][10], file_data.matrix[i][11]);
        }
        fprintf(f, "%d %d", file_data.steps, file_data.game_time);
    }
    fclose(f);
    return 1;
}
