#ifndef ARRAY_H
#define ARRAY_H

#include <array>

#include "Tile.h"

class Array {
public:
   Array(int arraySize);
   // Array(Array& other);
   ~Array();

   int size();

   TilePtr get(int index);

   void addTile(TilePtr tile);

   void addTile(TilePtr tile, int index);

   void removeTile(int index);

   void clear();

private:

   int length;
   int arraySize;

   TilePtr* tileArray;
};

#endif // ARRAY_H