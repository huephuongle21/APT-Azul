#include "Utility.h"
#include <vector>
#include <fstream>
#include <iostream>

Colour readColour(char c) {
    Colour colour = RED;
    if(c == 'R') {
        colour = RED;
    } else if (c == 'Y') {
        colour = YELLOW;
    } else if (c == 'B') {
        colour = DARK_BLUE;
    } else if (c == 'L') {
        colour = LIGHT_BLUE;
    } else if (c == 'U') {
        colour = BLACK;
    }
    return colour;
}

void printGame(std::ostream& outStream, LinkedList* tileBag, LinkedList* boxLid, Player* player1, 
        Player* player2, Factory factories[], std::vector<TilePtr>& centerOfTable) {

    outStream << "#Tile Bag" << std::endl;
    printLinkedList(outStream, tileBag);

    outStream << "#Box Lid" << std::endl;
    printLinkedList(outStream, boxLid);

    outStream << "#Factory" << std::endl;
    printFactory(outStream, factories);

    outStream << "#Center Of Table" << std::endl;
    printCenterOfTable(outStream, centerOfTable);

    outStream << "#Random number" << std::endl;

    outStream << "#Player1" << std::endl;
    printPlayer(outStream, player1);

    outStream << "#Player2" << std::endl;
    printPlayer(outStream, player2);    
}

void printLinkedList(std::ostream& outStream, LinkedList* list) {
    int length = list->size();
   if(length == 0) {
      outStream << '_';
   } else {
      for(int i = 0; i != length; i++) {
        outStream << list->get(i)->getColourByChar();
      }
   }
   outStream << std::endl;
}

void printFactory(std::ostream& outStream, Factory factories[]) {
    for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j != FACTORY_SIZE; j++) {
            if(factories[i][j] == nullptr) {
                outStream << NO_TILE;
            } else {
                outStream << factories[i][j]->getColourByChar();
            }
        } 
        outStream << std::endl;
    }               
}

void printCenterOfTable(std::ostream& outStream, std::vector<TilePtr>& centerOfTable) {
    int size = centerOfTable.size();
    if(size == 0) {
        outStream << "_";
    } else {
        for(TilePtr tile : centerOfTable) {
            outStream << tile->getColourByChar();
        }
    }
    outStream << std::endl;
}

void printPlayer(std::ostream& outStream, Player* player) {
    std::string name = player->getName();
    int point = player->getPoint();
    bool current = player->isCurrent();
    outStream << name << "\n" << point << "\n" << (current ? "T" : "F") << std::endl;
    printBoard(outStream, player->getBoard());
}

void printBoard(std::ostream& outStream, Board* board) {
    printPatternLines(outStream);
    printWall(outStream, board->getWall());
    printFloorLine(outStream, board->getFloor(), board->getFloorSize());
}

void printFloorLine(std::ostream& outStream, TilePtr* floorLine, int size) {
    if(size == 0) {
        outStream << '_';
    } else {
        for(int i = 0; i != size; i++) {
            outStream << floorLine[i]->getColourByChar();
        }
    }
    outStream << std::endl;
}

void printWall(std::ostream& outStream, Wall& wall) {
    for(int i = 0; i < WALL_DIM; i++) {
        for(int j = 0; j < WALL_DIM; j++) {
            if(wall[i][j] == nullptr) {
                outStream << NO_TILE;
            } else {
                outStream << wall[i][j]->getColourByChar();
            }
        }
        outStream << std::endl;
    }
    outStream << std::endl;
}

void printPatternLines(std::ostream& outStream) {
    
}

void readGame(std::istream& inStream, LinkedList* tileBag, LinkedList* boxLid, Player* player1, 
        Player* player2, Factory factories[], std::vector<TilePtr>& centerOfTable) {

    std::string line;    
    while(!inStream.eof() && std::getline(inStream, line)) {
        if(line == "#Tile Bag") {
            std::getline(inStream, line);
            readLinkedList(inStream, tileBag, line);
        } else if(line == "#Box Lid") {
            std::getline(inStream, line);
            readLinkedList(inStream, boxLid, line);
        } else if(line == "#Factory") {
            
        } else if(line == "#Center Of Table") {
           
        } else if(line == "#Random number") {

        } else if(line == "#Player1") {

        } else if(line == "#Player2") {

        } 
    } 
}

void readLinkedList(std::istream& inStream, LinkedList* list, std::string& line) {
    char c;
    while(inStream >> c && c != '_') {
        list->addBack(new Tile(readColour(c)));
    }
}
