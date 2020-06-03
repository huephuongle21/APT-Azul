#ifndef CURRENTGAMESTATE_H
#define CURRENTGAMESTATE_H

#include "Types.h"
#include "AbstractBoard.h"
#include "Vector.h"

class CurrentGameState {

public:
    CurrentGameState(int boardSize);

    ~CurrentGameState();

    Tile getTile(int index);

    void addTileAfterRound(Tile tile, int& row, int& col);

    void resetTable(int boardSize);

    void resetBoard(Tile** patternLines);

    void updateCenter(Vector* center);

    void updateFactory(Tile* factory, int& pos);

    void setPatternLines(Tile** patternLines);

    int updatePatternLines(int& patternLinesChoice, int numTilesTaken);

    void resetFactory(int& pos, char& colourChoice);

    int getIndex(Tile tile);

//    void printTableState();

    void setFloorLine(Tile* floorLine, int floorLineLength);

    int** getFactoryState();

    int* getCenterState();

    int* getPatternLinesState();

    void setAdjacent(int row, int col);

    void createDefaultFloorLine();

    int getFloorLineMaxSize();

    int* getFloorLineState();

    int** getAdjacent();

    int* getNumEachColor();

    int* getNumEachColumn();

    void updateFloorLine(int placeToFloor);

private:
    int* floorLineState;
    int* numEachColor;
    int* numEachColumn;
    int* numEachRow;
    int* centerState;
    int** factoryState;
    int** adjacent;
    int* patternLinesState;
    int floorLineLength;
    int boardSize;
    int floorLineMaxSize;
    int* defaultFloorLine;
};

#endif // CURRENTGAMESTATE_H