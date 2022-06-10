#ifndef OPENGL_GAME_FILEHANDLING_H
#define OPENGL_GAME_FILEHANDLING_H
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
#endif //OPENGL_GAME_FILEHANDLING_H
