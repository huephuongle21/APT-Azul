#ifndef AIMANAGER_H
#define AIMANAGER_H

#include "Types.h"
#include "AiTurn.h"
#include "Table.h"
#include "Types.h"
#include "Vector.h"
#include <array>
#include "CurrentGameState.h"

class AiManager {

public:

    AiManager();

    ~AiManager();

    void generatePossibleTurn();

    void updateByTurnFromFactory(Vector* center, int& factoryChoice, char& colourChoice);

    void updateByTurnFromCenter(Vector* center);

    void printTurn(); 

    AiTurn* createPotentialTurn(Wall wall);

    void updateGameState(Factory* factory);

    void clearEndOfRound(AbstractBoard* board);

    void updateByAiTurn(int& factoryChoice, int& patternLinesChoice, char& colourChoice, int numTilesTaken);

    void clearVector(std::vector<AiTurn*> vector);

    void updateTurnByWall(Wall wall);

    bool isValidTurn(Tile tile, int patternLinesChoice);

    void updateWall(int row, int col, Tile tile, Wall wall);

private:

    std::vector<AiTurn*> listTurn;

    std::vector<AiTurn*> invalidTurn;

    CurrentGameState* cgs;

};

#endif // AIMANAGER_H