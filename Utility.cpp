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

void printGame(std::ostream& outStream, LinkedList* tileBag, LinkedList* boxLid, Player* player1, 
        Player* player2, Factory factories[], std::vector<TilePtr>& centerOfTable) {

    outStream << "#Tile Bag" << std::endl;
    printLinkedList(outStream, tileBag);

    outStream << "#Box Lid" << std::endl;
    printLinkedList(outStream, boxLid);

    outStream << "#Factories" << std::endl;
    printFactory(outStream, factories);

    outStream << "#Discards from Factories" << std::endl;
    printVector(outStream, centerOfTable);

    outStream << "#Seed for Program" << std::endl;

    outStream << "# --- Player 1 ---" << std::endl;
    printPlayer(outStream, player1);

    outStream << "# --- Player 2 ---" << std::endl;
    printPlayer(outStream, player2);    
}

void printLinkedList(std::ostream& outStream, LinkedList* list) {
    int length = list->size();
    if(length == 0) {
        outStream << EMPTY_COLLECTION;
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

void printVector(std::ostream& outStream, std::vector<TilePtr>& vector) {
    int size = vector.size();
    outStream << "<";
    if(size != 0) {
        for(TilePtr tile : vector) {
            outStream << tile->getColourByChar();
        }
    }
    outStream << ">" << std::endl;
}

void printPlayer(std::ostream& outStream, Player* player) {
    std::string name = player->getName();
    int point = player->getPoints();
    bool current = player->isCurrent();
    outStream << "# Name" << "\n" << name << "\n" << "# Score" << "\n" << point << "\n"
            << "# Is Current Player" << "\n" << (current ? "T" : "F") << std::endl;
    printBoard(outStream, player->getBoard());
}

void printBoard(std::ostream& outStream, Board* board) {    
    outStream << "# Pattern Lines" << std::endl;
    printPatternLines(outStream, board);
    outStream << "# Wall" << std::endl;
    printWall(outStream, board->getWall());
    outStream << "# Floor Line" << std::endl;
    printArray(outStream, board->getFloor(), FLOOR_LINE_SIZE);
}

void printArray(std::ostream& outStream, TilePtr* array, int size) {
    for(int i = 0; i != size; i++) {
        if(array[i] != nullptr) {
            outStream << array[i]->getColourByChar();
        } else {
            outStream << NO_TILE;
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
}

void printPatternLines(std::ostream& outStream, Board* board) {
    for(int i = 0; i != 5; i++) {
        for(int j = 0; j != (i+1); j++) {
            TilePtr tile = board->getPatternLines(i)[j];
            if(tile == nullptr) {
                outStream << NO_TILE;
            } else {
                outStream << tile->getColourByChar();
            }
        }
        outStream << std::endl;
    }
}

void readGame(std::istream& inStream, LinkedList* tileBag, LinkedList* boxLid, Player* player1, 
        Player* player2, Factory factories[], std::vector<TilePtr>& centerOfTable) {

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
    std::cout << size << " size" << std::endl;
    while(index != size) {
        readLinkedList(tileBag, lines[index]);
        readLinkedList(boxLid, lines[++index]);
        for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
            readFactory(factories[i], lines[++index]);
        }
        readVector(centerOfTable, lines[++index]);
        readPlayer(player1, lines, &index);
        readPlayer(player2, lines, &index);
        index++;
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

void readLinkedList(LinkedList* list, std::string line) {
    int size = line.length();
    for(int i = 0; i != size; i++) {
        std::cout << line[i] << std::endl;
        if(line[i] != EMPTY_COLLECTION) {
            list->addBack(new Tile(readColour(line[i])));
        }
    }
}

void readVector(std::vector<TilePtr>& centerOfTable, std::string line) {
    int size = line.length();
    for(int i = 0; i != size; i++) {
        if(line[i] != '<' || line[i] != '>') {
            centerOfTable.push_back(new Tile(readColour(line[i])));
        }
    }
}

void readPlayer(Player* player, std::vector<std::string>& lines, int* i) {
    player->setName(lines[++(*i)]);
    player->addPoints(stoi(lines[++(*i)]));
    player->setCurrent(lines[++(*i)] == "T" ? true : false);
   
    for(int j = 0; j != PATTERN_LINES_SIZE; j++) {
        int size = lines[++(*i)].length();
        for(int k = 0; k != size; k++) {
            if(lines[*i][k] != NO_TILE) {
                TilePtr tile = new Tile(readColour(lines[*i][k]));
                player->getBoard()->setPatternLines(j, k, tile);
            }
        }
    }

    for(int j = 0; j != WALL_DIM; j++) {
        int size = lines[++(*i)].length();
        for(int k = 0; k != size; k++) {
            if(lines[*i][k] != NO_TILE) {
                TilePtr tile = new Tile(readColour(lines[*i][k]));
                player->getBoard()->setPatternLines(j, k, tile);
            }
        }
    }
    
    int size = lines[++(*i)].length();
    for(int j = 0; j != size; j++) {
        if(lines[*i][j] != NO_TILE) {
            TilePtr tile = new Tile(readColour(lines[*i][j]));
            player->getBoard()->setFloor(j, tile);
        }
    }
}
