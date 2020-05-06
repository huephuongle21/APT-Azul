
#ifndef VECTOR_H
#define VECTOR_H 

#include <vector>

#include "Tile.h"


class Vector {
public:
   Vector();
   Vector(Vector& other);
   ~Vector();

   int size();

   TilePtr get(int index);

   void addTile(TilePtr tile);

   void addTile(TilePtr tile, int index);

   void removeTile(int index);

   void clear();

private:

   std::vector<TilePtr> tileVector;
};

#endif // VECTOR_H
