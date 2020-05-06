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

    int getFloorSize();

    private:

    Wall wall;

    TilePtr* floorLine;

    int floorLineLength;

    TilePtr* patternLines;

};

#endif // BOARD_H