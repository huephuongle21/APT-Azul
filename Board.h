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

    void addFloorLine(Tile value);

    void addPatternLines(int row, int col, Tile value);

    void addWall(int row, int col, Tile value);

    Tile** getPatternLines();

    std::array<Tile, FLOOR_LINE_SIZE>& getFloorLine();

    int getLength();

    private:

    Wall wall;

    std::array <Tile, FLOOR_LINE_SIZE> floorLine;

    int length;

    Tile* patternLines[PATTERN_LINES_SIZE];
};

#endif // BOARD_H