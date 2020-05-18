#include "Board.h"
#include "Utility.h"
#include "GameManager.h"
#include "Types.h"


int main(void) {

    GameManager* gm = new GameManager("Alice","Bob");
    Table* table = gm->getTable();
    Tile red = RED;
    Tile yellow = YELLOW;
    Tile light = LIGHT_BLUE;
    // Tile dark = DARK_BLUE;
    // Tile black = BLACK;
    Tile invalid = 'd';
    int center = 0;
    int first = 1;
    int second = 2;
    int fifth = 5;

    std::cout << gm->isEndRound() << std::endl; //1
    
    std::cout << gm->promptForColourChoice(red) << std::endl; //1
    std::cout << gm->promptForColourChoice(yellow) << std::endl; //1
    std::cout << gm->promptForColourChoice(invalid) << std::endl; //0

    std::cout << gm->promptForFactoryChoice(center, red) << std::endl; //0

    table->getCenter()->addTile(LIGHT_BLUE);
    table->getCenter()->addTile(DARK_BLUE);

    std::cout << gm->promptForFactoryChoice(center, light) << std::endl; //1

    std::cout << gm->promptForFactoryChoice(first, red) << std::endl; //0

    table->addFactory(0,1,RED);
    table->addFactory(0,2,YELLOW);

    std::cout << gm->promptForFactoryChoice(first, red) << std::endl; //1

    std::cout << gm->promptForFactoryChoice(second, invalid) << std::endl; //0

    table->addFactory(1,4,LIGHT_BLUE);
    table->addFactory(1,2,RED);

    std::cout << gm->promptForFactoryChoice(second, red) << std::endl; //1

    gm->getPlayer(1)->getBoard()->addPatternLines(0,0,RED);
    gm->getPlayer(1)->getBoard()->addPatternLines(4,0,RED);
    gm->getPlayer(1)->getBoard()->addPatternLines(4,1,RED);
    gm->getPlayer(1)->getBoard()->addPatternLines(2,2,RED);

    std::cout << gm->promptForPatternLineChoice(gm->getPlayer(1), first, red) << std::endl; //0
    std::cout << gm->promptForPatternLineChoice(gm->getPlayer(1), second, red) << std::endl; //1
    std::cout << gm->promptForPatternLineChoice(gm->getPlayer(1), fifth, red) << std::endl; //1
    std::cout << gm->promptForPatternLineChoice(gm->getPlayer(1), fifth, yellow) << std::endl; //0

    std::cout << gm->playerTurn(gm->getPlayer(1), "turn 0 L 1") << std::endl; // 0
    std::cout << gm->playerTurn(gm->getPlayer(1), "turn 1 R 2") << std::endl; // 1
    std::cout << gm->playerTurn(gm->getPlayer(1), "turn 1 R 1") << std::endl; //0
    std::cout << gm->playerTurn(gm->getPlayer(1), "turn 1 Y 5") << std::endl; //0
    std::cout << gm->playerTurn(gm->getPlayer(1), "turn 3 R 5") << std::endl; //0

    std::cout << gm->isEndRound() << std::endl; //0
    gm->getPlayer(1)->getBoard()->addWall(1,1,RED);

    // gm->commenceTurn(gm->getPlayer(1));
    gm->commenceRound();

    delete gm;
}