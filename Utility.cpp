#include "Utility.h"
#include <fstream>
#include <iostream>

void printGame(std::ostream& outStream, Table* table, int currentPlayerID,
        Player* player1, Player* player2) {

    outStream << "# ---SAVE BEGINS---" << "\n" << std::endl;

    outStream << "# Board Id" << "\n" << player1->getBoard()->getBoardId() << "\n\n";

    outStream << "# Tile Bag" << std::endl;
    printLinkedList(outStream, table->getTileBag());
    
    outStream << "\n" << "# Box Lid" << std::endl;
    printLinkedList(outStream, table->getBoxLid());
    
    outStream << "\n" << "# Factories" << std::endl;
    printFactoryToFile(outStream, table->getFactories());   

    outStream << "\n" << "# Centre of Table" << std::endl;
    printCenterToFile(outStream, table->getCenter());
    
    outStream << "\n" << "# Seed for Program" << "\n" << table->getSeedNumber() << "\n\n";

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
            read = false;
        } else if(boardId == ADVANCED_6TILE_BOARD && size != NUM_LINES_6TILE_BOARD) {
            read = false;
        } else if((boardId == REGULAR_BOARD || boardId == GREY_BOARD) 
                && size != NUM_LINES_5TILE_BOARD) {
            read = false;
        } else {
            while(index != size && read) {
                LinkedList* tileBag = table->getTileBag();
                LinkedList* boxLid = table->getBoxLid();
                read = readLinkedList(tileBag, lines[++index], boardId);

                if(read) {
                    read = readLinkedList(boxLid, lines[++index], boardId);
                    if(read && tileBag->size() == 0 && boxLid->size() == 0) {
                        read = false;
                    }
                }
                if(read) {
                    Factory* factory = table->getFactories();
                    int i = 0;
                    while (read && i < WALL_DIM) {
                        read = readFactory(factory[i], lines[++index], boardId);
                        i++;
                    }
                    if(read) {
                        read = readCenter(table->getCenter(), lines[++index], boardId);
                    }
                    if(read) {
                        try {
                            table->setSeedNumber(std::stoi(lines[++index]));
                        } catch (const std::invalid_argument&) {
                            read = false;
                        } catch (const std::out_of_range&) {
                            read = false;
                        }
                    }
                    if(read) {
                        try {
                            *currentPlayerID = std::stoi(lines[++index]);
                            if(!isValidId(*currentPlayerID)) {
                                read = false;
                            }
                        } catch (const std::invalid_argument&) {
                            read = false;
                        } catch (const std::out_of_range&) {
                            read = false;
                        }   
                        if(read) {
                            read = readPlayer(player1, lines, &index, boardId);
                            if(read) {
                                read = readPlayer(player2, lines, &index, boardId);
                                index++;
                            }
                            if(read && player1->getID() == player2->getID()) {
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

bool readLinkedList(LinkedList* list, std::string line, int boardId) {
    list->clear();
    int size = line.length();
    bool valid = true;
    if(line[0] != EMPTY_COLLECTION) {
        for(int i = 0; i != size; i++) {
            Tile tile = line[i];
            if(isTileValid(boardId, tile)) {
                list->addBack(tile); 
            } else if(tile != NO_TILE) {
                valid = false;
            }
        }
    }
    return valid;
}

bool readFactory(Factory factory, std::string line, int boardId) {    
    int size = line.length();
    bool valid = true;
    // If tile data exists, read it.
    if(line[0] != EMPTY_COLLECTION) {        
        for(int i = 0; i  != size; i++) {
            Tile tile = line[i];
            if(isTileValid(boardId, tile) || tile == NO_TILE) {
                factory[i] = line[i];
            } else {
                valid = false;
            }
        }
    } else {
        // If no tile data exists, populate factories with NO_TILE char.
        for (int i = 0; i != FACTORY_SIZE; i++) {
            factory[i] = NO_TILE;
        }
    }  
    return valid; 
}

bool readCenter(Vector* centerOfTable, std::string line, int boardId) {
    centerOfTable->clear();
    int size = line.length();
    bool valid = true;
    if(line[0] != EMPTY_COLLECTION) {
        for(int i = 0; i != size; i++) {
            Tile tile = line[i];
            if(isTileValid(boardId, tile) || tile == FIRST_PLAYER) {
                centerOfTable->add(tile);  
            } else if(tile != NO_TILE) {
                valid = false;
            }
        }
    }
    return valid;
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
            } else if(id == AIPLAYER_ID && boardId == GREY_BOARD) {
                read = false;
            } else {
                player->setId(id);
            }
        } catch (const std::invalid_argument&) {
            read = false;
        } catch (const std::out_of_range&) {
            read = false;
        }
        if(read) {
            delete player->getBoard();
            player->createBoard(boardId);
            read = readBoard(lines, i, player->getBoard());
        }
    }
    return read;
}

bool readBoard(std::vector<std::string>& lines, int* i, AbstractBoard* board) {

    int boardSize = board->getBoardSize();
    int boardId = board->getBoardId();
    int index = *i;
    bool valid = true;

    for(int row = 0; row != boardSize; row++) {
        int size = lines[++index].length();
        for(int col = 0; col != size; col++) {

            if (lines[index][col] != EMPTY_COLLECTION) {
                Tile tile = lines[index][col];
                if(isTileValid(boardId, tile)) {
                    board->addPatternLines(row, col, tile);
                } else if(tile == NO_TILE) {
                    board->addPatternLines(row, col, NO_TILE);
                } else {
                    valid = false;
                }
            }
        }
    }
    if(valid) {
        for(int row = 0; row != boardSize; row++) {
            int size = lines[++index].length();
            for(int col = 0; col != size; col++) {
                char tile = lines[index][col];
                if(isTileValid(boardId, tile)) {
                    board->addWall(row, col, tile);
                } else if(tile != NO_TILE) {
                    valid = false;
                }
            }
        }
    }
    if(valid) {
        board->clearFloorLine();
        int size = lines[++index].length();
        if(lines[index][0] != EMPTY_COLLECTION) {
            for(int pos = 0; pos != size; pos++) {
                Tile tile = lines[index][pos];
                if(isTileValid(boardId, tile) || tile == FIRST_PLAYER) {
                    board->addFloorLine(tile);
                } else if(tile != NO_TILE) {
                    valid = false;
                }
            }
        }
    }

    *i = index;
    return valid;
}

void printBoard(std::ostream& outStream, std::string playerName, Wall wall, 
        Tile** patternLines, Tile* floorLine, int length, int boardSize) {
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

bool isTileValid(int boardId, Tile tile) {
    bool isValid = true;
    if(tile != RED && tile != YELLOW && tile != DARK_BLUE     
            && tile != LIGHT_BLUE && tile != BLACK) {
        if(boardId == REGULAR_BOARD || boardId == GREY_BOARD) {
            isValid = false;
        } else if(boardId == ADVANCED_6TILE_BOARD && tile != ORANGE) {
            isValid = false;
        }
    }
    return isValid;
}