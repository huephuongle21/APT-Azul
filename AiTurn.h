#ifndef AITURN_H
#define AITURN_H

#include "Types.h"
#include <string>

class AiTurn {

public:

    AiTurn(int factoryChoice, Tile tileChoice, int patternLinesChoice, bool valid);

    ~AiTurn();

    int getFactoryChoice() const;

    Tile getTileChoice() const;

    int getPatternLinesChoice() const;

    std::string toString();

    void setValid(bool valid);

    bool isValid();

private:
    int factoryChoice;

    Tile tileChoice;

    int patternLinesChoice;

    bool valid;
};

#endif // AITURN_H