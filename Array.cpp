
#include "Array.h"

Array::Array(int arraySize) {
   this->length = 0;
   this->arraySize = arraySize;

   tileArray = new TilePtr[arraySize];
   for (int i = 0; i != arraySize; ++i) {
      tileArray[i] = nullptr;
   }
}

Array::Array(Array& other) :
   Array()
{
   length = other.length;

   for (int i = 0; i != length; ++i) {
      tileArray[i] = new tilePtr(*other.tileArray[i]);
   }
}

Array::~Array() {
   clear();
   delete tile;
}

int Array::size() {
   return length;
}

TilePtr Array::get(int index) {
   TilePtr tile = nullptr;
   if (index >=0 && index < length) {
      tile = tileArray[index];
   }

   return tile;
}

void Array::addTile(TilePtr tile) {
   if (length != arraySize) {
      tileArray[length] = tile;
      ++length; 
   }
}

void Array::addTile(TilePtr tile, int index) {
   if (length != arraySize &&
       index >= 0 && index < length) {
      for (int i = length - 1; i >= index; --i) {
         tileArray[i + 1] = tileArray[i];
      }
      
      tileArray[index] = tile;
      ++length; 
   }
}

void Array::removeTile(int index) {
   if (length > 0 &&
       index >= 0 && index < length) {

      for (int i = index; i < length; ++i) {
         if (length < arraySize -1) {
            tileArray[i] = tileArray[i + 1];
         }
      }

      tileArray[length] = nullptr;
      --length; 
   }
}

void Array::clear() {
   for (int i = 0; i != length; ++i) {
      delete tileArray[i];
      tileArray[i] = nullptr;
   }
}
