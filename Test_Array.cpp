#include <iostream>

#include "Array.h"

int main(void) {

    Array* testArr = new Array(5);

    for(int i = 0; i != 15; ++i) {
        testArr->addTile(new Tile(RED));
    }

    for(int i = 0; i != testArr->size(); ++i) {
        std::cout << testArr->get(i)->getColourByChar();
    }

    std::cout << std::endl;

    std::cout << testArr->size() << std::endl;

    testArr->removeTile(2);

    std::cout << testArr->size() << std::endl;

    testArr->addTile(new Tile(BLACK));

    for(int i = 0; i != testArr->size(); ++i) {
        std::cout << testArr->get(i)->getColourByChar();
    }

    std::cout << std::endl;

    for(int i = 0; i != testArr->size(); ++i) {
        testArr->removeTile(i);
    }

    std::cout << testArr->size() << std::endl;

    delete testArr;

    return EXIT_SUCCESS;
}