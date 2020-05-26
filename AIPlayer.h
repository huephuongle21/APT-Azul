#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <string>
#include "Board.h"
#include <iostream>
#include "Player.h"
#include "Table.h"

class AIPlayer : public Player {

public:

    AIPlayer();

    void makeMove(Table* table, Board* playerBoard);

    void makeFactoryChoice(Factory* factories, Vector* center);

    void makePatternLinesChoice(Board* playerBoard);

    void setFactoryChoice(int& factoryChoice);

    void setColourChoice(char& tile);

    void setPatternLinesChoice(int& patternLineChoice);

    void addPossibleTiles(Tile tile);


private:

    int factoryChoice;

    char colourChoice;

    int patternLinesChoice;

    std::array<Tile, NUM_PLAYABLE_COLOURS> tilesMove;

    unsigned int tilesMoveLength;

    std::array<int, 6> factoriesMove;

};

#endif // AIPLAYER_H