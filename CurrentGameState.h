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

    void updateAiPlayerState(AbstractBoard* board);

    void addFloorLine(int numTiles);

    Tile getColourByIndex(int index);

    void addTileAfterRound(Tile tile, int& row, int& col);

    void updateEachRound(int otherPlayerPoints);

    void resetTable();

    void updateCenter(Vector* center);

    void updateFactory(Tile* factory, int& pos);

    void addTileByColor(std::array<int, NUM_PLAYABLE_COLOURS>& array, Tile tile);

    void resetFactory(int& pos);

    void updateWall();
    

private:
    std::array<int, FLOOR_LINE_SIZE> floorLine;
    std::array<int, NUM_PLAYABLE_COLOURS> numEachColor;
    std::array<int, WALL_DIM> numEachColumn;
    std::array<int, WALL_DIM> numEachRow;
    std::array<int, NUM_PLAYABLE_COLOURS> centerState;
    int factoryState[NUMBER_OF_FACTORY][NUM_PLAYABLE_COLOURS];
    int otherPlayerPoints;
    int adjacent[WALL_DIM][WALL_DIM];
};

#endif // CURRENTGAMESTATE_H