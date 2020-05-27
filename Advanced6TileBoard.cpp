#include "Advanced6TileBoard.h"

Advanced6TileBoard::Advanced6TileBoard() :
    AbstractBoard(A_WALL_DIM, ADVANCED_6TILE_BOARD) {
        char defaultWall[A_WALL_DIM][A_WALL_DIM] = {
            {W_DARK_BLUE, W_YELLOW, W_RED, W_BLACK, W_LIGHT_BLUE, W_ORANGE},
            {W_ORANGE, W_DARK_BLUE, W_YELLOW, W_RED, W_BLACK, W_LIGHT_BLUE},
            {W_LIGHT_BLUE, W_ORANGE, W_DARK_BLUE, W_YELLOW, W_RED, W_BLACK},
            {W_BLACK, W_LIGHT_BLUE, W_ORANGE, W_DARK_BLUE, W_YELLOW, W_RED},
            {W_RED, W_BLACK, W_LIGHT_BLUE, W_ORANGE, W_DARK_BLUE, W_YELLOW},
            {W_YELLOW, W_RED, W_BLACK, W_LIGHT_BLUE, W_ORANGE, W_DARK_BLUE}
            };

    for(int i = 0; i < A_WALL_DIM; i++) {
        for(int j = 0; j < A_WALL_DIM; j++) {
            wall[i][j] = defaultWall[i][j];
        }
    }
    };

Advanced6TileBoard::~Advanced6TileBoard() {
 
}
