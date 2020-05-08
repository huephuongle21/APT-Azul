#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include "Tile.h"

#include <string>
#include <iostream>

class Board {
    public:

    Board();

    ~Board();

    Wall& getWall();

    TilePtr* getFloor();

    TilePtr* getPatternLines(int i);

    void setPatternLines(int row, int col, TilePtr value);

    void setWall(int row, int col, TilePtr value);

    void setFloor(int index, TilePtr value);

    private:

    Wall wall;

    TilePtr floorLine[FLOOR_LINE_SIZE];

    int floorLineLength;

    TilePtr* patternLines[5];
    // TilePtr pattern_1[1];
    // TilePtr pattern_2[2];
    // TilePtr pattern_3[3];
    // TilePtr pattern_4[4];
    // TilePtr pattern_5[5];

};

#endif // BOARD_H