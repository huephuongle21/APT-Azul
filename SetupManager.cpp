#include "SetupManager.h"
#include "Types.h"

#include <time.h>

SetupManager::SetupManager() {
    std::srand(time(NULL));
}

SetupManager::SetupManager(int seed) {
    std::srand(seed);
}

// input: an integer between 0 and 4 (inclusive)
// output: the corresponding tile colour (white if input > 4)
Tile SetupManager::intToChar(unsigned int number) {

    Tile returnColour = FIRST_PLAYER;

    if(number == 0) {
        returnColour = RED;
    } else if (number == 1) {
        returnColour = YELLOW;
    } else if (number == 2) {
        returnColour = DARK_BLUE;
    } else if (number == 3) {
        returnColour = LIGHT_BLUE;
    } else if (number == 4) {
        returnColour = BLACK;
    }
    
    return returnColour;

}

void SetupManager::swap(Tile &a, Tile &b)  {  
    Tile tmp = a;  
    a = b;  
    b = tmp;
}

void SetupManager::shuffle(std::array<Tile, TILE_BAG_MAXIMUM> &tiles, int size) {
    
    for (int i = size - 1; i > 0; --i)  {  
        
        // Pick a random index from 0 to i  
        int j = rand() % (i + 1);
  
        // Swap arr[i] with the element at random index  
        swap(tiles[j], tiles[i]);
    } 
}

// Tile Bag Methods
void SetupManager::populateTileBag(LinkedList* tileBag) {

    std::array<Tile, TILE_BAG_MAXIMUM> tiles;
    int index = 0;

    // Set up ordered array of tiles.
    for (int i = 0; i != NUM_PLAYABLE_COLOURS; ++i) {

        // Iterate through all playable tile colours.
        Tile colourToAdd = intToChar(i); 
        
        for (int j = 0; j != TILES_PER_COLOUR; ++j) {

            // Add 20 tiles of each colour.
            Tile tileToAdd = colourToAdd;
            tiles[index] = tileToAdd;
            ++index;
        }
    }

    // Randomise order of tiles.
    shuffle(tiles, tiles.size());

    // Add tiles to tile bag.
    for (int i = 0; i != tiles.size(); ++i) {
        tileBag->addFront(tiles[i]);
    }

}

// When tile bag is empty, transfer tiles from box lid to tile bag.
// Currently does not shuffle.
void SetupManager::refillTileBagFromBoxLid(LinkedList* tileBag, LinkedList* boxLid) {
    
    for (unsigned int i = 0; i != boxLid->size(); ++i) {
        tileBag->addFront(boxLid->get(i));
    }

    boxLid->clear();
}

void SetupManager::populateFactories(LinkedList* tileBag, 
        Factory factories[NUMBER_OF_FACTORY], LinkedList* boxLid) {

    // Iterate through factories
    for (int factoryIndex = 0; factoryIndex != NUMBER_OF_FACTORY; ++factoryIndex) {

        // Ensure there are enough tiles to fill the factory.
        if (tileBag->size() < FACTORY_SIZE) {
            refillTileBagFromBoxLid(tileBag, boxLid);
        } 
        
        // Fill each tile index in factory.
        for (int tileIndex = 0; tileIndex != FACTORY_SIZE; ++tileIndex) {

            factories[factoryIndex][tileIndex] = tileBag->get(0);
            tileBag->removeFront();
            
        }
    }

}

void SetupManager::addFirstPlayerTileToCenter(Vector* center) {
    center->add(FIRST_PLAYER);
}

