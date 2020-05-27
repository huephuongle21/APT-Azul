#include "RegularBoard.h"

RegularBoard::RegularBoard() :
    AbstractBoard(WALL_DIM, REGULAR_BOARD) {
        char defaultWall[WALL_DIM][WALL_DIM] = {{W_DARK_BLUE, W_YELLOW, W_RED, W_BLACK, W_LIGHT_BLUE},
            {W_LIGHT_BLUE, W_DARK_BLUE, W_YELLOW, W_RED, W_BLACK},
            {W_BLACK, W_LIGHT_BLUE, W_DARK_BLUE, W_YELLOW, W_RED},
            {W_RED, W_BLACK, W_LIGHT_BLUE, W_DARK_BLUE, W_YELLOW},
            {W_YELLOW, W_RED, W_BLACK, W_LIGHT_BLUE, W_DARK_BLUE}
            };
        for(int i = 0; i < WALL_DIM; i++) {
            for(int j = 0; j < WALL_DIM; j++) {
                wall[i][j] = defaultWall[i][j];
            }
        }
    };

RegularBoard::~RegularBoard() {
   
}
