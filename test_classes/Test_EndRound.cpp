#include "GameManager.h"
#include "Types.h"
#include <iostream>


int main(void) {
    GameManager* gm = new GameManager("Alice","Bob", 1590043364);
    Player* player1 = gm->getPlayer(1);
    Board* board = player1->getBoard();
    LinkedList* box = gm->getTable()->getBoxLid();

    board->addPatternLines(0,0,RED);
    board->addPatternLines(1,1,YELLOW);
    board->addPatternLines(3,3,BLACK);
    board->addPatternLines(3,2,BLACK);
    board->addPatternLines(3,1,BLACK);
    board->addPatternLines(3,0,BLACK);
    board->addPatternLines(2,0,LIGHT_BLUE);
    board->addPatternLines(2,1,LIGHT_BLUE);
    board->addPatternLines(2,2,LIGHT_BLUE);
    board->addPatternLines(4,4,LIGHT_BLUE);

    board->addFloorLine(RED);
    board->addFloorLine(YELLOW);

    gm->printTableAndBoard(player1);
    gm->commenceEndOfRound(player1);
    std::cout << "Points for " << player1->getName() << " is " << player1->getPoints() << std::endl;
     
    // std::cout << gm->moveTilesFromPatternLines(player1) << std::endl;
    gm->printTableAndBoard(player1);
    for(unsigned int i = 0; i != box->size(); i++) {
        std::cout << box->get(i);
    }
    std::cout << std::endl;

    board->addPatternLines(1,0,YELLOW);
    gm->commenceEndOfRound(player1);
    std::cout << "Points for " << player1->getName() << " is " << player1->getPoints() << std::endl; 

    // std::cout << gm->moveTilesFromPatternLines(player1) << std::endl;
    gm->printTableAndBoard(player1);
    for(unsigned int i = 0; i != box->size(); i++) {
        std::cout << box->get(i);
    }
    std::cout << std::endl;

    board->addPatternLines(4,3,LIGHT_BLUE);
    board->addPatternLines(4,2,LIGHT_BLUE);
    board->addPatternLines(4,1,LIGHT_BLUE);

    gm->commenceEndOfRound(player1);
    gm->printTableAndBoard(player1);

    board->addFloorLine(RED);
    board->addFloorLine(YELLOW);
    board->addFloorLine(RED);
    board->addFloorLine(YELLOW);

    board->addPatternLines(4,0,LIGHT_BLUE);
    gm->commenceEndOfRound(player1);
    gm->printTableAndBoard(player1);
    for(unsigned int i = 0; i != box->size(); i++) {
        std::cout << box->get(i);
    }
    std::cout << std::endl;

    delete gm;

}