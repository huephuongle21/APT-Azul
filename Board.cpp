
#include "Board.h"
#include <iostream>

Board::Board() {
    floorLine = {};
    floorLineLength = 0;

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

    numberOfRowsCompleted = 0;
}

Board::~Board() {
    
    clearFloorLine();

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
    floorLine[floorLineLength] = value;
    floorLineLength++;
}

unsigned int Board::getFloorLineLength() {
    return floorLineLength;
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
        int count = 0;
        for(int i = 0; i != pos; i++) {
            if(patternLines[pos-1][i] == colourChoice) {
                count++;
            }
        }
        if(count == pos) {
            isFound = false;
        } else if(count < pos && count > 0) {
            isFound = true;
        }
    }
    return isFound;
}

bool Board::isPatternLinesFilled(int& pos) {
    bool isFilled = true;
    for(int i = 0; i != (pos+1); i++) {
        if(patternLines[pos][i] == NO_TILE) {
            isFilled = false;
        }
    }
    return isFilled;
}

Tile Board::removeFromPatternLines(int& pos) {
    Tile tile = patternLines[pos][0];
    for(int i = 0; i != (pos+1); i++) {
        patternLines[pos][i] = NO_TILE;
    }
    return tile;
}

int Board::addWall(int& pos, Tile value) {
    int colPos = 0;
    for(int i = 0; i != WALL_DIM; i++) {
        if(wall[pos][i] == tolower(value)) {
            wall[pos][i] = value;
            colPos = i;
        }
    }
    return colPos;
}

void Board::clearFloorLine() {
    std::fill(floorLine.begin(), floorLine.end(), 0);
    floorLineLength = 0;
}

void Board::completeRows() {
    bool rowFilled = true;
    for(int row = 0; row != WALL_DIM; row++) {
        for(int col = 0; col != WALL_DIM; col++) {
            Tile tile = wall[row][col];
            if(tile >= 'a' && tile <= 'z') {
                rowFilled = false;
            }
        }
        if(rowFilled) {
            numberOfRowsCompleted++;
        }
        rowFilled = true;
    }
}

unsigned int Board::getNumberOfRowsCompleted() {
    return numberOfRowsCompleted;
}
