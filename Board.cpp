
#include "Board.h"
#include <iostream>

Board::Board() {
    floorLineLength = 0;
    floorLine = new TilePtr[FLOOR_LINE_SIZE];
    for (int i = 0; i != FLOOR_LINE_SIZE; ++i) {
        floorLine[i] = nullptr;
    }
    for(int i = 0; i < WALL_DIM; i++) {
        for(int j = 0; j < WALL_DIM; j++) {
            wall[i][j] = nullptr;
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
    delete[] floorLine;

    for(int i = 0; i < WALL_DIM; i++) {
        for(int j = 0; j < WALL_DIM; j++) {
            if(wall[i][j] != nullptr) {
                delete wall[i][j];
                wall[i][j] = nullptr;
            }
        }
    }
}

Wall& Board::getWall() {
    return wall;
}

TilePtr* Board::getFloor() {
    return floorLine;
}

int Board::getFloorSize() {
    return floorLineLength;
}
