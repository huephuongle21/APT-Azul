#include "LinkedList.h"

#include <exception>
#include <iostream>

<<<<<<< HEAD
Node::Node(TilePtr value, Node* next) {
=======
Node::Node(int value, Node* next) {
>>>>>>> master
    this->value = value;
    this->next = next;
}

<<<<<<< HEAD
Node::~Node() {
   delete this->value;
   this->value = nullptr;
}

=======
>>>>>>> master
LinkedList::LinkedList() {
   this->head = nullptr;
   this->length = 0;

}

LinkedList::LinkedList(const LinkedList& other) {
   this->head = other.head;
   this->length = other.length;
}

LinkedList::~LinkedList() {
   clear();
}

unsigned int LinkedList::size() const {
   return length;
}

// Version of get that throws an exception when index is out of range.
<<<<<<< HEAD
TilePtr LinkedList::get(const unsigned int index) const {
   unsigned int count = 0;
   Node* current = head;
   TilePtr returnValue = nullptr;
=======
int LinkedList::get(const unsigned int index) const {
   
   unsigned int count = 0;
   Node* current = head;
   int returnValue = 0;
>>>>>>> master
   
   if (index < size()) {
      
      while(count < index) {
        ++count;
        current = current->next;
      }

      returnValue = current->value;
      
      } else {
        throw std::out_of_range("Linked List get - index out of range");
   }
   return returnValue;
}

// Version of get that returns error "code" when index is out of range.
<<<<<<< HEAD
bool LinkedList::get(const unsigned int index, TilePtr returnValue) const {
=======
bool LinkedList::get(const unsigned int index, int& returnValue) const {
>>>>>>> master
   
   bool error = true;
   unsigned int count = 0;
   Node* current = head;
   
   if (index >= 0 && index < size()) {
      
      while(count < index) {
        ++count;
        current = current->next;
      }

      returnValue = current->value;
      error = false;
   }
   
   return error;
}

<<<<<<< HEAD
void LinkedList::addFront(TilePtr tile) {

    Node* toAdd = new Node(tile, head);
=======
void LinkedList::addFront(int value) {

    Node* toAdd = new Node(value, head);
>>>>>>> master
    head = toAdd;
    ++length;

}

<<<<<<< HEAD
void LinkedList::addBack(TilePtr tile) {
   
   Node* toAdd = new Node(tile, nullptr);
=======
void LinkedList::addBack(int value) {
   
   Node* toAdd = new Node(value, nullptr);
>>>>>>> master

   if (head == nullptr) {
        head = toAdd;
   } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
      }
      current->next = toAdd;
<<<<<<< HEAD
   }
   ++length;
=======
      ++length;
   }
>>>>>>> master
}

void LinkedList::removeBack() {

    if (length > 0) {

        Node* current = head;

        while (current->next != nullptr) {
            current = current->next;
<<<<<<< HEAD
         }
=======
        }
>>>>>>> master

        delete current;
        --length;

    }
}

void LinkedList::removeFront() {
   
<<<<<<< HEAD
   if (length > 0) {
         Node* newHead = head->next;
         delete head;
         head = newHead;
         --length;
=======
    if (length > 0) {
        Node* newHead = head->next;
        delete head;
        head = newHead;
        --length;
>>>>>>> master
   }
}

void LinkedList::clear() {

<<<<<<< HEAD
   while (length > 0) {
      removeFront();
      --length;
   }

}
=======
    while (length > 0) {
        removeFront();
        --length;
    }

}
>>>>>>> master
