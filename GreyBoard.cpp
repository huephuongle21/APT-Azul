#include "GreyBoard.h"

GreyBoard::GreyBoard() :
    AbstractBoard(WALL_DIM, GREY_BOARD) {        
        for(int i = 0; i < WALL_DIM; i++) {
            for(int j = 0; j < WALL_DIM; j++) {
                wall[i][j] = NO_TILE;
            }
        }
    };


GreyBoard::~GreyBoard() {
    
}
