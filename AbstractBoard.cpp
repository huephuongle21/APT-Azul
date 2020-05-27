
#include "AbstractBoard.h" 
#include <iostream>

AbstractBoard::AbstractBoard(int boardSize, int boardId) {
    floorLineMaxSize = boardSize+2;
    floorLineLength = 0;
    numberOfRowsCompleted = 0;
    this->boardSize = boardSize;
    this->boardId = boardId;
    createPatternLines();
    for(int i = 0; i != boardSize; i++) {
        for(int j = 0; j != (i+1); j++) {
            patternLines[i][j] = NO_TILE;
        }
    }
    createWall();
    floorLine = new Tile[floorLineMaxSize];
}

AbstractBoard::~AbstractBoard() {
    delete[] floorLine;
    floorLineLength = 0;
    numberOfRowsCompleted = 0;
    deletePatternLines();
    deleteWall();
}

void AbstractBoard::createPatternLines() {
    patternLines = new Tile*[boardSize];
    for(int i = 0; i != boardSize; i++) {
        patternLines[i] = new Tile[i+1];
    }
}

void AbstractBoard::deletePatternLines() {
    for(int i = 0; i != boardSize; i++) {
        delete[] patternLines[i];
    }
    delete[] patternLines;
}

void AbstractBoard::createWall() {
    wall = new char*[boardSize];
    for(int i = 0; i != boardSize; i++) {
        wall[i] = new char[boardSize];
    }
}

void AbstractBoard::deleteWall() {
    for (int i = 0; i != boardSize; ++i) {
        delete[] wall[i];
    }
    delete[] wall;
}

void AbstractBoard::addFloorLine(Tile value) {
    floorLine[floorLineLength] = value;
    floorLineLength++;
}

int AbstractBoard::getFloorLineLength() {
    return floorLineLength;
}

Tile** AbstractBoard::getPatternLines() {
    return patternLines;
}

void AbstractBoard::addPatternLines(int row, int col, Tile value) {
    patternLines[row][col] = value;
}

void AbstractBoard::addWall(int row, int col, Tile value) {
    wall[row][col] = value;
}

bool AbstractBoard::isPatternLinesEmpty(int& pos) {
    bool isEmpty = true;
    for(int i = 0; i != pos; i++) {
        if(patternLines[pos-1][i] != NO_TILE) {
            isEmpty = false;
        }
    }
    return isEmpty;
}

bool AbstractBoard::findColourInBoard(char& colourChoice, int& pos, int wallDim) {
    bool isFound = false;
    if(findColourInWall(colourChoice, pos, wallDim)) {
        isFound = true;
    } else if(!findColourInPatternLines(colourChoice, pos)) {
        isFound = true;
    }
    return isFound;
}

bool AbstractBoard::findColourInWall(char& colourChoice, int& pos, int wallDim) {
    bool isFound = false;
    for(int i = 0; i != wallDim; i++) {
        if(wall[pos-1][i] == colourChoice) {
            isFound = true;
        }
    }
    return isFound;
}

bool AbstractBoard::findColourInPatternLines(char& colourChoice, int& pos) {
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

bool AbstractBoard::isPatternLinesFilled(int& pos) {
    bool isFilled = true;
    for(int i = 0; i != (pos+1); i++) {
        if(patternLines[pos][i] == NO_TILE) {
            isFilled = false;
        }
    }
    return isFilled;
}

Tile AbstractBoard::removeFromPatternLines(int& pos) {
    Tile tile = patternLines[pos][0];
    for(int i = 0; i != (pos+1); i++) {
        patternLines[pos][i] = NO_TILE;
    }
    return tile;
}

void AbstractBoard::clearFloorLine() {
    for(int i = 0; i != floorLineLength; i++) {
        floorLine[i] = NO_TILE;
    }
    floorLineLength = 0;
}

int AbstractBoard::getNumberOfRowsCompleted() {
    return numberOfRowsCompleted;
}

void AbstractBoard::completeRows(int wallDim) {
    bool rowFilled = true;
    for(int row = 0; row != wallDim; row++) {
        for(int col = 0; col != wallDim; col++) {
            Tile tile = wall[row][col];
            if((tile >= 'a' && tile <= 'z') || tile == NO_TILE) {
                rowFilled = false;
            }
        }
        if(rowFilled) {
            numberOfRowsCompleted++;
        }
        rowFilled = true;
    }
}

int AbstractBoard::getBoardSize() {
    return this->boardSize;
}

int AbstractBoard::addWallForColorBoard(int& pos, Tile value) {
    int colPos = 0;
    for(int i = 0; i != boardSize; i++) {
        if(wall[pos][i] == tolower(value)) {
            wall[pos][i] = value;
            colPos = i;
        }
    }
    return colPos;
}

Tile* AbstractBoard::getFloorLine() {
    return floorLine;
}

Wall AbstractBoard::getWall() {
    return wall;
}

int AbstractBoard::getBoardId() {
    return this->boardId;
}

int AbstractBoard::getFloorLineMaxSize() {
    return floorLineMaxSize;
}

bool AbstractBoard::isWallPositionFilled(int row, int col) {
    bool isFilled = true;
    if(wall[row][col] == NO_TILE) {
        isFilled = false;
    }
    return isFilled;
}
