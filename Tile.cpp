#include "Tile.h"

Tile::Tile(Colour colour) {
    this->colour = colour;
}
   
Tile::Tile(Tile& other) {

}

Tile::~Tile() {

}

/**
* Get the Tile colour
*/

char Tile::getColourByChar() {
    char returnColour = NO_TILE;
    if(colour == RED) {
        returnColour = 'R';
    } else if(colour == YELLOW) {
        returnColour = 'Y';
    } else if(colour == DARK_BLUE) {
        returnColour = 'B';
    } else if (colour == LIGHT_BLUE) {
        returnColour = 'L';
    } else if (colour == BLACK) {
        returnColour = 'U';
    } else if (colour == WHITE) {
        returnColour = FIRST_PLAYER;
    }
    return returnColour;
}
