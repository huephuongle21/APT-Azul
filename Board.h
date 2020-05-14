#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include <array>

#include <string>
#include <iostream>

class Board {
    public:

    Board();

    ~Board();

    Wall& getWall();

    void addFloorLine(char value);

    void addPatternLines(int row, int col, char value);

    void addWall(int row, int col, char value);

    char** getPatternLines();

    std::array<char, FLOOR_LINE_SIZE>& getFloorLine();

    int getLength();

    private:

    Wall wall;

    std::array <char, FLOOR_LINE_SIZE> floorLine;

    int length;

    char* patternLines[PATTERN_LINES_SIZE];
};

#endif // BOARD_H