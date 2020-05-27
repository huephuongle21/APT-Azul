#include "TileList.h"

TileList::TileList(char colour) {
    this->colour = colour;
    this->numberOfTiles = 0;
}

TileList::~TileList() {

}

void TileList::updateNumberOfTiles(int offSet) {
    numberOfTiles += offSet;
}

int TileList::getNumberOfTiles() {
    return this->numberOfTiles;
}

char TileList::getColour() {
    return this->colour;
}