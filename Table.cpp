#include "Table.h"

Table::Table(int seed) {
    this->tileBag = new LinkedList();
    this->boxLid = new LinkedList();

    this->seedNumber = seed;

    for(int i = 0; i < NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j < FACTORY_SIZE; j++) {
            factories[i][j] = NO_TILE;
        }
    }

    for(int i = 0; i < NUMBER_OF_FACTORY; i++) {
        chosenFactory[i] = NO_TILE;
    }
 

    centerOfTable = new Vector();

    sm = new SetupManager(seedNumber);
}

Table::~Table() {
    delete tileBag;
    delete boxLid;
    delete centerOfTable;
    delete sm;
}

LinkedList* Table::getTileBag() {
    return tileBag;
}

LinkedList* Table::getBoxLid() {
    return boxLid;
}

Factory* Table::getFactories() {
    return factories;
}

Vector* Table::getCenter() {
    return centerOfTable;
}

int Table::getSeedNumber() {
    return seedNumber;
}

void Table::setSeedNumber(int seedNumber) {
    this->seedNumber = seedNumber;
}

void Table::addFactory(int row, int col, Tile value) {
    factories[row][col] = value;
}

bool Table::isFactoryEmpty(int& pos) {
    bool isEmpty = true;
    for(int i = 0; i != FACTORY_SIZE; i++) {
        if(factories[pos][i] != NO_TILE) {
            isEmpty = false;
        }
    }
    return isEmpty;
}

bool Table::isCenterEmpty() {
    return centerOfTable->size() == 0 ? true : false;
}

bool Table::findColourInFactory(int& pos, char& colourChoice) {
    bool isFound = false;
    for(int i = 0; i != FACTORY_SIZE; i++) {
        if(factories[pos-1][i] == colourChoice) {
            isFound = true;
        }
    }
    return isFound;
}

bool Table::findColourInCenter(char& colourChoice) {
    bool isFound = false;
    if(!isCenterEmpty()) {
        for(int i = 0; i != centerOfTable->size(); i++) {
            if(centerOfTable->get(i) == colourChoice) {
                isFound = true;
            }
        }
    }
    return isFound;
}

void Table::setupGame() {
    sm->populateTileBag(tileBag);
    sm->populateFactories(tileBag, factories, boxLid);
    sm->addFirstPlayerTileToCenter(centerOfTable);
}

void Table::refillTable() {
    sm->populateFactories(tileBag, factories, boxLid);
}

void Table::populateChosenFactory(int& pos) {
    for(int i = 0; i != FACTORY_SIZE; i++) {
        chosenFactory[i] = factories[pos-1][i];
    }
}

Tile* Table::getChosenFactory() {
    return chosenFactory;
}

void Table::removeFactory(int& pos) {
    for(int i = 0; i != FACTORY_SIZE; i++) {
        factories[pos-1][i] = NO_TILE;
    }
}

void Table::clearChosenFactory() {
    for(int i = 0; i != FACTORY_SIZE; i++) {
       chosenFactory[i] = NO_TILE;
    }
}
