#ifndef ARRAY_H
#define ARRAY_H

#include "Tile.h"

class Array {
public:
   Array(int arraySize);
   Array(Array& other);
   ~Array();

   int size();

   TilePtr get(int index);

   void addTile(TilePtr tile);

   void addTile(TilePtr tile, int index);

   void removeTile(int index);

   void clear();

private:

   TilePtr* tileArray;
   int length;
   int arraySize;
};

#endif // ARRAY_H