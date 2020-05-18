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

    LinkedList* bag = game->getTable()->getTileBag();
    LinkedList* box = game->getTable()->getBoxLid();

    Factory* factories = game->getTable()->getFactories();

    Vector* centerOfTable = game->getTable()->getCenter();
    

    Player* player1 = game->getPlayer(1);


    Player* player2 = game->getPlayer(2);

    int currentID = player1->getID();
    int seedNumber = game->getTable()->getSeedNumber();

    std::ifstream outFile;
    outFile.open("azul.txt");
    readGame(outFile, game->getTable(), &currentID, player1, player2);
    outFile.close();

    printBoard(std::cout, player1->getBoard()->getWall(), player1->getBoard()->getPatternLines(), player1->getBoard()->getFloorLine(), player1->getBoard()->getLength());
    printBoard(std::cout, player2->getBoard()->getWall(), player2->getBoard()->getPatternLines(), player2->getBoard()->getFloorLine(), player2->getBoard()->getLength());

    player2->getBoard()->addPatternLines(1,0,RED);
    player2->getBoard()->addPatternLines(4,2, BLACK);
    player2->getBoard()->addPatternLines(4,3, LIGHT_BLUE);
    player2->getBoard()->addPatternLines(4,4, DARK_BLUE);
    player2->getBoard()->addPatternLines(3,3, FIRST_PLAYER);

    player2->getBoard()->addWall(0,1, RED);
    player2->getBoard()->addWall(0,2, YELLOW);
    player2->getBoard()->addWall(4,0, DARK_BLUE);
    player2->getBoard()->addWall(4,1, LIGHT_BLUE);
    player2->getBoard()->addWall(4,3, BLACK);

    player2->getBoard()->addFloorLine(DARK_BLUE);
    player2->getBoard()->addFloorLine(LIGHT_BLUE);

    player1->getBoard()->addPatternLines(0,0,RED);
    player1->getBoard()->addPatternLines(4,1, BLACK);
    player1->getBoard()->addPatternLines(4,2, LIGHT_BLUE);
    player1->getBoard()->addPatternLines(4,4, DARK_BLUE);
    player1->getBoard()->addPatternLines(2,2, FIRST_PLAYER);

    player1->getBoard()->addWall(0,1, RED);
    player1->getBoard()->addWall(0,3, YELLOW);
    player1->getBoard()->addWall(1,1, DARK_BLUE);
    player1->getBoard()->addWall(1,4, LIGHT_BLUE);
    player1->getBoard()->addWall(4,4, BLACK);

    player1->getBoard()->addFloorLine(RED);
    player1->getBoard()->addFloorLine(YELLOW);

    centerOfTable->addTile(RED);
    centerOfTable->addTile(YELLOW);
    centerOfTable->addTile(BLACK);

    factories[0][0] = RED;
    factories[0][2] = DARK_BLUE;
    factories[3][2] = LIGHT_BLUE;
    factories[4][2] = YELLOW;

    bag->addBack(RED);
    bag->addBack(BLACK);

    std::ofstream inFile;
    inFile.open("azul.txt");
    printGame(inFile, game->getTable(), game->getCurrentPlayerID(), player1, player2);
    inFile.close();

    printGame(std::cout, game->getTable(), game->getCurrentPlayerID(), player1, player2);
    printBoard(std::cout, player1->getBoard()->getWall(), player1->getBoard()->getPatternLines(), player1->getBoard()->getFloorLine(), player1->getBoard()->getLength());
    printBoard(std::cout, player2->getBoard()->getWall(), player2->getBoard()->getPatternLines(), player2->getBoard()->getFloorLine(), player2->getBoard()->getLength());

    delete game;

    return EXIT_SUCCESS;
}