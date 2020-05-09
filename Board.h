#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include "Tile.h"
#include "Array.h"

#include <string>
#include <iostream>

class Board {
    public:

    Board();

    ~Board();

    Wall& getWall();

    Array* getFloor();

    void addPatternLines(int row, int col, TilePtr value);

    void addWall(int row, int col, TilePtr value);

    TilePtr** getPatternLines();

    private:

    Wall wall;

    Array* floorLine;

    TilePtr* patternLines[PATTERN_LINES_SIZE];
};

#endif // BOARD_H