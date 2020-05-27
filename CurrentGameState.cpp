#include "CurrentGameState.h"

CurrentGameState::CurrentGameState() {
    floorLine = {0,0,0,0,0,0,0};
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
}

CurrentGameState::~CurrentGameState() {

}

// Call after each round
void CurrentGameState::updateAiPlayerState(AbstractBoard* board) {

}

// Call after each turn
void CurrentGameState::addFloorLine(int numTiles) {
    int index = 0;
    while(index < numTiles) {
        for(int i = 0; i != FLOOR_LINE_SIZE; i++) {
            if(floorLine[i] == 0) {
                floorLine[i] = 1;
                index++;
            }
        }
    }
}

Tile CurrentGameState::getColourByIndex(int index) {
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

// Call after each moveTilesFromPatternLines
void CurrentGameState::addTileAfterRound(Tile tile, int& row, int& col) {
    numEachColumn[col] += 1;
    numEachRow[row] += 1;

    addTileByColor(numEachColor, tile);
}

void CurrentGameState::updateWall() {

}

void CurrentGameState::addTileByColor(std::array<int, NUM_PLAYABLE_COLOURS>& array, Tile tile) {
    if(tile == RED) {
        array[0] += 1;
    } else if(tile == YELLOW) {
        array[1] += 1;
    } else if(tile == DARK_BLUE) {
        array[2] += 1;
    } else if(tile == LIGHT_BLUE) {
        array[3] += 1;
    } else if(tile == BLACK) {
        array[4] += 1;
    }
}

// Call when end of round, pass in other player's points
void CurrentGameState::updateEachRound(int ptherPlayerPoints) {
    resetTable();
    this->otherPlayerPoints = otherPlayerPoints;
}

void CurrentGameState::resetTable() {
    centerState = {0,0,0,0,0};
    for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j != NUM_PLAYABLE_COLOURS; j++) {
            factoryState[i][j] = 0;
        }
    }
}

// After set up table
void CurrentGameState::updateFactory(Tile* factory, int& pos) {
    for(int i = 0; i != FACTORY_SIZE; i++) {
        Tile tile = factory[i];
        if(tile != NO_TILE) {
            if(tile == RED) {
                factoryState[pos][0] += 1;
            } else if(tile == YELLOW) {
                factoryState[pos][1] += 1;
            } else if(tile == DARK_BLUE) {
                factoryState[pos][2] += 1;
            } else if(tile == LIGHT_BLUE) {
                factoryState[pos][3] += 1;
            } else if(tile == BLACK) {
                factoryState[pos][4] += 1;
            }
        }
    }
}

// After player takes tile from that corresponding factory
void CurrentGameState::resetFactory(int& pos) {
    for(int i = 0; i != NUM_PLAYABLE_COLOURS; i++) {
        factoryState[pos][i] = 0;
    }
}

void CurrentGameState::updateCenter(Vector* center) {
    for(unsigned int i = 0; i != center->size(); i++) {
        Tile tile = center->get(i);
        if(tile != FIRST_PLAYER) {
            addTileByColor(centerState, tile);
        }
    }
}