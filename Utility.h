
#ifndef UTILITY_H
#define UTILITY_H

#include "LinkedList.h"
#include "Player.h"
#include "Board.h"

Colour readColour(char c);

void printGame(std::ostream& outStream, LinkedList* tileBag, LinkedList* boxLid, Player* player1, 
        Player* player2, Factory factories[], std::vector<TilePtr>& centerOfTable);

void printFactory(std::ostream& outStream, Factory factories[]);

void printVector(std::ostream& outStream, std::vector<TilePtr>& vector);

void printPlayer(std::ostream& outStream, Player* player);

void printBoard(std::ostream& outStream, Board* board);

void printArray(std::ostream& outStream, TilePtr* array, int size);

void printWall(std::ostream& outStream, Wall& wall);

void printPatternLines(std::ostream& outStream, Board* board);

void printLinkedList(std::ostream& outStream, LinkedList* list);

void readGame(std::istream& inStream, LinkedList* tileBag, LinkedList* boxLid, Player* player1, 
        Player* player2, Factory factories[], std::vector<TilePtr>& centerOfTable);

void readLinkedList(LinkedList* list, std::string line);

void readVector(std::vector<TilePtr>& centerOfTable, std::string line);

void readPlayer(Player* player, std::vector<std::string>& lines, int* index);

void readFactory(Factory factory, std::string line);

#endif // UTILITY_H
