
<<<<<<< HEAD
#ifndef UTILITY_H
#define UTILITY_H

#include "LinkedList.h"
#include "Player.h"
#include "Board.h"

Colour readColour(char c);

void printGame(std::ostream& outStream, LinkedList* tileBag, LinkedList* boxLid, Player* player1, 
        Player* player2, Factory factories[], std::vector<TilePtr>& centerOfTable);

void printFactory(std::ostream& outStream, Factory factories[]);

void printCenterOfTable(std::ostream& outStream, std::vector<TilePtr>& centerOfTable);

void printPlayer(std::ostream& outStream, Player* player);

void printBoard(std::ostream& outStream, Board* board);

void printFloorLine(std::ostream& outStream, TilePtr* floorLine, int size);

void printWall(std::ostream& outStream, Wall& wall);

void printPatternLines(std::ostream& outStream);

void printLinkedList(std::ostream& outStream, LinkedList* list);

void readGame(std::istream& inStream, LinkedList* tileBag, LinkedList* boxLid, Player* player1, 
        Player* player2, Factory factories[], std::vector<TilePtr>& centerOfTable);

void readLinkedList(std::istream& inStream, LinkedList* list, std::string& line);

#endif // UTILITY_H
=======

#ifndef UTILITY_H
#define UTILITY_H

#define STUDENT_CREDITS_LENGTH 3
#define USER_PROMPT '<'

enum Option {
    Option1,
    Option2,
    Option3,
    Option4,
    OptionInvalid
};

#define RED            'R'
#define YELLOW         'Y'
#define DARK_BLUE      'B'
#define LIGHT_BLUE     'L'
#define BLACK          'U'
#define FIRST_PLAYER   'F'
#define NO_TILE        '.'

#endif // UTILITY_H
>>>>>>> master
