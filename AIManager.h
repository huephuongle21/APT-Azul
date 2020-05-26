#ifndef AIMANAGER_H
#define AIMANAGER_H

#include "Types.h"
#include "Vector.h"
#include "AITurn.h"
#include "Table.h"
#include "Types.h"

class AIManager {

public:

    AIManager();

    ~AIManager();

    void generatePossibleTurn(Table* table);

    void countNumberOfTile(Tile& tile);

    void sortColor();

    Tile* sortFactory(Tile* factory);

    std::vector<AITurn*>& getListOfTurn();

private:
    std::vector<AITurn*> listTurn;

    Vector* remainingColor;

    int numRedTile;
    int numYellowTile;
    int numBlackTile;
    int numLightBlueTile;
    int numDarkBlueTile;

};

#endif // AIMANAGER_H