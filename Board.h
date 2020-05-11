#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include "Tile.h"
#include <array>

#include <string>
#include <iostream>

class Board {
    public:

    Board();

    ~Board();

    Wall& getWall();

    void addFloorLine(TilePtr value);

    void addPatternLines(int row, int col, TilePtr value);

    void addWall(int row, int col, TilePtr value);

    TilePtr** getPatternLines();

    std::array<TilePtr, FLOOR_LINE_SIZE>& getFloorLine();

    int getLength();

    private:

    Wall wall;

    std::array <TilePtr, FLOOR_LINE_SIZE> floorLine;

    int length;

    TilePtr* patternLines[PATTERN_LINES_SIZE];
};

#endif // BOARD_H