#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "GameManager.h"
#include "Utility.h"

int main(void) {

    // Generate game and players.
    std::string p1 = "Alice";
    std::string p2 = "Bob";
    
    GameManager* gm = new GameManager(p1, p2, 1590043364);

    // Generate tiles and fill factories.
    gm->getTable()->setupGame();

    // Attempt save.
    std::string savePath = "program_generated_saves/testSaveAlpha.txt";
    gm->saveGame(savePath);

    // Attempt load.
    GameManager* gm2 = new GameManager();
    gm2->loadGame(savePath);

    delete gm;
    delete gm2;
    
    return EXIT_SUCCESS;
}
