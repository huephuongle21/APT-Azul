
#include "Board.h"
#include <iostream>

Board::Board() {
    floorLine = {};
    length = 0;

    for(int i = 0; i != PATTERN_LINES_SIZE; i++) {
        patternLines[i] = new Tile[i+1];
        for(int j = 0; j != (i+1); j++) {
            patternLines[i][j] = NO_TILE;
        }
    }

    Wall defaultWall = {{W_DARK_BLUE, W_YELLOW, W_RED, W_BLACK, W_LIGHT_BLUE},
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

bool Board::isPatternLinesEmpty(int& pos) {
    bool isEmpty = true;
    for(int i = 0; i != pos; i++) {
        if(patternLines[pos-1][i] != NO_TILE) {
            isEmpty = false;
        }
    }
    return isEmpty;
}

bool Board::findColourInBoard(char& colourChoice, int& pos) {
    bool isFound = false;
    if(findColourInWall(colourChoice, pos)) {
        isFound = true;
    } else if(!findColourInPatternLines(colourChoice, pos)) {
        isFound = true;
    }
    return isFound;
}

bool Board::findColourInWall(char& colourChoice, int& pos) {
    bool isFound = false;
    for(int i = 0; i != WALL_DIM; i++) {
        if(wall[pos-1][i] == colourChoice) {
            isFound = true;
        }
    }
    return isFound;
}

bool Board::findColourInPatternLines(char& colourChoice, int& pos) {
    bool isFound = false;
    if(isPatternLinesEmpty(pos)) {
        isFound = true;
    } else {
        for(int i = 0; i != pos; i++) {
            if(patternLines[pos-1][i] == colourChoice && i != (pos-1)) {
                isFound = true;
            }
        }
    }
    return isFound;
}
