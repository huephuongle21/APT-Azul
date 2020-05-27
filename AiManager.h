#ifndef AIMANAGER_H
#define AIMANAGER_H

#include "Types.h"
#include "AiTurn.h"
#include "Table.h"
#include "Types.h"
#include "TileList.h"
#include "Vector.h"
#include <array>

class AiManager {

public:

    AiManager();

    ~AiManager();

    void generatePossibleTurn(Table* table); //Tested

    void sortColor(); //Tested

    void updateByTurnFromFactory(int& factoryChoice, char& colourChoice); //Tested

    void updateTurnByColour(Tile colour); //Tested

    void updateByTurnFromCenter(char& colourChoice, Table* table, int numTilesTaken);

    int getIndexByColour(Tile colour); //Tested

    void printPossibleTiles(); //Tested

    void printTurn(); //Tested

private:

    std::vector<AiTurn*> listTurn;

    std::array<TileList*, NUM_PLAYABLE_COLOURS> listColour;

    int listColourLength;

};

#endif // AIMANAGER_H