#ifndef TILE_H
#define TILE_H

#include <string>

// First player tile
#define NO_TILE '.'

enum Colour {
   RED,
   YELLOW,
   DARK_BLUE,
   LIGHT_BLUE,
   BLACK
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

private:
   Colour   colour;

};

typedef Tile* TilePtr;

#endif // TILE_H
