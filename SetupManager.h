#ifndef SETUPMANAGER_H
#define SETUPMANAGER_H

#include "LinkedList.h"
#include <array>

class SetupManager {

public:

    SetupManager(int seed);

    Tile intToChar(unsigned int number);

    // Shuffle methods.
    void swap(Tile& a, Tile& b);
    void shuffle(std::array<Tile, TILE_BAG_MAXIMUM> &tiles, int size);

    // Tile Bag Methods
    void populateTileBag(LinkedList* tileBag);
    
    void refillTileBagFromBoxLid(LinkedList* tileBag, LinkedList* boxLid);

    // Factory Methods
    void populateFactories(LinkedList* tileBag, Factory factories[NUMBER_OF_FACTORY], LinkedList* boxLid);

private:

};

#endif // SETUPMANAGER_H