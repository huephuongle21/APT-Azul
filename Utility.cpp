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
    } else if (c == FIRST_PLAYER) {
        colour = WHITE;
    }
    return colour;
}

void printGame(std::ostream& outStream, LinkedList* tileBag, LinkedList* boxLid, int currentPlayerID,
        Player* player1, Player* player2, Factory factories[], Vector* centerOfTable, int seedNumber) {

    outStream << "# ---SAVE BEGINS---" << "\n" << std::endl;

    outStream << "#Tile Bag" << std::endl;
    printLinkedList(outStream, tileBag);

    outStream << "#Box Lid" << std::endl;
    printLinkedList(outStream, boxLid);

    outStream << "#Factories" << std::endl;
    printFactory(outStream, factories);

    outStream << "#Discards from Factories" << std::endl;
    printCenter(outStream, centerOfTable);

    outStream << "#Seed for Program" << "\n" << seedNumber << std::endl;

    outStream << "# Current Player's ID" << "\n" << currentPlayerID << std::endl;

    outStream << "# --- Player 1 ---" << std::endl;
    printPlayer(outStream, player1);

    outStream << "# --- Player 2 ---" << std::endl;
    printPlayer(outStream, player2);    

    outStream << "# ---SAVE ENDS---" << std::endl;
}

void printLinkedList(std::ostream& outStream, LinkedList* list) {
    int length = list->size();
    if(length == 0) {
        outStream << EMPTY_COLLECTION;
    } else {
        for(int i = 0; i != length; i++) {
            if(list->get(i) != nullptr) {
                outStream << list->get(i)->getColourByChar();
            }
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

void printCenter(std::ostream& outStream, Vector* centerOfTable) {
    int size = centerOfTable->size();
    if (size == 0) {
        outStream << EMPTY_COLLECTION;
    } else {
        for(int i = 0; i != size; i++) {
            if(centerOfTable->get(i) != nullptr) {
                outStream << centerOfTable->get(i)->getColourByChar();
            }
        }
    }
    outStream << std::endl;
}

void printPlayer(std::ostream& outStream, Player* player) {
    std::string name = player->getName();
    int point = player->getPoints();
    outStream << name << "\n" << point << std::endl;
    printBoard(outStream, player->getBoard());
}

void printBoard(std::ostream& outStream, Board* board) {    
    outStream << "# Pattern Lines" << std::endl;
    printPatternLines(outStream, board->getPatternLines());
    outStream << "# Wall" << std::endl;
    printWall(outStream, board->getWall());
    outStream << "# Floor Line" << std::endl;
    printFloorLine(outStream, board->getFloor());
}

void printPatternLines(std::ostream& outStream, TilePtr** patternLines) {
    for(int i = 0; i != PATTERN_LINES_SIZE; i++) {
        for(int j = 0; j != (i+1); j++) {
            if(patternLines[i][j] == nullptr) {
                outStream << NO_TILE;
            } else {
                outStream << patternLines[i][j]->getColourByChar();
            }
        }
        outStream << std::endl;
    }
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
}

void printFloorLine(std::ostream& outStream, Array* floorLine) {
    int size = floorLine->size();
    if(size == 0) {
        outStream << EMPTY_COLLECTION;
    } else {
        for(int i = 0; i != size; i++) {
            if(floorLine->get(i) != nullptr) {
                outStream << floorLine->get(i)->getColourByChar();
            } 
        }
    }
    outStream << std::endl;
}

void readGame(std::istream& inStream, LinkedList* tileBag, LinkedList* boxLid, int* currentPlayerID,
        Player* player1, Player* player2, Factory factories[], Vector* centerOfTable, int* seedNumber) {

    std::string line;  
    std::vector<std::string> lines;                             
    while (!inStream.eof() && std::getline(inStream, line))                          
    {
        if(line.length() > 0 && line[0] != '#') {
            lines.push_back(line);
        }                                  
    }  

    int index = 0;
    int size = lines.size();
    while(index != size) {
        readLinkedList(tileBag, lines[index]);
        readLinkedList(boxLid, lines[++index]);

        for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
            readFactory(factories[i], lines[++index]);
        }

        readCenter(centerOfTable, lines[++index]);

        *seedNumber = std::stoi(lines[++index]);
        *currentPlayerID = std::stoi(lines[++index]);

        readPlayer(player1, lines, &index);
        readPlayer(player2, lines, &index);

        index++;
    }
}

void readLinkedList(LinkedList* list, std::string line) {
    int size = line.length();
    if(line[0] != EMPTY_COLLECTION) {
        for(int i = 0; i != size; i++) {
            list->addBack(new Tile(readColour(line[i])));  
        }
    }
}

void readFactory(Factory factory, std::string line) {
    int size = line.length();
    for(int i = 0; i  != size; i++) {
        if(line[i] != NO_TILE) {
            factory[i] = new Tile(readColour(line[i]));
        }
    }
}

void readCenter(Vector* centerOfTable, std::string line) {
    int size = line.length();
    if(line[0] != EMPTY_COLLECTION) {
        for(int i = 0; i != size; i++) {
            centerOfTable->addTile(new Tile(readColour(line[i])));  
        }
    }
}

void readPlayer(Player* player, std::vector<std::string>& lines, int* i) {
    player->setName(lines[++(*i)]);
    player->addPoints(std::stoi(lines[++(*i)]));  

    readBoard(lines, i, player->getBoard());
}

void readBoard(std::vector<std::string>& lines, int* i, Board* board) {

    int index = *i;

    for(int row = 0; row != PATTERN_LINES_SIZE; row++) {
        int size = lines[++index].length();
        for(int col = 0; col != size; col++) {
            if(lines[index][col] != NO_TILE) {
                TilePtr tile = new Tile(readColour(lines[index][col]));
                board->addPatternLines(row, col, tile);
            }
        }
    }

    for(int row = 0; row != WALL_DIM; row++) {
        int size = lines[++index].length();
        for(int col = 0; col != size; col++) {
            if(lines[index][col] != NO_TILE) {
                TilePtr tile = new Tile(readColour(lines[index][col]));
                board->addWall(row, col, tile);
            }
        }
    }
    
    int size = lines[++index].length();
    if(lines[index][0] != EMPTY_COLLECTION) {
        for(int pos = 0; pos != size; pos++) {
            TilePtr tile = new Tile(readColour(lines[index][pos]));
            board->getFloor()->addTile(tile);
        }
    }

    *i = index;
}