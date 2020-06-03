#ifndef AIMANAGER_H
#define AIMANAGER_H

#include "Table.h"
#include "Heuristic.h"

class AiManager {

public:

    AiManager(int boardId);

    ~AiManager();

    void generatePossibleTurn();

    void updateByTurnFromFactory(Vector* center, int& factoryChoice, char& colourChoice);

    void setCenterTurnAndState(Vector* center, AbstractBoard* board);

//    void printTurn(); 

    std::string getTurn(Wall wall);

    void updateGameState(Factory* factory);

    void clearEndOfRound(AbstractBoard* board, bool isLoadGame);

    void updateByAiTurn(int& factoryChoice, int& patternLinesChoice, char& colourChoice, int numTilesTaken);

    void updateTurnByWall(Wall wall);

    bool isValidTurn(Tile tile, int patternLinesChoice);

    void updateWall(int row, int col, Tile tile);

    void updateForLoadGame(AbstractBoard* board, Factory* factory, Vector* vector);

//    void printInvalidTurn();

    void setTurnByPatternLines(AbstractBoard* board);

    void sortInvalidTurn();

    void createPatternLinesConstraint();

private:

    std::vector<AiTurn*> listTurn;

    std::vector<AiTurn*> invalidTurn;

    CurrentGameState* cgs;

    unsigned int startIndex;

    int boardSize;

    Heuristic* heuristic;

};

#endif // AIMANAGER_H