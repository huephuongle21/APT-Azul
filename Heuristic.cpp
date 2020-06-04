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

int Heuristic::calculateMove(int* patternLinesState, int** adjacent, int* floorLineState, 
        int maxSize, Wall wall, Tile colour, int patternLinesIndex, int numTilesTaken) {
    
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
    int addScore = 0;
    int col = findCol(wall, row, tile);
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
/*  
    INIT three vectors: first, second and third priority
    INIT mTurn
    INIT mScore
    FOR each turn in list of turn
        IF turn's pattern line choice already had tiles and will be filled up by that turn 
            THEN add turn to first priority list
        ELSE IF turn's number of tiles taken is equal to available tiles in an empty pattern line
            THEN add turn to second priority list
        ELSE IF turn can fullfill any vertical line or 5 tiles of one colour
            THEN add turn to third priority list
        ELSE
            CALCULATE the score turn can get 
            IF score > mScore
                mTurn <- turn
                mScore <- score
            ENDIF
        ENDIF
    ENDFOR  
        
    IF first priority list is not empty
        INIT mFirstPriorityScore
        FOR each turn in first priority list
            CALCULATE the score turn can get
            IF score > mFirstPriorityScore
                mTurn <- turn
                mFirstPriorityScore <- score
            ENDIF
        ENDFOR
    ELSE IF first priority is empty and second priority is not empty
        INIT mSecondPriorityScore
        FOR each turn in first priority list
            CALCULATE the score turn can get
            IF score > mSecondPriorityScore
                mTurn <- turn
                mSecondPriorityScore <- score
            ENDIF
        ENDFOR
    ELSE IF first priority is empty and second priority is empty and third priority is not empty
        INIT mThirdPriorityScore
        FOR each turn in first priority list
            CALCULATE the score turn can get
            IF score > mThirdPriorityScore
                mTurn <- turn
                mThirdPriorityScore <- score
            ENDIF
        ENDFOR
    ENDIF

    INIT toReturn
    IF mTurn not null
        toReturn <- string of mTurn
    ENDIF
    CLEAR first priority list
    CLEAR second priority list
    CLEAR third priority list
    RETURN toReturn
*/
std::string Heuristic::createPotentialTurn(CurrentGameState* cgs, Wall wall, int startIndex, 
        std::vector<AiTurn*>& listTurn) {
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

            Tile color = turn->getTileChoice();
            int patternLinesChoice = turn->getPatternLinesChoice();
            int numTilesTaken = turn->getNumTilesTaken();

            if((patternLinesChoice-1) != boardSize 
                    && needFill(patternLinesState, patternLinesChoice-1)) {
                AiTurn* copyTurn = new AiTurn(*turn);
                firstPriority.push_back(copyTurn);

            } else if((patternLinesChoice -1) != boardSize 
                    && numTilesTaken == patternLinesChoice) {
                AiTurn* copyTurn = new AiTurn(*turn);
                secondPriority.push_back(copyTurn);

            } else if((patternLinesChoice -1) != boardSize 
                    && isFullFill(cgs, color, wall, patternLinesChoice-1)){
                AiTurn* copyTurn = new AiTurn(*turn);
                thirdPriority.push_back(copyTurn);

            } else {
                int score = calculateMove(patternLinesState, adjacent, floorLineState, 
                    maxSize, wall, color, patternLinesChoice-1, numTilesTaken);
                if(score > mScore) {
                    mScore = score;
                    mTurn = turn;
                }
            }
        }   
    }
    if(firstPriority.size() != 0) {
        AiTurn* turn = chooseTurnFromFirstPriority(firstPriority, floorLineState, 
            maxSize, patternLinesState);
            if(turn != nullptr) {
                mTurn = turn;
            }
    } else if(firstPriority.size() == 0 && secondPriority.size() != 0) {
        AiTurn* turn = sortScore(secondPriority, adjacent, wall);
        if(turn != nullptr) {
            mTurn = turn;
        }
    } else if(firstPriority.size() == 0 && secondPriority.size() == 0 
            && thirdPriority.size() != 0) {
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

AiTurn* Heuristic::chooseTurnFromFirstPriority(std::vector<AiTurn*>& firstPriority, 
        int* floorLineState, int maxSize, int* patternLinesState) {
    int loseScore = INT_MAX;
    AiTurn* fTurn = nullptr;
    AiTurn* sTurn = nullptr;
    for(unsigned int i = 0; i != firstPriority.size(); i++) {
        AiTurn* turn = firstPriority.at(i);
        int availableTiles = patternLinesState[turn->getPatternLinesChoice()-1];
        int tilesPlaced = turn->getNumTilesTaken() - availableTiles;
        if(tilesPlaced <= 0) {
            fTurn = turn;
        } else {
            int score = subtractScore(floorLineState, maxSize, tilesPlaced);
            if(score < loseScore) {
                loseScore = score;
                sTurn = turn;
            }
        }
    }
    if(fTurn == nullptr) {
        fTurn = sTurn;
    }
    return fTurn;
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

/* 
    This method to check when that tile will be placed in the wall, will it 
    satisfy any vertical line or 5 tiles of 1 colour
*/
bool Heuristic::isFullFill(CurrentGameState* cgs, Tile tile, 
        Wall wall, int patternLinesIndex) {
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

// This method to find which column index where a tile will be placed in the wall
int Heuristic::findCol(Wall wall, int patternLinesIndex, Tile tile) {
    int col = -1;
    for(int i = 0; i != boardSize; i++) {
        if(toupper(wall[patternLinesIndex][i]) == tile) {
            col = i;
        }
    }
    return col;
}

// This method to find if a pattern line is not empty and needs to be filled
bool Heuristic::needFill(int* patternLinesState, int patternLinesIndex) {
    bool needFill = false;
    int available = patternLinesState[patternLinesIndex];
    if(available != 0 && available < patternLinesIndex+1) {    
        needFill = true;
    }
    return needFill;
}