#include "Utility.h"
#include <fstream>
#include <iostream>

void printGame(std::ostream& outStream, Table* table, int currentPlayerID,
        Player* player1, Player* player2) {

    outStream << "# ---SAVE BEGINS---" << "\n" << std::endl;

    outStream << "#Tile Bag" << std::endl;
    printLinkedList(outStream, table->getTileBag());

    outStream << "#Box Lid" << std::endl;
    printLinkedList(outStream, table->getBoxLid());

    outStream << "#Factories" << std::endl;
    printFactory(outStream, table->getFactories());

    outStream << "#Discards from Factories" << std::endl;
    printCenter(outStream, table->getCenter());

    outStream << "#Seed for Program" << "\n" << table->getSeedNumber() << std::endl;

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
            if(list->get(i) != NO_TILE) {
                outStream << list->get(i);
            }
        }
    }
    outStream << std::endl;
}

void printFactory(std::ostream& outStream, Factory factories[]) {
    for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j != FACTORY_SIZE; j++) {
            outStream << factories[i][j];
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
            if(centerOfTable->get(i) != NO_TILE) {
                outStream << centerOfTable->get(i);
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
    printFloorLine(outStream, board->getFloorLine(), board->getLength());
}

void printPatternLines(std::ostream& outStream, Tile** patternLines) {
    for(int i = 0; i != PATTERN_LINES_SIZE; i++) {
        for(int j = 0; j != (i+1); j++) {
            outStream << patternLines[i][j];
        }
        outStream << std::endl;
    }
}

// Need to update for lowercase and uppercase
void printWall(std::ostream& outStream, Wall& wall) {
    for(int i = 0; i < WALL_DIM; i++) {
        for(int j = 0; j < WALL_DIM; j++) {
            outStream << wall[i][j];
        }
        outStream << std::endl;
    }
}

void printFloorLine(std::ostream& outStream, std::array<Tile, FLOOR_LINE_SIZE>& floorLine, int length) {
    if(length == 0) {        
        outStream << EMPTY_COLLECTION;
    } else {
        for(int i = 0; i != length; i++) {
            if(floorLine[i] != NO_TILE) {
                outStream << floorLine[i];
            } 
        }
    }
    outStream << std::endl;
}

void readGame(std::istream& inStream, Table* table, int* currentPlayerID, Player* player1, Player* player2) {

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
        readLinkedList(table->getTileBag(), lines[index]);
        readLinkedList(table->getBoxLid(), lines[++index]);

        for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
            readFactory(table->getFactories()[i], lines[++index]);
        }

        readCenter(table->getCenter(), lines[++index]);

        table->setSeedNumber(std::stoi(lines[++index]));
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
            list->addBack(line[i]);  
        }
    }
}

void readFactory(Factory factory, std::string line) {
    int size = line.length();
    for(int i = 0; i  != size; i++) {
        factory[i] = line[i];
    }
}

void readCenter(Vector* centerOfTable, std::string line) {
    int size = line.length();
    if(line[0] != EMPTY_COLLECTION) {
        for(int i = 0; i != size; i++) {
            centerOfTable->addTile(line[i]);  
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
            board->addPatternLines(row, col, lines[index][col]);
        }
    }

    //upper and lower
    for(int row = 0; row != WALL_DIM; row++) {
        int size = lines[++index].length();
        for(int col = 0; col != size; col++) {
            board->addWall(row, col, lines[index][col]);
        }
    }
    
    int size = lines[++index].length();
    if(lines[index][0] != EMPTY_COLLECTION) {
        for(int pos = 0; pos != size; pos++) {
            board->addFloorLine(lines[index][pos]);
        }
    }

    *i = index;
}

void printBoard(std::ostream& outStream, Wall& wall, Tile** patternLines, std::array<Tile, FLOOR_LINE_SIZE>& floorLine, int length) {
    for(int row = 0; row != PATTERN_LINES_SIZE; row++) {
        for(int col = 0; col != PATTERN_LINES_SIZE; col++) {
            if((col + 1) >= (PATTERN_LINES_SIZE - row)) {
                outStream << patternLines[row][col-(PATTERN_LINES_SIZE-row-1)];               
            } else {
                outStream << " ";
            }

            // uppercase and lowercase
            if(col == PATTERN_LINES_SIZE - 1) {
                outStream << " || ";
                for(int wCol = 0; wCol != WALL_DIM; wCol++) {
                    outStream << wall[row][wCol];
                }
            }
        }
        outStream << "\n";
    }
    outStream << "broken: ";
    printFloorLine(outStream, floorLine, length);
}