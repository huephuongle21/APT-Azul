#include <iostream>

#include "Vector.h"
#include "Types.h"

int main(void) {

    Vector* testVec = new Vector;

    testVec->addTile(RED);

    if(testVec->get(0) == NO_TILE) {
        std::cout << "tile is being a fucking fuckhead" << std::endl;
    } else {
        std::cout << testVec->get(0) << std::endl;
    }

    testVec->removeTile(0);
    testVec->addTile(BLACK);
    testVec->addTile(DARK_BLUE);

    if(testVec->get(0) == NO_TILE) {
        std::cout << "tile is being a fucking fuckhead" << std::endl;
    } else {
        std::cout << testVec->get(0) << std::endl;
    }

    std::cout << testVec->get(0) << std::endl;
    std::cout << testVec->get(1) << std::endl;
    
    delete testVec;

    return EXIT_SUCCESS;
}
