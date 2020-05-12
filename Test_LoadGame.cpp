#include <iostream>

#include "LinkedList.h"
#include "Vector.h"
#include "Types.h"
#include "Player.h"
#include "Utility.h"
#include <fstream>
#include "GameManager.h"

int main(void) {

    GameManager* game = new GameManager();

    LinkedList* bag = game->getTileBag();
    LinkedList* box = game->getBoxLid();

    Factory* factories = game->getFactories();

    Vector* centerOfTable = game->getCenter();
    

    Player* player1 = game->getPlayer(1);


    Player* player2 = game->getPlayer(2);

    int currentID = player1->getID();
    int seedNumber = game->getSeedNumber();

    std::ifstream outFile;
    outFile.open("azul.txt");
    readGame(outFile, bag, box, &currentID, player1, player2, factories, centerOfTable, &seedNumber);
    outFile.close();

    printBoard(std::cout, player1->getBoard()->getWall(), player1->getBoard()->getPatternLines(), player1->getBoard()->getFloorLine(), player1->getBoard()->getLength());
    printBoard(std::cout, player2->getBoard()->getWall(), player2->getBoard()->getPatternLines(), player2->getBoard()->getFloorLine(), player2->getBoard()->getLength());

    player2->getBoard()->addPatternLines(1,0,new Tile(RED));
    player2->getBoard()->addPatternLines(4,2, new Tile(BLACK));
    player2->getBoard()->addPatternLines(4,3, new Tile(LIGHT_BLUE));
    player2->getBoard()->addPatternLines(4,4, new Tile(DARK_BLUE));
    player2->getBoard()->addPatternLines(3,3, new Tile(WHITE));

    player2->getBoard()->addWall(0,1, new Tile(RED));
    player2->getBoard()->addWall(0,2, new Tile(YELLOW));
    player2->getBoard()->addWall(4,0, new Tile(DARK_BLUE));
    player2->getBoard()->addWall(4,1, new Tile(LIGHT_BLUE));
    player2->getBoard()->addWall(4,3, new Tile(BLACK));

    player2->getBoard()->addFloorLine(new Tile(DARK_BLUE));
    player2->getBoard()->addFloorLine(new Tile(LIGHT_BLUE));

    player1->getBoard()->addPatternLines(0,0, new Tile(RED));
    player1->getBoard()->addPatternLines(4,1, new Tile(BLACK));
    player1->getBoard()->addPatternLines(4,2, new Tile(LIGHT_BLUE));
    player1->getBoard()->addPatternLines(4,4, new Tile(DARK_BLUE));
    player1->getBoard()->addPatternLines(2,2, new Tile(WHITE));

    player1->getBoard()->addWall(0,1, new Tile(RED));
    player1->getBoard()->addWall(0,3, new Tile(YELLOW));
    player1->getBoard()->addWall(1,1, new Tile(DARK_BLUE));
    player1->getBoard()->addWall(1,4, new Tile(LIGHT_BLUE));
    player1->getBoard()->addWall(4,4, new Tile(BLACK));

    player1->getBoard()->addFloorLine(new Tile(RED));
    player1->getBoard()->addFloorLine(new Tile(YELLOW));

    centerOfTable->addTile(new Tile(RED));
    centerOfTable->addTile(new Tile(YELLOW));
    centerOfTable->addTile(new Tile(BLACK));

    factories[0][0] = new Tile(RED);
    factories[0][2] = new Tile(DARK_BLUE);
    factories[3][2] = new Tile(LIGHT_BLUE);
    factories[4][2] = new Tile(YELLOW);

    bag->addBack(new Tile(RED));
    bag->addBack(new Tile(BLACK));

    std::ofstream inFile;
    inFile.open("azul.txt");
    printGame(inFile, bag, box, currentID, player1, player2, factories, centerOfTable, seedNumber);
    inFile.close();

    printGame(std::cout, bag, box, currentID, player1, player2, factories, centerOfTable, seedNumber);
    printBoard(std::cout, player1->getBoard()->getWall(), player1->getBoard()->getPatternLines(), player1->getBoard()->getFloorLine(), player1->getBoard()->getLength());
    printBoard(std::cout, player2->getBoard()->getWall(), player2->getBoard()->getPatternLines(), player2->getBoard()->getFloorLine(), player2->getBoard()->getLength());

    delete game;

    return EXIT_SUCCESS;
}