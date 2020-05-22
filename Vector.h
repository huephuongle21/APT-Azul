
#ifndef VECTOR_H
#define VECTOR_H 

#include <vector>
#include "Types.h"

class Vector {
public:
   Vector();
   Vector(Vector& other);
   ~Vector();

   int size();

   Tile get(unsigned int index);

   void addTile(Tile tile);

   void removeTile(unsigned int index);

   void clear();

private:

   std::vector<Tile> tileVector;
};

#endif // VECTOR_H
