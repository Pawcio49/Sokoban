//
// Created by joulupukki on 10.05.2021.
//
#ifndef LLC_GAME_FILEHANDLING_H
#define LLC_GAME_FILEHANDLING_H
struct File_data {
    int **matrix;
    int **goals;
    int steps;
    int game_time;
    int correct_file;
};
File_data read_new_map();
File_data read_saved_map();
File_data read_map(FILE *f);
int save_map(File_data fileData);
#endif //LLC_GAME_FILEHANDLING_H
