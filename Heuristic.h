#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "AiTurn.h"
#include "CurrentGameState.h"

class Heuristic {
    public:

    Heuristic(int boardSize);

    ~Heuristic();

    void calculateAdjacent(int** adjacent, int row, int col);

    AiTurn* createPotentialTurn(CurrentGameState* cgs, Wall wall, int startIndex, std::vector<AiTurn*>& listTurn);

    int subtractScore(int* floorLineState, int floorLineLineMaxSize, int numTiles);

    int addScore(int** adjacent, Wall wall , int row, Tile tile);

    int calculateMove(CurrentGameState* cgs, Wall wall, int factoryIndex, Tile colour, int patternLinesIndex, int numTilesTaken);

    private:

    int boardSize;

};

#endif // HEURISTIC_H