#include "CurrentGameState.h"
#include <iostream>

CurrentGameState::CurrentGameState() {
    floorLineState = {-1,-1,-2,-2,-2,-3,-3};
    numEachColor = {0,0,0,0,0};
    numEachColumn = {0,0,0,0,0};
    numEachRow = {0,0,0,0,0};
    resetTable();
    this->otherPlayerPoints = 0;
    for(int i = 0; i != WALL_DIM; i++) {
        for(int j = 0; j != WALL_DIM; j++) {
            adjacent[i][j] = 0;
        }
    }
    patternLinesState = {1,2,3,4,5};  
    floorLineLength = 0;
}

CurrentGameState::~CurrentGameState() {

}

int CurrentGameState::updatePatternLines(int& patternLinesChoice, int numTilesTaken) {
    int availablePlaces = patternLinesState[patternLinesChoice-1];
    if(availablePlaces >= numTilesTaken) {
        patternLinesState[patternLinesChoice-1] = (availablePlaces-numTilesTaken);
    } else {
        patternLinesState[patternLinesChoice-1] = 0;
        int placeToFloor = numTilesTaken-availablePlaces;
        for(int index = floorLineLength; index != (floorLineLength + placeToFloor); index++) {
            if(index < FLOOR_LINE_SIZE) {
                floorLineState[index] = 0;
            }
        }
    }
    return patternLinesState[patternLinesChoice-1];
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
    }
    return index;
}

void CurrentGameState::addTileAfterRound(Tile tile, int& row, int& col) {
    numEachColumn[col] += 1;
    numEachRow[row] += 1;
    numEachColor[getIndex(tile)] += 1;
}

void CurrentGameState::resetBoard(Tile** patternLines) {
    floorLineState = {-1,-1,-2,-2,-2,-3,-3};
    floorLineLength = 0;
    int count = 0;
    for(int i = 0; i != WALL_DIM; i++) {
        for(int j = 0; j != i+1; j++) {
            if(patternLines[i][j] != NO_TILE) {
                count++;
            }
        }
        patternLinesState[i] = i + 1 - count;
        count = 0;
    }
}

void CurrentGameState::resetTable() {
    centerState = {0,0,0,0,0};
    for(int i = 0; i != WALL_DIM; i++) {
        for(int j = 0; j != NUM_PLAYABLE_COLOURS; j++) {
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

std::array<int, NUM_PLAYABLE_COLOURS> CurrentGameState::getCenterState() {
    return centerState;
}

void CurrentGameState::printTableState() {
    std::cout << std::endl;
    for(int i = 0; i != WALL_DIM; i++) {
        for(int j = 0; j != NUM_PLAYABLE_COLOURS; j++) {
            std::cout << factoryState[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n" << std::endl;
    for(int i = 0; i != NUM_PLAYABLE_COLOURS; i++) {
        std::cout << centerState[i] << " ";
    }
    std::cout << "\n" << std::endl;
    for(int i = 0; i != WALL_DIM; i++) {
        std::cout << patternLinesState[i] << " ";
    }
    std::cout << "\n" << std::endl;
}

void CurrentGameState::resetFactory(int& pos, char& colourChoice) {   
    for(int i = 0; i != NUM_PLAYABLE_COLOURS; i++) {
        factoryState[pos-1][i] = 0;
    }
}

void CurrentGameState::updateCenter(Vector* center) {
    centerState = {0,0,0,0,0};
    for(unsigned int i = 0; i != center->size(); i++) {
        Tile tile = center->get(i);
        if(tile != FIRST_PLAYER) {
            centerState[getIndex(tile)] += 1;
        }
    }
}

// Might move to heuristic class
void CurrentGameState::updateAdjacent(int rowPos, int colPos) {
    int score = 0;
    int countRow = 0;
    int countCol = 0;
    for(int row = 0; row != WALL_DIM; row++) {
        if(adjacent[row][colPos] != 0) {
            score++;
            countCol++;
        }
    }
    for(int col = 0; col != WALL_DIM; col++) {
        if(adjacent[rowPos][col] != 0) {
            score++;
            countRow++;
        }
    }
    if(countRow == 1 || countCol == 1) {
        score--;
    }
    adjacent[rowPos][colPos] = score;
}

int CurrentGameState::calculateMove(Wall wall, int factoryIndex, Tile colour, int patternLinesIndex, int numTilesTaken) {
    int totalScore = 0;
    if(numTilesTaken != 0 && patternLinesIndex != 5) {
        int floorLinesPlaces = numTilesTaken - patternLinesState[patternLinesIndex];
        if(floorLinesPlaces > 0) {
            totalScore += subtractScore(floorLinesPlaces);
        }
        totalScore += addScore(wall, patternLinesIndex, colour);
    }    
    return totalScore;
}

int CurrentGameState::addScore(Wall wall , int row, Tile tile) {
    int col = -1;
    int addScore = 0;
    for(int i = 0; i != WALL_DIM; i++) {
        if(toupper(wall[row][i]) == tile) {
            col = i;
        }
    }
    if(col != -1) {
        updateAdjacent(row,col);
        addScore = adjacent[row][col];
        adjacent[row][col] = 0;
    }
    return addScore;
}

int CurrentGameState::subtractScore(int numTiles) {
    int subtract = 0;
    int index = FLOOR_LINE_SIZE;
    int tilesPlaced = 0;
    for(int i = 0; i != FLOOR_LINE_SIZE; i++) {
        if(floorLineState[i] != 0) {
            if(i < index) {
                index = i;
            }
        }
    }
    int possiblePosition = (WALL_DIM+1) - index;
    if(possiblePosition < numTiles) {
        tilesPlaced = possiblePosition;
    } else {
        tilesPlaced = numTiles;
    }
    for(int i = index; i != (index+tilesPlaced); i++) {
        subtract += floorLineState[index];
    }
    return subtract;
}

std::array<std::array<int, NUM_PLAYABLE_COLOURS>, WALL_DIM> CurrentGameState::getFactoryState() {
    return this->factoryState;
}