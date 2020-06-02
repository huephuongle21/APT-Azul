#include "Utility.h"
#include <fstream>
#include <iostream>

void printGame(std::ostream& outStream, Table* table, int currentPlayerID,
        Player* player1, Player* player2) {

    outStream << "# ---SAVE BEGINS---" << "\n" << std::endl;

    outStream << "# Board Id" << "\n" << player1->getBoard()->getBoardId() << "\n" << std::endl;

    outStream << "# Tile Bag" << std::endl;
    printLinkedList(outStream, table->getTileBag());
    
    outStream << "\n" << "# Box Lid" << std::endl;
    printLinkedList(outStream, table->getBoxLid());
    
    outStream << "\n" << "# Factories" << std::endl;
    printFactoryToFile(outStream, table->getFactories());   

    outStream << "\n" << "# Centre of Table" << std::endl;
    printCenterToFile(outStream, table->getCenter());
    
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
        Tile tile = factory[i];
        outStream << colour(tile) << tile << C_RESET;
    }
    outStream << std::endl;
}

void printFactoryToFile(std::ostream& outStream, Factory* factories) {
    for(int i = 0; i != WALL_DIM; i++) {
        for(int j = 0; j != FACTORY_SIZE; j++) {
            outStream << factories[i][j];
        }
        outStream << std::endl;
    }
}

void printCenterToFile(std::ostream& outStream, Vector* centerOfTable) {
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

void printCenter(std::ostream& outStream, Vector* centerOfTable) {
    int size = centerOfTable->size();
    if(size != 0) {
        for(int i = 0; i != size; i++) {
            if(centerOfTable->get(i) != NO_TILE) {
                Tile tile = centerOfTable->get(i);
                outStream << colour(tile) << tile << C_RESET;
            }
        }
    }
    outStream << std::endl;
}

void printPlayer(std::ostream& outStream, Player* player) {

    std::string name = player->getName();
    int score = player->getPoints();
    int id = player->getID();

    outStream << "# Name" << "\n" << name << "\n" << std::endl;
    outStream << "# Score" << "\n" << score << "\n" << std::endl;
    outStream << "# Player ID" << "\n" << id << "\n" << std::endl;
    
    printBoard(outStream, player->getBoard());
}

void printBoard(std::ostream& outStream, AbstractBoard* board) {    
    int size = board->getBoardSize();
    outStream << "# Pattern Lines" << std::endl;
    printPatternLines(outStream, board->getPatternLines(), size);

    outStream << "\n" << "# Wall" << std::endl;
    printWall(outStream, board->getWall(), size);

    outStream << "\n" << "# Floor Line" << std::endl;
    printFloorLine(outStream, board->getFloorLine(), board->getFloorLineLength());

}

void printPatternLines(std::ostream& outStream, Tile** patternLines, int boardSize) {
    
    for(int i = 0; i != boardSize; i++) {
        for(int j = 0; j != (i+1); j++) {
            outStream << patternLines[i][j];
        }
        outStream << std::endl;
    }
}

void printWall(std::ostream& outStream, Wall wall, int boardSize) {
    for(int i = 0; i < boardSize; i++) {
        for(int j = 0; j < boardSize; j++) {
            Tile tile = wall[i][j];
            if((tile >= 'a' && tile <= 'z') || tile == NO_TILE) {
                outStream << NO_TILE;
            } else {
                outStream << wall[i][j];
            }
        }
        outStream << std::endl;
    }
}

void printFloorLine(std::ostream& outStream, Tile* floorLine, int length) {

    if(length == 0) {        
        outStream << EMPTY_COLLECTION;
    } else {
        for(int i = 0; i != length; i++) {
            if(floorLine[i] != NO_TILE) {
                Tile tile = floorLine[i];
                outStream << tile;
            } 
        }
    }
    outStream << "\n" << std::endl;
}

bool readGame(std::istream& inStream, Table* table, int* currentPlayerID, 
        Player* player1, Player* player2) {

    int boardId = 0; 
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
    try {
        boardId = std::stoi(lines[index]);
    } catch (const std::invalid_argument&) {
        read = false;
    } catch (const std::out_of_range&) {
        read = false;
    }
    if(read) {
        if(!isValidId(boardId)) {
            std::cout << "Invalid 1" << std::endl;
            read = false;
        } else if(boardId == ADVANCED_6TILE_BOARD && size != NUM_LINES_6TILE_BOARD) {
            std::cout << "Invalid 2" << std::endl;
            read = false;
        } else if((boardId == REGULAR_BOARD || boardId == GREY_BOARD) && size != NUM_LINES_5TILE_BOARD) {
            std::cout << "Invalid 3" << std::endl;
            read = false;
        } else {
            while(index != size && read) {
                LinkedList* tileBag = table->getTileBag();
                readLinkedList(tileBag, lines[++index]);

                LinkedList* boxLid = table->getBoxLid();
                readLinkedList(boxLid, lines[++index]);
                if(tileBag->size() == 0 && boxLid->size() == 0) {
                    std::cout << "Invalid 4" << std::endl;
                    read = false;
                }
                if(read) {
                    Factory* factory = table->getFactories();
                    for(int i = 0; i != WALL_DIM; i++) {
                        readFactory(factory[i], lines[++index]);
                    }

                    readCenter(table->getCenter(), lines[++index]);

                    try {
                        table->setSeedNumber(std::stoi(lines[++index]));
                    } catch (const std::invalid_argument&) {
                        std::cout << "Invalid 5" << std::endl;
                        read = false;
                    } catch (const std::out_of_range&) {
                        std::cout << "Invalid 6" << std::endl;
                        read = false;
                    }
                    if(read) {
                        try {
                            *currentPlayerID = std::stoi(lines[++index]);
                            if(!isValidId(*currentPlayerID)) {
                                std::cout << "Invalid 7" << std::endl;
                                read = false;
                            }
                        } catch (const std::invalid_argument&) {
                            std::cout << "Invalid 8" << std::endl;
                            read = false;
                        } catch (const std::out_of_range&) {
                            std::cout << "Invalid 9" << std::endl;
                            read = false;
                        }   
                        if(read) {
                            read = readPlayer(player1, lines, &index, boardId);
                            // if grey board and playerId = 3 => false
                            if(read) {
                                std::cout << "Invalid 10" << std::endl;
                                read = readPlayer(player2, lines, &index, boardId);
                                index++;
                            }
                            if(player1->getID() == player2->getID()) {
                                std::cout << "Invalid 11" << std::endl;
                                read = false;
                            }
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
            centerOfTable->add(line[i]);  
        }
    }
}

bool readPlayer(Player* player, std::vector<std::string>& lines, int* i, int boardId) {
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
        try {
            int id = std::stoi(lines[++(*i)]);  
            if(!isValidId(id)) {
                read = false;
            } else {
                player->setId(id);
            }
        } catch (const std::invalid_argument&) {
            read = false;
        } catch (const std::out_of_range&) {
            read = false;
        }
        player->createBoard(boardId);
        readBoard(lines, i, player->getBoard());
    }
    return read;
}

void readBoard(std::vector<std::string>& lines, int* i, AbstractBoard* board) {

    int boardSize = board->getBoardSize();

    int index = *i;

    for(int row = 0; row != boardSize; row++) {
        int size = lines[++index].length();
        for(int col = 0; col != size; col++) {

            if (lines[index][col] != EMPTY_COLLECTION) {
                board->addPatternLines(row, col, lines[index][col]);
            } else {
                board->addPatternLines(row, col, NO_TILE);
            }

        }
    }

    for(int row = 0; row != boardSize; row++) {
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

void printBoard(std::ostream& outStream, std::string playerName, Wall wall, Tile** patternLines, Tile* floorLine, int length, int boardSize) {
    std::cout << "Mosaic for " << playerName << ":" << "\n" << std::endl;
    for(int row = 0; row != boardSize; row++) {
        std::cout << (row+1) << ": ";
        for(int col = 0; col != boardSize; col++) {
            if((col + 1) >= (boardSize - row)) {
                Tile tile = patternLines[row][boardSize - col - 1];
                outStream << colour(tile) << tile << C_RESET;               
            } else {
                outStream << " ";
            }

            if(col == boardSize - 1) {
                outStream << C_MAGENTA << " || " << C_RESET;
                for(int wCol = 0; wCol != boardSize; wCol++) {
                    char tile = wall[row][wCol];
                    if(tile >= 'a' && tile <= 'z') {
                        outStream << colour(toupper(tile)) << NO_TILE << C_RESET;
                    } else if(tile == NO_TILE) {
                        outStream << C_GREY << NO_TILE << C_RESET;
                    } else {
                        outStream << colour(tile) << tile << C_RESET;
                    }
                }
            }
        }
        outStream << "\n";
    }

    outStream << "\n" << (boardSize+1) << ": broken: ";
    for(int i = 0; i != length; i++) {
        if(floorLine[i] != NO_TILE) {
            Tile tile = floorLine[i];
            outStream << colour(tile) << tile << C_RESET;
        } 
    }
    outStream << "\n\n";
}

std::string colour(char tile) {
    std::string colour = C_WHITE;
    if(tile == RED) {
        colour = C_RED;
    } else if(tile == YELLOW) {
        colour = C_YELLOW;
    } else if(tile == BLACK) {
        colour = C_BLACK;
    } else if(tile == LIGHT_BLUE) {
        colour = C_CYAN;
    } else if(tile == DARK_BLUE) {
        colour = C_BLUE;
    } else if(tile == ORANGE) {
        colour = C_ORANGE;
    }
    return colour;
}

void printInstructions() {

    std::string instructionsPath = "azul_guide.txt";

    std::ifstream ifs(instructionsPath);
    std::string line;
    
    while(getline(ifs, line)) {
        if(line[0] == '=') {
            std::cout << C_LIGHTYELLOW << line << C_RESET << '\n';
        } else {
            std::cout << line << '\n';
        }
    }
}

bool isValidId(int id) {
    bool valid = true;
    if(id != 1 && id != 2 && id != 3) {
        valid = false;
    }
    return valid;
}

void printValidCommand() {
    std::cout << "\n" << U_TIPS << " Valid command:" << "\n";
    std::cout << TURN << "\n" << SAVE << "\n" << COMMAND_HELP << "\n" 
        << COMMAND_EXIST << std::endl;
}