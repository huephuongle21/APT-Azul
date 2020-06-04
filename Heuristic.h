#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "AiTurn.h"
#include "CurrentGameState.h"

class Heuristic {
    public:

    Heuristic(int boardSize);

    ~Heuristic();

    std::string createPotentialTurn(CurrentGameState* cgs, Wall wall, int startIndex, 
        std::vector<AiTurn*>& listTurn);

    private:

    int boardSize;

    bool needFill(int* patternLinesState, int patternLinesIndex);

    bool isFullFill(CurrentGameState* cgs, Tile tile, Wall wall, int patternLinesIndex);

    void clearVector(std::vector<AiTurn*> vector);
    
    int findCol(Wall wall, int patternLinesIndex, Tile tile);

    AiTurn* sortScore(std::vector<AiTurn*>& list, int** adjacent, Wall wall);

    void calculateAdjacent(int** adjacent, int row, int col);

    int subtractScore(int* floorLineState, int floorLineLineMaxSize, int numTiles);

    int addScore(int** adjacent, Wall wall , int row, Tile tile);

    int calculateMove(int* patternLinesState, int** adjacent, int* floorLineState, int maxSize, 
        Wall wall, Tile colour, int patternLinesIndex, int numTilesTaken);

    AiTurn* chooseTurnFromFirstPriority(std::vector<AiTurn*>& firstPriority, 
        int* floorLineState, int maxSize, int* patternLinesState);
};

#endif // HEURISTIC_H