#ifndef CURRENTGAMESTATE_H
#define CURRENTGAMESTATE_H

#include "Types.h"
#include "AbstractBoard.h"
#include "Vector.h"
#include <array>

class CurrentGameState {

public:
    CurrentGameState();

    ~CurrentGameState();

    Tile getTile(int index);

    void addTileAfterRound(Tile tile, int& row, int& col);

    void resetTable();

    void resetBoard(Tile** patternLines);

    void updateCenter(Vector* center);

    void updateFactory(Tile* factory, int& pos);

    int updatePatternLines(int& patternLinesChoice, int numTilesTaken);

    void resetFactory(int& pos, char& colourChoice);

    void updateAdjacent(int row, int col);

    int getIndex(Tile tile);

    int calculateMove(Wall wall, int factoryIndex, Tile colour, int patternLinesIndex, int numTilesTaken);

    int subtractScore(int nTiles);

    int addScore(Wall wall, int row, Tile tile);

    void printTableState();

    std::array<std::array<int, NUM_PLAYABLE_COLOURS>, WALL_DIM> getFactoryState();

    std::array<int, NUM_PLAYABLE_COLOURS> getCenterState();

private:
    std::array<int, FLOOR_LINE_SIZE> floorLineState;
    std::array<int, NUM_PLAYABLE_COLOURS> numEachColor;
    std::array<int, WALL_DIM> numEachColumn;
    std::array<int, WALL_DIM> numEachRow;
    std::array<int, NUM_PLAYABLE_COLOURS> centerState;
    std::array<std::array<int, NUM_PLAYABLE_COLOURS>, WALL_DIM> factoryState;
    int otherPlayerPoints;
    int adjacent[WALL_DIM][WALL_DIM];
    std::array<int, WALL_DIM> patternLinesState;
    int floorLineLength;
};

#endif // CURRENTGAMESTATE_H