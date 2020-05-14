
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

   char get(unsigned int index);

   void addTile(char tile);

   void removeTile(unsigned int index);

   void clear();

private:

   std::vector<char> tileVector;
};

#endif // VECTOR_H
