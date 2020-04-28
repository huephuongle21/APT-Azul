#include "LinkedList.h"

#include <exception>
#include <iostream>

Node::Node(int value, Node* next) {
    this->value = value;
    this->next = next;
}

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
int LinkedList::get(const unsigned int index) const {
   
   int count = 0;
   Node* current = head;
   int returnValue = 0;
   
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
bool LinkedList::get(const int index, int& returnValue) const {
   
   bool error = true;
   int count = 0;
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

void LinkedList::addFront(int value) {

    Node* toAdd = new Node(value, head);
    head = toAdd;
    ++length;

}

void LinkedList::addBack(int value) {
   
   Node* toAdd = new Node(value, nullptr);

   if (head == nullptr) {
        head = toAdd;
   } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
      }
      current->next = toAdd;
      ++length;
   }
}

void LinkedList::removeBack() {

    if (length > 0) {

        Node* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        delete current;
        --length;

    }
}

void LinkedList::removeFront() {
   
    if (length > 0) {
        Node* newHead = head->next;
        delete head;
        head = newHead;
        --length;
   }
}

void LinkedList::clear() {

    while (length > 0) {
        removeFront();
        --length;
    }

}