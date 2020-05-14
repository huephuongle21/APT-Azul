
#ifndef UTILITY_H
#define UTILITY_H

#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "Vector.h"
#include "Table.h"

void printGame(std::ostream& outStream, Table* table, int currentPlayerID, 
        Player* player1, Player* player2);

void printFactory(std::ostream& outStream, Factory factories[]);

void printCenter(std::ostream& outStream, Vector* vector);

void printPlayer(std::ostream& outStream, Player* player);

void printBoard(std::ostream& outStream, Board* board);

void printFloorLine(std::ostream& outStream, std::array<char, FLOOR_LINE_SIZE>& floorLine, int length);

void printWall(std::ostream& outStream, Wall& wall);

void printPatternLines(std::ostream& outStream, char** patternLines);

void printLinkedList(std::ostream& outStream, LinkedList* list);

// Print board during the game
void printBoard(std::ostream& outStream, Wall& wall, char** patternLines, std::array<char, FLOOR_LINE_SIZE>& floorLine, int length);

void readGame(std::istream& inStream, Table* table, int* currentPlayerID,
        Player* player1, Player* player2);

void readLinkedList(LinkedList* list, std::string line);

void readCenter(Vector* centerOfTable, std::string line);

void readPlayer(Player* player, std::vector<std::string>& lines, int* index);

void readFactory(Factory factory, std::string line);

void readBoard(std::vector<std::string>& lines, int* index, Board* board);

#endif // UTILITY_H
