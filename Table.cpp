#include "Table.h"

Table::Table() {
    this->tileBag = new LinkedList();
    this->boxLid = new LinkedList();

    seedNumber = 10;

    for(int i = 0; i < NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j < FACTORY_SIZE; j++) {
            factories[i][j] = NO_TILE;
        }
    }

    centerOfTable = new Vector();
}

Table::~Table() {
    delete tileBag;
    delete boxLid;
    delete centerOfTable;
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