#ifndef UTILITY_H
#define UTILITY_H

#include "LinkedList.h"
#include "Player.h"
#include "AbstractBoard.h"
#include "Vector.h"
#include "Table.h"

void printGame(std::ostream& outStream, Table* table, int currentPlayerID, 
        Player* player1, Player* player2);

void printLinkedList(std::ostream& outStream, LinkedList* list);

void printFactory(std::ostream& outStream, Tile factory[]);

void printFactoryToFile(std::ostream& outStream, Factory* factories);

void printCenterToFile(std::ostream& outStream, Vector* vector);

void printCenter(std::ostream& outStream, Vector* vector);

void printPlayer(std::ostream& outStream, Player* player);

// Print board to the file
void printBoard(std::ostream& outStream, AbstractBoard* board);

void printPatternLines(std::ostream& outStream, Tile** patternLines, int boardSize);

void printWall(std::ostream& outStream, Wall wall, int boardSize);

void printFloorLine(std::ostream& outStream, Tile* floorLine, int length);

bool readGame(std::istream& inStream, Table* table, int* currentPlayerID,
        Player* player1, Player* player2);

void readLinkedList(LinkedList* list, std::string line);

void readFactory(Factory factory, std::string line);

void readCenter(Vector* centerOfTable, std::string line);

bool readPlayer(Player* player, std::vector<std::string>& lines, int* index, int boardId);

void readBoard(std::vector<std::string>& lines, int* index, AbstractBoard* board);

// Print board during the game
void printBoard(std::ostream& outStream, std::string playerName, Wall wall, Tile** patternLines, 
        Tile* floorLine, int length, int boardSize);

std::string colour(char tile);

void printInstructions();

#endif // UTILITY_H
