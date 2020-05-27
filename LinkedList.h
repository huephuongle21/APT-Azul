#ifndef LINKED_LIST_H
#define LINKED_LIST_H 

#include "Types.h"
#include <iostream>

class Node {
public:
   Node(Tile value, Node* next);
   ~Node();
   Tile value;
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
   int size() const;

   /**
    * output: Get the value at the given index.
    * input: Index must be >=0 and < size()
    * 
    */
   Tile get(const int index) const;
   bool get(const int index, Tile returnValue) const;

   /**
    * Add the value to the back of the Linked List
    */
   void addBack(Tile tile);

   /**
    * Add the value to the front of the Linked List
    */
   void addFront(Tile tile);

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

#endif // LINKED_LIST_H

