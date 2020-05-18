#include "GameManager.h"
#include "Types.h"
#include <iostream>


int main(void) {
    GameManager* gm = new GameManager("Alice","Bob");
    Player* player1 = gm->getPlayer(1);

    player1->getBoard()->addPatternLines(0,0,RED);
    player1->getBoard()->addPatternLines(1,1,YELLOW);
    player1->getBoard()->addPatternLines(3,3,BLACK);
    player1->getBoard()->addPatternLines(3,2,BLACK);
    player1->getBoard()->addPatternLines(3,1,BLACK);
    player1->getBoard()->addPatternLines(3,0,BLACK);
    player1->getBoard()->addPatternLines(2,0,LIGHT_BLUE);
    player1->getBoard()->addPatternLines(2,1,LIGHT_BLUE);
    player1->getBoard()->addPatternLines(2,2,LIGHT_BLUE);
    player1->getBoard()->addPatternLines(4,4,LIGHT_BLUE);

    gm->printTableAndBoard(player1);
    gm->moveTilesFromPatternLines(gm->getPlayer(1));
    gm->printTableAndBoard(player1);
    for(unsigned int i = 0; i != gm->getTable()->getBoxLid()->size(); i++) {
        std::cout << gm->getTable()->getBoxLid()->get(i);
    }
    std::cout << std::endl;

    player1->getBoard()->addPatternLines(1,0,YELLOW);
    gm->moveTilesFromPatternLines(gm->getPlayer(1));
    gm->printTableAndBoard(player1);
    for(unsigned int i = 0; i != gm->getTable()->getBoxLid()->size(); i++) {
        std::cout << gm->getTable()->getBoxLid()->get(i);
    }
    std::cout << std::endl;

    player1->getBoard()->addPatternLines(4,3,LIGHT_BLUE);
    player1->getBoard()->addPatternLines(4,2,LIGHT_BLUE);
    player1->getBoard()->addPatternLines(4,1,LIGHT_BLUE);

    gm->moveTilesFromPatternLines(gm->getPlayer(1));
    gm->printTableAndBoard(player1);

    player1->getBoard()->addPatternLines(4,0,LIGHT_BLUE);
    gm->moveTilesFromPatternLines(gm->getPlayer(1));
    gm->printTableAndBoard(player1);
    for(unsigned int i = 0; i != gm->getTable()->getBoxLid()->size(); i++) {
        std::cout << gm->getTable()->getBoxLid()->get(i);
    }
    std::cout << std::endl;



}