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

    // Add tile to wall when load game from file
    void addWall(int row, int col, Tile value);

    // Add tile to wall during the game
    int addWall(int& pos, Tile value);

    Tile** getPatternLines();

    std::array<Tile, FLOOR_LINE_SIZE>& getFloorLine();

    int getLength();

    bool findColourInWall(char& colourChoice, int& pos);

    bool findColourInBoard(char& colourChoice, int& pos);

    // True if patternLine is empty OR patternLine is not full and has that colourChoice
    bool findColourInPatternLines(char& colourChoice, int& pos);

    bool isPatternLinesEmpty(int& pos);

    bool isPatternLinesFilled(int& pos);

    bool hasPatternLineColour(int& pos);

    Tile removeFromPatternLines(int& pos);

    // Check for any rows completed and set number of rows completed
    void completeRows();

    // Clear floor line after each round
    void clearFloorLine();

    unsigned int getNumberOfRowsCompleted();

    private:

    Wall wall;

    std::array <Tile, FLOOR_LINE_SIZE> floorLine;

    int floorLineLength;

    Tile* patternLines[PATTERN_LINES_SIZE];

    unsigned int numberOfRowsCompleted;

};

#endif // BOARD_H