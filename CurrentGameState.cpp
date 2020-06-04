#include "CurrentGameState.h"
#include <iostream>

CurrentGameState::CurrentGameState(int boardSize) {
    this->boardSize = boardSize;

    if(boardSize == A_WALL_DIM) {
        floorLineMaxSize = A_FLOOR_LINE_SIZE;
        floorLineState = new int[A_FLOOR_LINE_SIZE];
    } else if(boardSize == WALL_DIM) {
        floorLineMaxSize = FLOOR_LINE_SIZE;
        floorLineState = new int[FLOOR_LINE_SIZE];
    }
    createDefaultFloorLine();
    for(int i = 0; i != floorLineMaxSize; i++) {
        floorLineState[i] = defaultFloorLine[i];
    }

    numEachColor = new int[boardSize];
    numEachColumn = new int[boardSize];
    numEachRow = new int[boardSize];
    for(int i = 0; i != boardSize; i++) {
        numEachColor[i] = 0;
        numEachColumn[i] = 0;
        numEachRow[i] = 0;
    }
    centerState = new int[boardSize];
    factoryState = new int*[WALL_DIM];
    for(int i = 0; i != WALL_DIM; i++) {
        factoryState[i] = new int[boardSize];
    }

    resetTable(boardSize);

    adjacent = new int*[boardSize];
    for(int i = 0; i != boardSize; i++) {
        adjacent[i] = new int[boardSize];
    }
    for(int i = 0; i != boardSize; i++) {
        for(int j = 0; j != boardSize; j++) {
            adjacent[i][j] = 0;
        }
    }
    patternLinesState = new int[boardSize];
    for(int i = 0; i != boardSize; i++) {
        patternLinesState[i] = (i+1);
    } 
    floorLineLength = 0;
}

void CurrentGameState::createDefaultFloorLine() {
    defaultFloorLine = new int[floorLineMaxSize];
    if(floorLineMaxSize == A_FLOOR_LINE_SIZE) {
        int floorLine[A_FLOOR_LINE_SIZE] = {-1,-1,-2,-2,-2,-3,-3,-4};
        for(int i = 0; i != A_FLOOR_LINE_SIZE; i++) {
            defaultFloorLine[i] = floorLine[i];
        }
    } else if(floorLineMaxSize == FLOOR_LINE_SIZE) {
        int floorLine[FLOOR_LINE_SIZE] = {-1,-1,-2,-2,-2,-3,-3};
        for(int i = 0; i != FLOOR_LINE_SIZE; i++) {
            defaultFloorLine[i] = floorLine[i];
        }
    }
}

CurrentGameState::~CurrentGameState() {
    floorLineMaxSize = 0;
    floorLineLength = 0;
    delete[] defaultFloorLine;
    delete[] floorLineState;
    delete[] numEachRow;
    delete[] numEachColumn;
    delete[] numEachColor;
    delete[] centerState;
    delete[] patternLinesState;
    for(int i = 0; i != boardSize; i++) {
        delete[] adjacent[i];
    }
    delete[] adjacent;
    for(int i = 0; i != WALL_DIM; i++) {
        delete[] factoryState[i];
    }
    delete[] factoryState;
    boardSize = 0;
}

int CurrentGameState::updatePatternLines(int& patternLinesChoice, int numTilesTaken) {
    int toReturn = -1;
    if(patternLinesChoice-1 == boardSize) {
        updateFloorLine(numTilesTaken);
    } else {
        int availablePlaces = patternLinesState[patternLinesChoice-1];
        if(availablePlaces >= numTilesTaken) {
            patternLinesState[patternLinesChoice-1] = (availablePlaces-numTilesTaken);
        } else {
            patternLinesState[patternLinesChoice-1] = 0;
            int placeToFloor = numTilesTaken-availablePlaces;
            updateFloorLine(placeToFloor);
        }
        toReturn = patternLinesState[patternLinesChoice-1];
    }
    return toReturn;
}

void CurrentGameState::updateFloorLine(int placeToFloor) {
    for(int index = floorLineLength; index != (floorLineLength + placeToFloor); index++) {
        if(index < FLOOR_LINE_SIZE) {
            floorLineState[index] = 0;
        }
    }
}

Tile CurrentGameState::getTile(int index) {
    Tile tile = NO_TILE;
    if(index == 0) {
        tile = RED;
    } else if(index == 1) {
        tile = YELLOW;
    } else if(index == 2) {
        tile = DARK_BLUE;
    } else if(index == 3) {
        tile = LIGHT_BLUE;
    } else if(index == 4) {
        tile = BLACK;
    } else if(index == 5) {
        tile = ORANGE;
    }
    return tile;
} 

int CurrentGameState::getIndex(Tile tile) {
    int index = -1;
    if(tile == RED) {
        index = 0;
    } else if(tile == YELLOW) {
        index = 1;
    } else if(tile == DARK_BLUE) {
        index = 2;
    } else if(tile == LIGHT_BLUE) {
        index = 3;
    } else if(tile == BLACK) {
        index = 4;
    } else if(tile == ORANGE) {
        index = 5;
    }
    return index;
}

void CurrentGameState::addTileAfterRound(Tile tile, int& row, int& col) { 
    numEachColumn[col] += 1;
    numEachRow[row] += 1;
    numEachColor[getIndex(tile)] += 1;
}

void CurrentGameState::resetBoard(Tile** patternLines) {
    for(int i = 0; i != floorLineMaxSize; i++) {
        floorLineState[i] = defaultFloorLine[i];
    }
    floorLineLength = 0;
    setPatternLines(patternLines);
}

void CurrentGameState::setFloorLine(Tile* floorLine, int floorLineLength) {
    for(int i = 0; i != floorLineLength; i++) {
        if(floorLine[i] != NO_TILE) {
            floorLineState[i] = 0;
        }
    }
}

void CurrentGameState::setPatternLines(Tile** patternLines) {
    int count = 0;
    for(int i = 0; i != boardSize; i++) {
        for(int j = 0; j != i+1; j++) {
            if(patternLines[i][j] != NO_TILE) {
                count++;
            }
        }
        patternLinesState[i] = i + 1 - count;
        count = 0;
    }
}

void CurrentGameState::resetTable(int boardSize) {
    for(int i = 0; i != boardSize; i++) {
        centerState[i] = 0;
    }
    for(int i = 0; i != WALL_DIM; i++) {
        for(int j = 0; j != boardSize; j++) {
            factoryState[i][j] = 0;
        }
    }
}

void CurrentGameState::updateFactory(Tile* factory, int& pos) {
    for(int i = 0; i != FACTORY_SIZE; i++) {
        Tile tile = factory[i];
        if(tile != NO_TILE) {
            factoryState[pos][getIndex(tile)] += 1;
        }
    }
}

int* CurrentGameState::getCenterState() {
    return centerState;
}

void CurrentGameState::resetFactory(int& pos, char& colourChoice) {   
    for(int i = 0; i != boardSize; i++) {
        factoryState[pos-1][i] = 0;
    }
}

void CurrentGameState::updateCenter(Vector* center) {
    for(int i = 0; i != boardSize; i++) {
        centerState[i] = 0;
    }
    for(unsigned int i = 0; i != center->size(); i++) {
        Tile tile = center->get(i);
        if(tile != FIRST_PLAYER) {
            centerState[getIndex(tile)] += 1;
        }
    }
}

void CurrentGameState::setAdjacent(int row, int col) {
    adjacent[row][col] = 1;
}

int** CurrentGameState::getFactoryState() {
    return this->factoryState;
}

int* CurrentGameState::getPatternLinesState() {
    return patternLinesState;
}

int CurrentGameState::getFloorLineMaxSize() {
    return floorLineMaxSize;
}

int* CurrentGameState::getFloorLineState() {
    return floorLineState;
}

int** CurrentGameState::getAdjacent() {
    return adjacent;
}

int* CurrentGameState::getNumEachColor() {
    return numEachColor;
}

int* CurrentGameState::getNumEachColumn() {
    return numEachColumn;
}