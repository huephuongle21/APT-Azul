#include "AIManager.h"

AIManager::AIManager() {
    listTurn = {};

    remainingColor = new Vector();
    remainingColor->add(RED);
    remainingColor->add(YELLOW);
    remainingColor->add(BLACK);
    remainingColor->add(LIGHT_BLUE);
    remainingColor->add(DARK_BLUE);

    numRedTile = 0;
    numYellowTile = 0;
    numBlackTile = 0;
    numLightBlueTile = 0;
    numDarkBlueTile = 0;
}

AIManager::~AIManager() {
    for(unsigned int i = 0; i != listTurn.size(); i++) {
        delete listTurn.at(i);
        listTurn.at(i) = nullptr;
    }

    remainingColor->clear();
    numRedTile = 0;
    numYellowTile = 0;
    numBlackTile = 0;
    numLightBlueTile = 0;
    numDarkBlueTile = 0;
}

void AIManager::generatePossibleTurn(Table* table) {
    Factory* factories = table->getFactories();

    // Loop through all the factories to generate turn (except center factory)
    for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j != FACTORY_SIZE; j++) {
            Tile tile = factories[i][j];
            if(tile != NO_TILE) {
                countNumberOfTile(tile);
                for(int index = 0; index != FLOORLINE_POSITION; index++) {
                    AITurn* turn = new AITurn(i+1, tile, index+1);
                    listTurn.push_back(turn);
                }
            }
        }
    }
    sortColor();

    // Generate all possible turns for from center of table
    for(int i = 0; i != remainingColor->size(); i++) {
        Tile tile = remainingColor->get(i);
        for(int index = 0; index != FLOORLINE_POSITION; index++) {
            AITurn* turn = new AITurn(0, tile, index+1);
            listTurn.push_back(turn);
        }
    }
}

void AIManager::sortColor() {
    if(numRedTile == 0) {
        remainingColor->removeByName(RED);
    } else if(numYellowTile == 0) {
        remainingColor->removeByName(YELLOW);
    } else if(numBlackTile == 0) {
        remainingColor->removeByName(BLACK);
    } else if(numLightBlueTile == 0) {
        remainingColor->removeByName(LIGHT_BLUE);
    } else if(numDarkBlueTile == 0) {
        remainingColor->removeByName(DARK_BLUE);
    }
}

void AIManager::countNumberOfTile(Tile& tile) {
    if(tile == RED) {
        numRedTile++;
    } else if(tile == YELLOW) {
        numYellowTile++;
    } else if(tile == BLACK) {
        numBlackTile++;
    } else if(tile == LIGHT_BLUE) {
        numLightBlueTile++;
    } else if(tile == DARK_BLUE) {
        numDarkBlueTile++;
    }
}

std::vector<AITurn*>& AIManager::getListOfTurn() {
    return listTurn;
}

Tile* AIManager::sortFactory(Tile* factory) {
    
}
