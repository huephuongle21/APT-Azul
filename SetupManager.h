#ifndef SETUPMANAGER_H
#define SETUPMANAGER_H

#include "LinkedList.h"
#include "Vector.h"

class SetupManager {

public:

    SetupManager();
    SetupManager(int seed, int boardId);

    Tile intToChar(int number);

    // Shuffle methods.
    void swap(Tile& a, Tile& b);
    void shuffle(Tile* tiles, int size);

    // Tile Bag Methods
    void populateTileBag(LinkedList* tileBag);
    
    void refillTileBagFromBoxLid(LinkedList* tileBag, LinkedList* boxLid);

    // Factory Methods
    void populateFactories(LinkedList* tileBag, 
        Factory factories[NUMBER_OF_FACTORY], LinkedList* boxLid);

    void addFirstPlayerTileToCenter(Vector* center);

private:
    int boardId;

};

#endif // SETUPMANAGER_H