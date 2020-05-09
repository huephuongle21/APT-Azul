#include <iostream>

#include "Vector.h"

int main(void) {

    Vector* testVec = new Vector;

    testVec->addTile(new Tile(RED));

    if(testVec->get(0) == nullptr) {
        std::cout << "tile is being a fucking fuckhead" << std::endl;
    } else {
        std::cout << testVec->get(0)->getColourByChar() << std::endl;
    }

    testVec->removeTile(0);
    testVec->addTile(new Tile(BLACK));
    testVec->addTile(new Tile(DARK_BLUE));

    if(testVec->get(0) == nullptr) {
        std::cout << "tile is being a fucking fuckhead" << std::endl;
    } else {
        std::cout << testVec->get(0)->getColourByChar() << std::endl;
    }

    std::cout << testVec->get(0)->getColourByChar() << std::endl;
    std::cout << testVec->get(1)->getColourByChar() << std::endl;
    
    delete testVec;

    return EXIT_SUCCESS;
}
