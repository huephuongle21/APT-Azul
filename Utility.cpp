#include "Utility.h"
#include <fstream>
#include <iostream>

void printGame(std::ostream& outStream, Table* table, int currentPlayerID,
        Player* player1, Player* player2) {

    outStream << "# ---SAVE BEGINS---" << "\n" << std::endl;

    outStream << "# Tile Bag" << std::endl;
    printLinkedList(outStream, table->getTileBag());
    

    outStream << "\n" << "# Box Lid" << std::endl;
    printLinkedList(outStream, table->getBoxLid());
    
    Factory* factory = table->getFactories();
    outStream << "\n" << "# Factories" << std::endl;
    for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
        printFactory(outStream, factory[i]);
    }    

    outStream << "\n" << "# Centre of Table" << std::endl;
    printCenter(outStream, table->getCenter());
    

    outStream << "\n" << "# Seed for Program" << "\n" << table->getSeedNumber() << "\n" << std::endl;

    outStream << "# Current Player's ID" << "\n" << currentPlayerID << "\n" << std::endl;

    outStream << "# --- Player 1 ---" << "\n" << std::endl;
    printPlayer(outStream, player1);

    outStream << "# --- Player 2 ---" << "\n" << std::endl;
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

void printFactory(std::ostream& outStream, Tile factory[]) {
    for(int i = 0; i != FACTORY_SIZE; i++) {
        outStream << factory[i];
    }
    outStream << std::endl;
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
    int score = player->getPoints();

    outStream << "# Name" << "\n" << name << "\n" << std::endl;
    outStream << "# Score" << "\n" << score << "\n" << std::endl;
    
    printBoard(outStream, player->getBoard());
}

void printBoard(std::ostream& outStream, Board* board) {    
    
    outStream << "# Pattern Lines" << std::endl;
    printPatternLines(outStream, board->getPatternLines());

    outStream << "\n" << "# Wall" << std::endl;
    printWall(outStream, board->getWall());

    outStream << "\n" << "# Floor Line" << std::endl;
    printFloorLine(outStream, board->getFloorLine(), board->getFloorLineLength());

}

void printPatternLines(std::ostream& outStream, Tile** patternLines) {
    
    for(int i = 0; i != PATTERN_LINES_SIZE; i++) {
        for(int j = 0; j != (i+1); j++) {
            outStream << patternLines[i][j];
        }
        outStream << std::endl;
    }
}

void printWall(std::ostream& outStream, Wall& wall) {
    for(int i = 0; i < WALL_DIM; i++) {
        for(int j = 0; j < WALL_DIM; j++) {
            if(wall[i][j] >= 'a' && wall[i][j] <= 'z') {
                outStream << NO_TILE;
            } else {
                outStream << wall[i][j];
            }
        }
        outStream << std::endl;
    }
}

void printFloorLine(std::ostream& outStream, 
        std::array<Tile, FLOOR_LINE_SIZE>& floorLine, unsigned int length) {

    if(length == 0) {        
        outStream << EMPTY_COLLECTION;
    } else {
        for(unsigned int i = 0; i != length; i++) {
            if(floorLine[i] != NO_TILE) {
                outStream << floorLine[i];
            } 
        }
    }
    outStream << "\n" << std::endl;
}

bool readGame(std::istream& inStream, Table* table, int* currentPlayerID, 
        Player* player1, Player* player2) {
    bool read = true;
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
    if(size != NUM_LINES) {
        read = false;
    } else {
        while(index != size && read) {
            LinkedList* tileBag = table->getTileBag();
            readLinkedList(tileBag, lines[index]);
            if(tileBag->size() == 0) {
                read = false;
            }
            if(read) {
                readLinkedList(table->getBoxLid(), lines[++index]);

                Factory* factory = table->getFactories();
                for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
                    readFactory(factory[i], lines[++index]);
                }

                readCenter(table->getCenter(), lines[++index]);

                try {
                    table->setSeedNumber(std::stoi(lines[++index]));
                } catch (const std::invalid_argument&) {
                    read = false;
                } catch (const std::out_of_range&) {
                    read = false;
                }
                if(read) {
                    try {
                        *currentPlayerID = std::stoi(lines[++index]);
                        if(*currentPlayerID != 1 && *currentPlayerID != 2) {
                            read = false;
                        }
                    } catch (const std::invalid_argument&) {
                        read = false;
                    } catch (const std::out_of_range&) {
                        read = false;
                    }   
                    if(read) {
                        read = readPlayer(player1, lines, &index);
                        if(read) {
                            read = readPlayer(player2, lines, &index);
                            index++;
                        }
                    }
                }
            }
        }
    }
    return read;
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

    // If tile data exists, read it.
    if(line[0] != EMPTY_COLLECTION) {
        
        for(int i = 0; i  != size; i++) {
            factory[i] = line[i];
        }

    } else {

        // If no tile data exists, populate factories with NO_TILE char.
        for (int i = 0; i != FACTORY_SIZE; i++) {
            factory[i] = NO_TILE;
        }

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

bool readPlayer(Player* player, std::vector<std::string>& lines, int* i) {
    bool read = true;
    player->setName(lines[++(*i)]);
    try {
        player->addPoints(std::stoi(lines[++(*i)]));  
    } catch (const std::invalid_argument&) {
        read = false;
    } catch (const std::out_of_range&) {
        read = false;
    }
    if(read) {
        readBoard(lines, i, player->getBoard());
    }
    return read;
}

void readBoard(std::vector<std::string>& lines, int* i, Board* board) {

    int index = *i;

    for(int row = 0; row != PATTERN_LINES_SIZE; row++) {
        int size = lines[++index].length();
        for(int col = 0; col != size; col++) {

            if (lines[index][col] != EMPTY_COLLECTION) {
                board->addPatternLines(row, col, lines[index][col]);
            } else {
                board->addPatternLines(row, col, NO_TILE);
            }

        }
    }

    for(int row = 0; row != WALL_DIM; row++) {
        int size = lines[++index].length();
        for(int col = 0; col != size; col++) {
            char tile = lines[index][col];
            if(tile >= 'A' && tile <= 'Z') {
                board->addWall(row, col, tile);
            }
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

void printBoard(std::ostream& outStream, Wall& wall, Tile** patternLines, 
        std::array<Tile, FLOOR_LINE_SIZE>& floorLine, int length) {

    for(int row = 0; row != PATTERN_LINES_SIZE; row++) {
        std::cout << (row+1) << ": ";
        for(int col = 0; col != PATTERN_LINES_SIZE; col++) {
            if((col + 1) >= (PATTERN_LINES_SIZE - row)) {
                outStream << patternLines[row][PATTERN_LINES_SIZE - col - 1];               
            } else {
                outStream << " ";
            }

            if(col == PATTERN_LINES_SIZE - 1) {
                outStream << " || ";
                for(int wCol = 0; wCol != WALL_DIM; wCol++) {
                    char tile = wall[row][wCol];
                    if(tile >= 'a' && tile <= 'z') {
                        outStream << NO_TILE;
                    } else {
                        outStream << tile;
                    }
                }
            }
        }
        outStream << "\n";
    }

    outStream << "6: broken: ";
    printFloorLine(outStream, floorLine, length);
}