
#ifndef VECTOR_H
#define VECTOR_H 

#include <vector>
#include "Types.h"

class Vector {
public:
   Vector();
   Vector(Vector& other);
   ~Vector();

   unsigned int size();

   Tile get(unsigned int index);

   void add(Tile tile);

   void remove(unsigned int index);

   void removeByName(Tile tile);

   void clear();

private:

   std::vector<Tile> tileVector;
};

#endif // VECTOR_H
