#ifndef AITURN_H
#define AITURN_H

#include "Types.h"
#include <string>

class AiTurn {

public:

    AiTurn(int factoryChoice, Tile tileChoice, 
        int patternLinesChoice, bool valid, int numTileTaken);

    AiTurn(Tile tileChoice, int patternLinesChoice);

    AiTurn(AiTurn& other);

    ~AiTurn();

    int getFactoryChoice() const;

    Tile getTileChoice() const;

    int getPatternLinesChoice() const;

    std::string toString();

    void setValid(bool valid);

    bool isValid();

    void setNumTilesTaken(int num);

    int getNumTilesTaken();

    bool isPatternLinesValid();

    void setPatternLines(bool valid);

private:
    int factoryChoice;

    Tile tileChoice;

    int patternLinesChoice;

    bool valid;

    int numTilesTaken;

    bool validPatternLines;
};

#endif // AITURN_H