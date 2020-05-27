#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <string>
#include "AbstractBoard.h"
#include <iostream>
#include "Player.h"
#include "Table.h"

class AiPlayer : public Player {

public:

    AiPlayer();

    void makeMove(Table* table, AbstractBoard* playerBoard);

    void makeFactoryChoice(Factory* factories, Vector* center);

    void makePatternLinesChoice(AbstractBoard* playerBoard);

    void setFactoryChoice(int& factoryChoice);

    void setColourChoice(char& tile);

    void setPatternLinesChoice(int& patternLineChoice);

    void addPossibleTiles(Tile tile);


private:

    int factoryChoice;

    char colourChoice;

    int patternLinesChoice;

    std::array<Tile, NUM_PLAYABLE_COLOURS> tilesMove;

    int tilesMoveLength;

    std::array<int, 6> factoriesMove;

};

#endif // AIPLAYER_H