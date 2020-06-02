#include "AiManager.h"
#include "GameManager.h"
#include "Utility.h"

int main(void) {
    AiManager* ai = new AiManager();
    GameManager* gm = new GameManager();

    gm->loadGame("test.txt");
    Table* table = gm->getTable();
    printFactoryToFile(std::cout, table->getFactories());
    std::cout << std::endl;
    printCenterToFile(std::cout, table->getCenter());

    // Generate all possible turns
    ai->generatePossibleTurn();
    ai->printTurn();


    // // Player takes first turn from factory 2
    // int factory = 3;
    // char tile = YELLOW;
    // ai->updateByTurnFromFactory(factory,tile);
    // ai->printTurn();
    // ai->printPossibleTiles();

    // factory = 4;
    // tile = BLACK;
    // ai->updateByTurnFromFactory(factory,tile);
    // ai->printTurn();
    // ai->printPossibleTiles();

    // factory = 5;
    // tile = RED;
    // ai->updateByTurnFromFactory(factory,tile);
    // ai->printTurn();
    // ai->printPossibleTiles();

    // factory = 1;
    // tile = YELLOW;
    // ai->updateByTurnFromFactory(factory,tile);
    // ai->printTurn();
    // ai->printPossibleTiles();

    // factory = 2;
    // tile = DARK_BLUE;
    // ai->updateByTurnFromFactory(factory,tile);
    // ai->printTurn();
    // ai->printPossibleTiles();

    delete gm;
    delete ai;

}