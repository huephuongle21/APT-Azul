#include <iostream>

#include "SetupManager.h"

int main(void) {

    // Set random seed.
    int seed = 50;
    
    LinkedList* tileBag = new LinkedList();
    LinkedList* boxLid = new LinkedList();
    Factory factories[NUMBER_OF_FACTORY];
    SetupManager* sm = new SetupManager(seed);
    
    std::cout << std::endl;
    std::cout << "Tile Bag:" << std::endl;
    sm->populateTileBag(tileBag);

    // Prints all tile colours as chars from tile bag.
    for (int i = 0; i != TILE_BAG_MAXIMUM; ++i) {

        TilePtr tile = tileBag->get(i);
        std::cout << tile->getColourByChar();

    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Factories:" << std::endl;

    sm->populateFactories(tileBag, factories, boxLid);

     // Iterate through factories
    for (int factoryIndex = 0; factoryIndex != NUMBER_OF_FACTORY; ++factoryIndex) {
        
        // Print each tile colour
        for (int tileIndex = 0; tileIndex != FACTORY_SIZE; ++tileIndex) {
            std::cout << factories[factoryIndex][tileIndex]->getColourByChar();
        }

        std::cout << std::endl;
    }
    
    
    return EXIT_SUCCESS;
}
