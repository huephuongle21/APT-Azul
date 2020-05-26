#ifndef AITURN_H
#define AITURN_H

#include "Types.h"
#include <string>

class AITurn {

public:

    AITurn(int factoryChoice, Tile tileChoice, int patternLinesChoice);

    ~AITurn();

    int getFactoryChoice() const;

    Tile getTileChoice() const;

    int getPatternLinesChoice() const;

    std::string toString();

private:
    int factoryChoice;

    Tile tileChoice;

    int patternLinesChoice;
};

#endif // AITURN_H