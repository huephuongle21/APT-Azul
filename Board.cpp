
#include "Board.h"
#include <iostream>

Board::Board() {
    floorLine = {};
    length = 0;

    for(int i = 0; i < WALL_DIM; i++) {
        for(int j = 0; j < WALL_DIM; j++) {
            wall[i][j] = NO_TILE;
        }
    }

    for(int i = 0; i != PATTERN_LINES_SIZE; i++) {
        patternLines[i] = new Tile[i+1];
        for(int j = 0; j != (i+1); j++) {
            patternLines[i][j] = NO_TILE;
        }
    }
}

Board::~Board() {
    
    length = 0;

    for(int i = 0; i != PATTERN_LINES_SIZE; i++) {
        delete[] patternLines[i];
    }
    
}

Wall& Board::getWall() {
    return wall;
}

std::array<Tile, FLOOR_LINE_SIZE>& Board::getFloorLine() {
    return floorLine;
}

void Board::addFloorLine(Tile value) {
    floorLine[length] = value;
    length++;
}

int Board::getLength() {
    return length;
}

Tile** Board::getPatternLines() {
    return patternLines;
}

void Board::addPatternLines(int row, int col, Tile value) {
    patternLines[row][col] = value;
}

void Board::addWall(int row, int col, Tile value) {
    wall[row][col] = value;
}
