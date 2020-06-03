#include "Heuristic.h"
#include <limits.h>

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

int Heuristic::calculateMove(int* patternLinesState, int** adjacent, int* floorLineState, int maxSize, 
        Wall wall, int factoryIndex, Tile colour, int patternLinesIndex, int numTilesTaken) {
    
    int totalScore = 0;
    if(numTilesTaken != 0 && patternLinesIndex != boardSize) {
        int floorLinesPlaces = numTilesTaken - patternLinesState[patternLinesIndex];
        if(floorLinesPlaces > 0) {
            totalScore += subtractScore(floorLineState, maxSize, floorLinesPlaces);
        }
        totalScore += addScore(adjacent, wall, patternLinesIndex, colour);
    } else if (patternLinesIndex == boardSize) {
        totalScore += subtractScore(floorLineState, maxSize, numTilesTaken);
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

std::string Heuristic::createPotentialTurn(CurrentGameState* cgs, Wall wall, int startIndex, std::vector<AiTurn*>& listTurn) {
    int mScore = INT_MIN;
    AiTurn* mTurn = nullptr;

    std::vector<AiTurn*> firstPriority = {};
    std::vector<AiTurn*> secondPriority = {};
    std::vector<AiTurn*> thirdPriority = {};

    int* patternLinesState = cgs->getPatternLinesState();
    int* floorLineState = cgs->getFloorLineState();
    int maxSize = cgs->getFloorLineMaxSize();
    int** adjacent = cgs->getAdjacent();

    for(unsigned int index = startIndex; index != listTurn.size(); index++) {
        AiTurn* turn = listTurn.at(index);
        if(turn->isValid()) {

            int factoryChoice = turn->getFactoryChoice();
            Tile color = turn->getTileChoice();
            int patternLinesChoice = turn->getPatternLinesChoice();
            int numTilesTaken = turn->getNumTilesTaken();

            if((patternLinesChoice-1) != boardSize && needFill(patternLinesState, patternLinesChoice-1, numTilesTaken)) {
                AiTurn* copyTurn = new AiTurn(*turn);
                firstPriority.push_back(copyTurn);

            } else if((patternLinesChoice -1) != boardSize && numTilesTaken == patternLinesChoice) {
                AiTurn* copyTurn = new AiTurn(*turn);
                secondPriority.push_back(copyTurn);

            } else if((patternLinesChoice -1) != boardSize && isFullFill(cgs, color, wall, patternLinesChoice-1)){
                AiTurn* copyTurn = new AiTurn(*turn);
                thirdPriority.push_back(copyTurn);

            } else {
                int score = calculateMove(patternLinesState, adjacent, floorLineState, maxSize, 
                    wall, factoryChoice-1, color, patternLinesChoice-1, numTilesTaken);
                if(score > mScore) {
                    mScore = score;
                    mTurn = turn;
                }
            }
        }   
    }
    if(firstPriority.size() != 0) {
        int totalScore = INT_MIN;
        for(unsigned int i = 0; i != firstPriority.size(); i++) {
            AiTurn* turn = firstPriority.at(i);
            int tilesPlaced = turn->getNumTilesTaken() - patternLinesState[turn->getPatternLinesChoice()-1];
            if(tilesPlaced <= 0) {
                mTurn = turn;
            } else {
                int score = subtractScore(floorLineState, maxSize, tilesPlaced);
                if(score > totalScore) {
                    totalScore = score;
                    mTurn = turn;
                }
            }
        }
    } else if(firstPriority.size() == 0 && secondPriority.size() != 0) {
        AiTurn* turn = sortScore(secondPriority, adjacent, wall);
        if(turn != nullptr) {
            mTurn = turn;
        }
    } else if(firstPriority.size() == 0 && secondPriority.size() == 0 && thirdPriority.size() != 0) {
        AiTurn* turn = sortScore(thirdPriority, adjacent, wall);
        if(turn != nullptr) {
            mTurn = turn;
        }
    }

    std::string toReturn = NO_TURN;
    if(mTurn != nullptr) {
        toReturn = mTurn->toString();
    }
    
    clearVector(firstPriority);
    clearVector(secondPriority);
    clearVector(thirdPriority);
    return toReturn;
}

AiTurn* Heuristic::sortScore(std::vector<AiTurn*>& list, int** adjacent, Wall wall) {
    int score = INT_MIN;
    AiTurn* mTurn = nullptr;
    for(unsigned int i = 0; i != list.size(); i++) {
        AiTurn* turn = list.at(i);
        int row = turn->getPatternLinesChoice()-1;
        Tile tile = turn->getTileChoice();
        
        int add = addScore(adjacent, wall, row, tile);
        if(add > score) {
            score = add;
            mTurn = turn;
        }
    }
    return mTurn;
}

void Heuristic::clearVector(std::vector<AiTurn*> vector) {
    if(vector.size() != 0) {
        for(unsigned int i = 0; i != vector.size(); i++) {
            delete vector.at(i);
            vector.at(i) = nullptr;
        }
        vector.clear();
    }
}

bool Heuristic::isFullFill(CurrentGameState* cgs, Tile tile, Wall wall, int patternLinesIndex) {
    int* color = cgs->getNumEachColor();
    int* column = cgs->getNumEachColumn();
    bool fullfill = false;
    if(color[cgs->getIndex(tile)] + 1 == boardSize) {
        fullfill = true;
    } else {
        int col = findCol(wall, patternLinesIndex, tile);
        if(col != -1) {
            if(column[col] + 1 == boardSize) {
                fullfill = true;
            }
        }
    }
    return fullfill;
}

int Heuristic::findCol(Wall wall, int patternLinesIndex, Tile tile) {
    int col = -1;
    for(int i = 0; i != boardSize; i++) {
        if(toupper(wall[patternLinesIndex][i]) == tile) {
            col = i;
        }
    }
    return col;
}

bool Heuristic::needFill(int* patternLinesState, int patternLinesIndex, int numTilesTaken) {
    bool needFill = false;
    int available = patternLinesState[patternLinesIndex];
    if(available != 0 && available < patternLinesIndex+1) {    
        needFill = true;
    }
    return needFill;
}