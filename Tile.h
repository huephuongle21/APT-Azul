#ifndef TILE_H
#define TILE_H

#include <string>

// First player tile
#define NO_TILE       '.'
#define FIRST_PLAYER  'F'

enum Colour {
   RED,
   YELLOW,
   DARK_BLUE,
   LIGHT_BLUE,
   BLACK,
   WHITE
};

class Tile {
public:
   Tile(Colour colour);
   Tile(Tile& other);
   ~Tile();

   /**
    * Get the Tile colour
    */
   char getColourByChar();
   Colour getColour();

private:
   Colour   colour;

};

typedef Tile* TilePtr;

#endif // TILE_H
