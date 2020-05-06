#ifndef LINKED_LIST_H
#define LINKED_LIST_H 

<<<<<<< HEAD
#include "Tile.h"
#include "Types.h"
#include <iostream>

class Node {
public:
   Node(TilePtr value, Node* next);

   ~Node();
   
   TilePtr value;
=======
class Node {
public:
   Node(int value, Node* next);

   int value;
>>>>>>> master
   Node* next;
};

class LinkedList {
public:
   LinkedList();
   LinkedList(const LinkedList& other);
   ~LinkedList();

   /**
    * Return the current size of the Linked List.
    */
   unsigned int size() const;

   /**
    * output: Get the value at the given index.
    * input: Index must be >=0 and < size()
    * 
    */
<<<<<<< HEAD
   TilePtr get(const unsigned int index) const;
   bool get(const unsigned int index, TilePtr returnValue) const;
=======
   int get(const unsigned int index) const;
   bool get(const unsigned int index, int& returnValue) const;
>>>>>>> master

   /**
    * Add the value to the back of the Linked List
    */
<<<<<<< HEAD
   void addBack(TilePtr tile);
=======
   void addBack(int value);
>>>>>>> master

   /**
    * Add the value to the front of the Linked List
    */
<<<<<<< HEAD
   void addFront(TilePtr tile);
=======
   void addFront(int value);
>>>>>>> master

   /**
    * Remove the value at the back of the Linked List
    */
   void removeBack();

   /**
    * Remove the value at the front of the Linked List
    */
   void removeFront();

   /**
    * Removes all values from the Linked List
    */
   void clear();

private:

   Node* head;
   int length;
};

<<<<<<< HEAD
#endif // LINKED_LIST_H

=======
#endif // LINKED_LIST_H
>>>>>>> master
