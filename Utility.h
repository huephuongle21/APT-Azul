
#ifndef UTILITY_H
#define UTILITY_H

#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "Vector.h"
#include "Array.h"

Colour readColour(char c);

void printGame(std::ostream& outStream, LinkedList* tileBag, LinkedList* boxLid, int currentPlayerID, 
        Player* player1, Player* player2, Factory factories[], Vector* centerOfTable, int seedNumber);

void printFactory(std::ostream& outStream, Factory factories[]);

void printCenter(std::ostream& outStream, Vector* vector);

void printPlayer(std::ostream& outStream, Player* player);

void printBoard(std::ostream& outStream, Board* board);

void printFloorLine(std::ostream& outStream, Array* array);

void printWall(std::ostream& outStream, Wall& wall);

void printPatternLines(std::ostream& outStream, TilePtr** patternLines);

void printLinkedList(std::ostream& outStream, LinkedList* list);

void readGame(std::istream& inStream, LinkedList* tileBag, LinkedList* boxLid, int* currentPlayerID,
        Player* player1, Player* player2, Factory factories[], Vector* centerOfTable, int* seedNumber);

void readLinkedList(LinkedList* list, std::string line);

void readCenter(Vector* centerOfTable, std::string line);

void readPlayer(Player* player, std::vector<std::string>& lines, int* index);

void readFactory(Factory factory, std::string line);

void readBoard(std::vector<std::string>& lines, int* index, Board* board);

#endif // UTILITY_H
