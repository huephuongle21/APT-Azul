
#include "Board.h"
#include <iostream>

Board::Board() {
    floorLine = new Array(FLOOR_LINE_SIZE);

    for(int i = 0; i < WALL_DIM; i++) {
        for(int j = 0; j < WALL_DIM; j++) {
            wall[i][j] = nullptr;
        }
    }

    for(int i = 0; i != PATTERN_LINES_SIZE; i++) {
        patternLines[i] = new TilePtr[i+1];
        for(int j = 0; j != (i+1); j++) {
            patternLines[i][j] = nullptr;
        }
    }
}

Board::~Board() {
    
    delete floorLine;

    for(int i = 0; i < WALL_DIM; i++) {
        for(int j = 0; j < WALL_DIM; j++) {
            if(wall[i][j] != nullptr) {
                delete wall[i][j];
                wall[i][j] = nullptr;
            }
        }
    }

    for(int i = 0; i != PATTERN_LINES_SIZE; i++) {
        for(int j = 0; j != (i+1); j++) {
            if(patternLines[i][j] != nullptr) {
                delete patternLines[i][j];
                patternLines[i][j] = nullptr;
            }
        }
        delete[] patternLines[i];
    }
    
}

Wall& Board::getWall() {
    return wall;
}

Array* Board::getFloor() {
    return floorLine;
}

TilePtr** Board::getPatternLines() {
    return patternLines;
}

void Board::addPatternLines(int row, int col, TilePtr value) {
    patternLines[row][col] = value;
}

void Board::addWall(int row, int col, TilePtr value) {
    wall[row][col] = value;
}
