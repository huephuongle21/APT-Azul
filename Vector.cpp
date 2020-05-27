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

unsigned int Vector::size() {
   return tileVector.size();
}

Tile Vector::get(unsigned int index) {
   Tile tile = NO_TILE;
   if (index >=0 && index < tileVector.size()) {
      tile = tileVector.at(index);
   }
   return tile;
}

void Vector::add(Tile tile) {
   tileVector.push_back(tile);
}

void Vector::remove(unsigned int index) {
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

void Vector::removeByName(Tile tile) {
   unsigned int size = tileVector.size();
   if(size > 0) {
         for(unsigned int index = 0; index != size; index++) {
            if(get(index) == tile) {
               for (unsigned int i = index; i < size - 1; ++i) {
               tileVector[i] = tileVector[i + 1];
               }
               tileVector.pop_back();
            }
         }
      }
}