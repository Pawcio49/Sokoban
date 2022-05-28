//
// Created by joulupukki on 10.05.2021.
//

#include "movement.h"

Hero find_hero(int **matrix){
    Hero hero;
    for(int i=0; i<12; i++){
        for(int j=0; j<12; j++){
            if(matrix[i][j] == 4){
                hero.i = i;
                hero.j = j;
                hero.target_place = 0;
            } else if(matrix[i][j] == 5) {
                hero.i = i;
                hero.j = j;
                hero.target_place = 1;
            }
        }
    }
    return hero;
}

// int manage_action(sf::Event *event, int **matrix) {
//     int step_i, step_j, behind_step_i, behind_step_j;
//     Hero hero = find_hero(matrix);
//     switch (event->key.code) {
//         case sf::Keyboard::Left:
//             step_i = hero.i;
//             step_j = hero.j - 1;
//             behind_step_i = hero.i;
//             behind_step_j = hero.j - 2;
//             break;
//         case sf::Keyboard::Right:
//             step_i = hero.i;
//             step_j = hero.j + 1;
//             behind_step_i = hero.i;
//             behind_step_j = hero.j + 2;
//             break;
//         case sf::Keyboard::Up:
//             step_i = hero.i - 1;
//             step_j = hero.j;
//             behind_step_i = hero.i - 2;
//             behind_step_j = hero.j;
//             break;
//         case sf::Keyboard::Down:
//             step_i = hero.i + 1;
//             step_j = hero.j;
//             behind_step_i = hero.i + 2;
//             behind_step_j = hero.j;
//             break;
//     }

//     if(free_place(matrix, hero, step_i, step_j) == 0){
//         if(move_box(matrix, hero, step_i, step_j, behind_step_i, behind_step_j) == 1){
//             if(check_win(matrix) == 1){
//                 return 1;
//             }
//         }
//     }
//     return 0;
// }

int free_place(int **matrix, Hero hero, int step_i, int step_j){
    if(matrix[step_i][step_j] == 1) {
        matrix[step_i][step_j] = 4;
        if(hero.target_place == 0){
            matrix[hero.i][hero.j] = 1;
        } else {
            matrix[hero.i][hero.j] = 2;
        }
        return 1;
    } else if(matrix[step_i][step_j] == 2) {
        matrix[step_i][step_j] = 5;
        if(hero.target_place == 0){
            matrix[hero.i][hero.j] = 1;
        } else {
            matrix[hero.i][hero.j] = 2;
        }
        return 1;
    } else {
        return 0;
    }
}

int move_box(int **matrix, Hero hero, int step_i, int step_j, int behind_step_i, int behind_step_j){
    if(matrix[step_i][step_j] == 6 && matrix[behind_step_i][behind_step_j] == 1){
        matrix[behind_step_i][behind_step_j] = 6;
        matrix[step_i][step_j] = 4;
        if(hero.target_place == 0){
            matrix[hero.i][hero.j] = 1;
        } else {
            matrix[hero.i][hero.j] = 2;
        }
        return 1;
    } else if(matrix[step_i][step_j] == 6 && matrix[behind_step_i][behind_step_j] == 2) {
        matrix[behind_step_i][behind_step_j] = 7;
        matrix[step_i][step_j] = 4;
        if(hero.target_place == 0){
            matrix[hero.i][hero.j] = 1;
        } else {
            matrix[hero.i][hero.j] = 2;
        }
        return 1;
    } else if(matrix[step_i][step_j] == 7 && matrix[behind_step_i][behind_step_j] == 1) {
        matrix[behind_step_i][behind_step_j] = 6;
        matrix[step_i][step_j] = 5;
        if(hero.target_place == 0){
            matrix[hero.i][hero.j] = 1;
        } else {
            matrix[hero.i][hero.j] = 2;
        }
        return 1;
    }  else if(matrix[step_i][step_j] == 7 && matrix[behind_step_i][behind_step_j] == 2) {
        matrix[behind_step_i][behind_step_j] = 7;
        matrix[step_i][step_j] = 5;
        if(hero.target_place == 0){
            matrix[hero.i][hero.j] = 1;
        } else {
            matrix[hero.i][hero.j] = 2;
        }
        return 1;
    } else {
        return 0;
    }
}

int check_win(int **matrix){
    for(int i=0; i<12; i++){
        for(int j=0; j<12; j++){
            if(matrix[i][j] == 2){
                return 0;
            }
        }
    }
    return 1;
}