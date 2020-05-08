
#include "Board.h"
#include <iostream>

Board::Board() {
    floorLineLength = 0;
    for (int i = 0; i != FLOOR_LINE_SIZE; ++i) {
        floorLine[i] = nullptr;
    }
    for(int i = 0; i < WALL_DIM; i++) {
        for(int j = 0; j < WALL_DIM; j++) {
            wall[i][j] = nullptr;
        }
    }

    for(int i= 0; i != PATTERN_LINES_SIZE; i++) {
        patternLines[i] = new TilePtr[i+1];
        for(int j = 0; j != (i+1); j++) {
            patternLines[i][j] = nullptr;
        }
    }

}

Board::~Board() {
    for(int i = 0; i != FLOOR_LINE_SIZE; ++i) {
        if(floorLine[i] != nullptr) {
            delete floorLine[i];
            floorLine[i] = nullptr;
        }
    }

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
        delete patternLines[i];
    }
    
}

Wall& Board::getWall() {
    return wall;
}

TilePtr* Board::getFloor() {
    return floorLine;
}

TilePtr* Board::getPatternLines(int i) {
    return patternLines[i];
}

void Board::setPatternLines(int row, int col, TilePtr value) {
    patternLines[row][col] = value;
}

void Board::setWall(int row, int col, TilePtr value) {
    wall[row][col] = value;
}

void Board::setFloor(int index, TilePtr value) {
    // if floorLineLength > FLOOR_LINE_SIZE => add to Box Lid
    floorLine[index] = value;
    floorLineLength++;
}
