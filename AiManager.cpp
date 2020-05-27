#include "AiManager.h"

AiManager::AiManager() {
    listTurn = {};

    listColour = {new TileList(RED), new TileList(YELLOW), new TileList(BLACK), 
        new TileList(LIGHT_BLUE), new TileList(DARK_BLUE)};

    listColourLength = NUM_PLAYABLE_COLOURS;
}

AiManager::~AiManager() {
    for(unsigned int i = 0; i != listTurn.size(); i++) {
        if(listTurn.at(i) != nullptr) {
            delete listTurn.at(i);
            listTurn.at(i) = nullptr;
        }
    }
    listTurn.clear();
    for(int i = 0; i != listColourLength; i++) {
        delete listColour[i];
        listColour[i] = nullptr;
    }
    listColourLength = 0;
}

void AiManager::generatePossibleTurn(Table* table) {
    Factory* factories = table->getFactories();

    // Loop through all the factories to generate turn (except center factory)
    for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j != FACTORY_SIZE; j++) {
            Tile tile = factories[i][j];
            if(tile != NO_TILE) {
                listColour[getIndexByColour(tile)]->updateNumberOfTiles(1);
                for(int index = 0; index != FLOORLINE_POSITION; index++) {
                    AiTurn* turn = new AiTurn(i+1, tile, index+1, true);
                    listTurn.push_back(turn);
                }
            }
        }
    }
    sortColor();

    // Generate all possible turns for from center of table
    for(int i = 0; i != listColourLength; i++) {
        TileList* list = listColour[i];
        if(list->getNumberOfTiles() != 0) {
            Tile tile = list->getColour();
            for(int index = 0; index != FLOORLINE_POSITION; index++) {
                AiTurn* turn = new AiTurn(0, tile, index+1, true);
                listTurn.push_back(turn);
            }
        }
    }
}

int AiManager::getIndexByColour(Tile tile) {
    int index = -1;
    for(int i = 0; i != listColourLength; i++) {
        if(listColour[i]->getColour() == tile) {
            index = i;
        }
    }
    return index;
}

void AiManager::sortColor() {
    for(int i = 0; i != listColourLength; i++) {
        TileList* tileList = listColour[i];
        if(tileList->getNumberOfTiles() == 0) {
            updateTurnByColour(tileList->getColour());
        }     
    }
}

// std::vector<AITurn*>& AIManager::getListOfTurn() {
//     return listTurn;
// }

void AiManager::printPossibleTiles() {
    for(int i = 0; i != listColourLength; i++) {
        TileList* list = listColour[i];
        std::cout << list->getColour() << " " << list->getNumberOfTiles() << std::endl;
    }
    std::cout << std::endl;
}

void AiManager::printTurn() {
    for(unsigned int i = 0; i != listTurn.size(); i++) {
        if(listTurn.at(i)->isValid()) {
            std::cout << listTurn.at(i)->toString() << std::endl;
        }
    }
}

void AiManager::updateByTurnFromFactory(int& factoryChoice, char& colourChoice) {
    int count = 0;
    for(unsigned int i = 0; i != listTurn.size(); i++) {
        AiTurn* turn = listTurn.at(i);
        if(turn->getFactoryChoice() == factoryChoice) {
            if(turn->getTileChoice() == colourChoice) {
                count++;
            }
            turn->setValid(false);
        }
    }
    int numTiles = count/FLOORLINE_POSITION;
    int minus = 0-numTiles;
    listColour[getIndexByColour(colourChoice)]->updateNumberOfTiles(minus);
    sortColor();
}

void AiManager::updateTurnByColour(Tile colour) {
    for(unsigned int i = 0; i != listTurn.size(); i++) {
        AiTurn* turn = listTurn.at(i);
        if(turn->getTileChoice() == colour) {
            turn->setValid(false);
        }
    }
}

void AiManager::updateByTurnFromCenter(char& colourChoice, Table* table, int numTilesTaken) {
    if(table->isAllFactoriesEmpty()) {
        for(unsigned int i = 0; i != listTurn.size(); i++) {
            AiTurn* turn = listTurn.at(i);
            if(turn->getTileChoice() == colourChoice) {
                turn->setValid(false);
            }
        }
    } else {
        int minus = 0-numTilesTaken;
        listColour[getIndexByColour(colourChoice)]->updateNumberOfTiles(minus);
        sortColor();
    }
}