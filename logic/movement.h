#ifndef OPENGL_GAME_MOVEMENT_H
#define OPENGL_GAME_MOVEMENT_H
struct Hero{
    int i;
    int j;
    int target_place;
};
Hero find_hero(int **matrix);
// int manage_action(sf::Event *event, int **matrix);
int free_place(int **matrix, Hero hero, int step_i, int step_j);
int move_box(int **matrix, Hero hero, int step_i, int step_j, int behind_step_i, int behind_step_j);
int check_win(int **matrix);

#endif //OPENGL_GAME_MOVEMENT_H
