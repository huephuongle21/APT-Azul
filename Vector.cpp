#include <iostream>


#include "Vector.h"

Vector::Vector() :
   tileVector()
{

}

Vector::Vector(Vector& other) :
   tileVector(other.tileVector)
{
   
}

Vector::~Vector() {
}

 int Vector::size() {
   return tileVector.size();
}

TilePtr Vector::get(unsigned int index) {
   TilePtr tile = nullptr;
   if (index >=0 && index < tileVector.size()) {
      tile = tileVector.at(index);
   }

   return tile;
}

void Vector::addTile(TilePtr tile) {
   tileVector.push_back(tile);
}

void Vector::removeTile(unsigned int index) {
   if (tileVector.size() > 0 &&
       index >= 0 && index < tileVector.size()) {
      for (unsigned int i = index; i < tileVector.size() - 1; ++i) {
         tileVector[i] = tileVector[i + 1];
      }

      tileVector.pop_back();
   }
}

void Vector::clear() {
   tileVector.clear();
}