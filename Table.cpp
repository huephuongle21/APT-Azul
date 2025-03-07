#include "Table.h"

Table::Table(int seed, int boardId) {
    this->tileBag = new LinkedList();
    this->boxLid = new LinkedList();

    this->seedNumber = seed;

    for(int i = 0; i < WALL_DIM; i++) {
        for(int j = 0; j < FACTORY_SIZE; j++) {
            factories[i][j] = NO_TILE;
        }
    }

    for(int i = 0; i < WALL_DIM; i++) {
        chosenFactory[i] = NO_TILE;
    }

    centerOfTable = new Vector();

    sm = new SetupManager(seedNumber, boardId);
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

bool Table::isFactoryEmpty(int& pos) {
    bool isEmpty = true;
    for(int i = 0; i != FACTORY_SIZE; i++) {
        if(factories[pos][i] != NO_TILE) {
            isEmpty = false;
        }
    }
    return isEmpty;
}

bool Table::isAllFactoriesEmpty() {
    bool isEmpty = true;
    for(int i = 0; i != WALL_DIM; i++) {
        if(!isFactoryEmpty(i)) {
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
    if(!isFound) {
        std::cout << "\n" << C_RED << U_INCORRECT_TICK << C_RESET 
            << "  Factory " << pos << " does not have that colour" << "\n" << std::endl;
    }
    return isFound;
}

bool Table::findColourInCenter(char& colourChoice) {
    bool isFound = false;
    if(!isCenterEmpty()) {
        for(unsigned int i = 0; i != centerOfTable->size(); i++) {
            if(centerOfTable->get(i) == colourChoice) {
                isFound = true;
            }
        }
        if(!isFound) {
            std::cout << "\n" << C_RED << U_INCORRECT_TICK << C_RESET 
                << "  Center does not have that colour" << "\n" << std::endl;
        }
    } else {
        std::cout << "\n" << C_RED << U_INCORRECT_TICK << C_RESET
            << "  Center of table is empty" << "\n" << std::endl;
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
