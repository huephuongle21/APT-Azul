#include "Heuristic.h"

Heuristic::Heuristic(int boardSize) {
    this->boardSize = boardSize;
}

Heuristic::~Heuristic() {

}

void Heuristic::calculateAdjacent(int** adjacent, int rowPos, int colPos) {
    int score = 0;
    int countRow = 0;
    int countCol = 0;
    for(int row = 0; row != boardSize; row++) {
        if(adjacent[row][colPos] != 0) {
            score++;
            countCol++;
        }
    }
    for(int col = 0; col != boardSize; col++) {
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

int Heuristic::calculateMove(CurrentGameState* cgs, Wall wall, int factoryIndex, Tile colour, 
        int patternLinesIndex, int numTilesTaken) {
    
    int* patternLinesState = cgs->getPatternLinesState();
    int** adjacent = cgs->getAdjacent();
    int* floorLine = cgs->getFloorLineState();
    int floorLineMaxSize = cgs->getFloorLineMaxSize();

    int totalScore = 0;
    if(numTilesTaken != 0 && patternLinesIndex != boardSize) {
        int floorLinesPlaces = numTilesTaken - patternLinesState[patternLinesIndex];
        if(floorLinesPlaces > 0) {
            totalScore += subtractScore(floorLine, floorLineMaxSize, floorLinesPlaces);
        }
        totalScore += addScore(adjacent, wall, patternLinesIndex, colour);
    }    
    return totalScore;
}

int Heuristic::addScore(int** adjacent, Wall wall , int row, Tile tile) {
    int col = -1;
    int addScore = 0;
    for(int i = 0; i != boardSize; i++) {
        if(toupper(wall[row][i]) == tile) {
            col = i;
        }
    }
    if(col != -1) {
        calculateAdjacent(adjacent, row,col);
        addScore = adjacent[row][col];
        adjacent[row][col] = 0;
    }
    return addScore;
}

int Heuristic::subtractScore(int* floorLineState, int floorLineLineMaxSize, int numTiles) {
    int subtract = 0;
    int index = floorLineLineMaxSize;
    int tilesPlaced = 0;
    for(int i = 0; i != floorLineLineMaxSize; i++) {
        if(floorLineState[i] != 0) {
            if(i < index) {
                index = i;
            }
        }
    }
    int possiblePosition = (boardSize+1) - index;
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

AiTurn* Heuristic::createPotentialTurn(CurrentGameState* cgs, Wall wall, int startIndex, std::vector<AiTurn*>& listTurn) {
    int mScore = -15;
    AiTurn* mTurn = nullptr;
    for(unsigned int index = startIndex; index != listTurn.size(); index++) {
        AiTurn* turn = listTurn.at(index);
        if(turn->isValid()) {
            int factoryChoice = turn->getFactoryChoice();
            Tile color = turn->getTileChoice();
            int patternLinesChoice = turn->getPatternLinesChoice();
            int numTilesTaken = turn->getNumTilesTaken();
            int score = calculateMove(cgs, wall, factoryChoice-1, color, patternLinesChoice-1, numTilesTaken);
            if(score > mScore) {
                mScore = score;
                mTurn = turn;
            }
        }
        
    }
    return mTurn;
}