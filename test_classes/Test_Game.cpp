#include <iostream>

#include "GameManager.h"

int main(void) {


    GameManager* gm = new GameManager;

    std::cout << gm->getCurrentPlayerID() << std::endl;
    gm->swapCurrentPlayer();
    std::cout << gm->getCurrentPlayerID() << std::endl;
    gm->swapCurrentPlayer();
    std::cout << gm->getCurrentPlayerID() << std::endl;
    
    return EXIT_SUCCESS;
}
