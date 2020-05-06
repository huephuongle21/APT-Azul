
#include "Vector.h"

#define MAXIMUM_DECK_SIZE    50

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

TilePtr Vector::get(int index) {
   TilePtr tile = nullptr;
   if (index >=0 && index < tileVector.size()) {
      tile = tileVector[index];
   }

   return tile;
}

void Vector::addTile(TilePtr tile) {
   tileVector.push_back(tile);
}

// Double check this!!
void Vector::addTile(TilePtr tile, int index) {
   tileVector.insert(tileVector.begin() + index, tile);
}

void Vector::removeTile(int index) {
   if (tileVector.size() > 0 &&
       index >= 0 && index < tileVector.size()) {
      for (int i = index; i < tileVector.size() - 1; ++i) {
         tileVector[i] = tileVector[i+1];
      }

      tileVector.pop_back();
   }
}

void Vector::clear() {
   tileVector.clear();
}