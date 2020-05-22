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
   clear();
}

 int Vector::size() {
   return tileVector.size();
}

Tile Vector::get(unsigned int index) {
   Tile tile = NO_TILE;
   if (index >=0 && index < tileVector.size()) {
      tile = tileVector.at(index);
   }
   return tile;
}

void Vector::addTile(Tile tile) {
   tileVector.push_back(tile);
}

void Vector::removeTile(unsigned int index) {
   if (tileVector.size() > 0 && index >= 0 && index < tileVector.size()) {
      for (unsigned int i = index; i < tileVector.size() - 1; ++i) {
         tileVector[i] = tileVector[i + 1];
      }
      tileVector.pop_back();
   }
}

void Vector::clear() {
   tileVector.clear();
}