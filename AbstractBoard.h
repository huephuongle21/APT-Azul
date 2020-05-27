#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H

#include "Types.h"
#include <string>
#include <array>

class AbstractBoard {
    public:

    AbstractBoard(int boardSize, int boardId);

    virtual ~AbstractBoard();

    void addFloorLine(Tile tile);

    void addPatternLines(int row, int col, Tile value);

    // Add tile to wall when load game from file
    void addWall(int row, int col, Tile value);

    int addWallForColorBoard(int& pos, Tile value);

    Tile** getPatternLines();

    int getFloorLineLength();

    bool findColourInWall(char& colourChoice, int& pos, int wallDim);

    bool findColourInBoard(char& colourChoice, int& pos, int wallDim);

    bool findColourInPatternLines(char& colourChoice, int& pos);

    bool isPatternLinesEmpty(int& pos);

    bool isPatternLinesFilled(int& pos);

    Tile removeFromPatternLines(int& pos);

    // Clear floor line after each round
    void clearFloorLine();

    int getNumberOfRowsCompleted();

    void completeRows(int wallDim);

    Tile* getFloorLine();

    Wall getWall();

    void createWall();

    void deleteWall();

    void createPatternLines();

    void deletePatternLines();

    int getBoardSize();

    int getBoardId();

    int getFloorLineMaxSize();

    bool isWallPositionFilled(int row, int col);

    protected:

    int boardSize;

    int floorLineMaxSize;

    int floorLineLength;

    int numberOfRowsCompleted;

    Wall wall;

    Tile* floorLine;

    Tile** patternLines;

    int boardId;

};

#endif // ABSTRACTBOARD_H