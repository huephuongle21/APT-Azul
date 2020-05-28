#include "GameManager.h"
#include "SetupManager.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>

GameManager::GameManager() {
    this->player1 = new Player(1);
    this->player2 = new Player(2);
    currentPlayerID = 0;
    this->table = new Table(0,0);
    this->calculator = new ScoreCalculator();
    this->roundCount = 1;
}

GameManager::GameManager(std::string player1Name, std::string player2Name, int seed, int boardId) {
    this->player1 = new Player(player1Name, 1, boardId);
    this->player2 = new Player(player2Name, 2, boardId);
    currentPlayerID = player1->getID();
    this->table = new Table(seed, boardId);
    this->calculator = new ScoreCalculator();
    this->roundCount = 1;
}

GameManager::~GameManager() {
    delete player1;
    delete player2;
    delete table;
    delete calculator;
}

bool GameManager::startGame(bool isNewGame) {
    if(isNewGame) {
        table->setupGame();
    }

    std::cout << "\n" << C_BLUE << "Let's Play!" << C_RESET << "\n" << std::endl;
   
    bool gameOver = false;
    bool isEOF = false;

    while(!gameOver) {
        isEOF = commenceRound();
        
        // If player enters EOF, end the game. Otherwise, check for end of game condition
        if(isEOF) {
            gameOver = isEOF;
        } else if(!isEOF) {
            bool endGame = isEndGame();
            if(!endGame) {
                // refill table if game doesn't end and start new round
                table->refillTable();
                roundCount++;
            }
            gameOver = endGame;
        }
    }
    // if game ends not because of EOF, commence end of game
    if(!isEOF) {
        commenceEndOfGame();
    }
    return isEOF;
}

void GameManager::commenceEndOfGame() {
    // Modify score end of game
    calculator->calculateScoreEndOfGame(player1);
    calculator->calculateScoreEndOfGame(player2);
    std::cout << "\n" << C_BROWN << "=== GAME OVER ===" << C_RESET << "\n" << std::endl;
    player1->toStringEndOfGame();
    player2->toStringEndOfGame();
    std::cout << std::endl;
    showWinner();
}

bool GameManager::loadGame(std::string loadPath) {
    bool isLoaded = true;

    std::ifstream inFile;
    inFile.open(loadPath);

    if(inFile.fail()) {
        std::cout << "\n" << C_RED << "File does not exist!" 
            << C_RESET << "\n" << std::endl;
        isLoaded = false;
    } else {
        if(readGame(inFile, table, &currentPlayerID, player1, player2)) {
            inFile.close();
            std::cout << "\n" << C_GREEN << "Azul game successfully loaded" 
                << C_RESET << "\n" << std::endl;
        } else {
            std::cout << "\n" << C_RED << "File does not contain a valid game!" 
                << C_RESET << "\n" << std::endl;
            isLoaded = false;
        }
    }
    return isLoaded;
}

bool GameManager::saveGame(std::string input) {
    std::stringstream splitInput(input);
    std::string argument;
    std::vector<std::string> saveCommand = {};
    bool saved = false;

    while(splitInput >> argument) {
        saveCommand.push_back(argument);
    }

    if(saveCommand.size() == COMMAND_SAVE_LENGTH && saveCommand.at(0) == COMMAND_SAVE) {
        std::ofstream os;
        std::string savePath = saveCommand.at(1);
        os.open(savePath);

        if(os.fail()) {
            std::cout << "\n" << C_RED << "Could not create save." 
                << C_RESET << "\n" << std::endl;
        } else {
            printGame(os, table, currentPlayerID, player1, player2);
            os.close();

            std::cout << "\n" << C_GREEN << "Save successful!" << C_RESET << std::endl;
            std::cout << "Game saved as: '" << C_GREEN << savePath 
                << C_RESET << "'" << std::endl;
            saved = true;
        }   
    } else {
        std::cout << "\n" << "Invalid save command" << std::endl;
        std::cout << C_RED << "save [save path]" << C_RESET << "\n" << std::endl;
    }     
    return saved; 
}

bool GameManager::commenceRound() {
    std::cout << C_BROWN << "=== Start Round " << roundCount << " ===" 
        << C_RESET << std::endl;
    bool endRound = false;
    bool isEOF = false;

    while(!endRound) {
        if(currentPlayerID == player1->getID()) {
            printTableAndBoard(player1);
            isEOF = commenceTurn(player1);
        } else {
            printTableAndBoard(player2);
            isEOF = commenceTurn(player2);
        }
        if(!isEOF) {
            endRound = isEndRound(); 
            swapCurrentPlayer();
        } else if(isEOF) {
            endRound = isEOF;
        } 
    }

    if(!isEOF) {
        std::cout << "\n" << C_BROWN << "=== END OF ROUND " << roundCount << " ===" 
            << C_RESET << "\n" << std::endl;
        isEOF = commenceEndOfRound(player1);
        if(!isEOF) {
            isEOF = commenceEndOfRound(player2);
        }
        endRound = isEOF;
    }

    return endRound;
    
}

bool GameManager::commenceEndOfRound(Player* player) {
    bool isEOF = false;
    AbstractBoard* board = player->getBoard();
    int floorLineLength = board->getFloorLineLength();
    LinkedList* boxLid = table->getBoxLid();
    Vector* center = table->getCenter();
    Tile* floorLine = board->getFloorLine();

    if(board->getBoardId() == GREY_BOARD) {
        printBoard(std::cout, player->getName(), board->getWall(), board->getPatternLines(), 
            floorLine, board->getFloorLineLength(), board->getBoardSize());
    }

    // Move tiles from patternLines to Wall and Box Lid
    int addScore = moveTilesFromPatternLines(player);
    if(addScore != -1) {
        // Calculate score end of round
        int score = calculator->calculateScoreEachRound(player, addScore);

        // Print player's board and their updating points
        printBoard(std::cout, player->getName(), board->getWall(), board->getPatternLines(), 
            floorLine, board->getFloorLineLength(), board->getBoardSize());
            
        player->toStringEndOfRound(score, roundCount);
        std::cout << C_GREEN << BREAK_LINE << C_RESET << "\n" << std::endl;

        // Clear floor line after each round
        for(int index = 0; index != floorLineLength; index++) {
            Tile tile = floorLine[index];
            if(tile == FIRST_PLAYER) {
                center->add(tile);
                setCurrentPlayerID(player->getID());
            } else if(tile != FIRST_PLAYER && tile != NO_TILE) {
                boxLid->addFront(tile);
            }
        }
        board->clearFloorLine();
    } else {
        isEOF = true;
    }
    return isEOF;
}

void GameManager::printTableAndBoard(Player* player) {

    AbstractBoard* board = player->getBoard();
    std::string name = player->getName();

    std::cout << std::endl;
    std::cout << "TURN FOR PLAYER: " << name << "\n" << std::endl;

    std::cout << "Factories:" << std::endl;
    std::cout << "0: ";
    printCenter(std::cout, table->getCenter());

    Factory* factory = table->getFactories();
    for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
        std::cout << (i+1) << ": ";
        printFactory(std::cout, factory[i]);
    }
    std::cout << std::endl;

    printBoard(std::cout, name, board->getWall(), board->getPatternLines(), 
        board->getFloorLine(), board->getFloorLineLength(), board->getBoardSize());
}

bool GameManager::commenceTurn(Player* player) {

    std::cout << C_LIGHTYELLOW << USER_PROMPT << C_RESET << " ";
    std::string input;
    bool isTurnFinished = false;
    bool isEOF = false;
    
    while(!isTurnFinished && getline(std::cin, input)) {

        std::string typeOfCommand = input.substr(0, 4);

        if(typeOfCommand == COMMAND_TURN && playerTurn(player, input)) {
            std::cout << "\n" << C_GREEN << "Turn successful." << C_RESET << "\n" << std::endl;
            isTurnFinished = true;
        } else if(input == COMMAND_EXIST) {
            isTurnFinished = true;
            isEOF = true;
        } else if(input == COMMAND_HELP) {
            printInstructions();
            std::cout << std::endl;
            std::cout << "\n" << "Please continue your turn" << "\n" << std::endl;
        } else if(typeOfCommand == COMMAND_SAVE && saveGame(input)) {
            std::cout << "\n" << "Please continue your turn" << "\n" << std::endl;
        } else if(typeOfCommand != COMMAND_TURN && typeOfCommand != COMMAND_SAVE 
                && input != COMMAND_EXIST) {
            std::cout << "\n" << "Invalid Input." << "\n" << std::endl;
        }
        if(!isTurnFinished && !std::cin.eof()) {
            std::cout << C_LIGHTYELLOW << USER_PROMPT << C_RESET << " ";
        } 
    }

    if(std::cin.eof()) {
        isEOF = true;
    }
        
    return isEOF;    
}

bool GameManager::isEndGame() {
    bool endGame = false;
    AbstractBoard* board1 = player1->getBoard();
    AbstractBoard* board2 = player2->getBoard();
    board1->completeRows(board1->getBoardSize());
    board2->completeRows(board2->getBoardSize());

    if(board1->getNumberOfRowsCompleted() > 0 || board2->getNumberOfRowsCompleted() > 0) {
        endGame = true;
    }
    return endGame;
}

bool GameManager::isEndRound() {
    bool isEmpty = true;
    if(!table->isCenterEmpty() || !table->isAllFactoriesEmpty()) {
        isEmpty = false;
    } 
    return isEmpty;
}

bool GameManager::playerTurn(Player* player, std::string input) {
    int boardId = player->getBoard()->getBoardId();
    int boardSize = player->getBoard()->getBoardSize();
    std::stringstream playerTurn(input);
    std::string command;
    int factoryChoice;
    char colourChoice;
    int patternLineChoice;
    bool isTurnValid = true;

    if(input.length() != COMMAND_TURN_LENGTH 
            || !(playerTurn >> command >> factoryChoice >> colourChoice >> patternLineChoice)
            || command != COMMAND_TURN) {
        std::cout << "\n" << "Invalid turn command" << "\n" << std::endl;
        std::cout << C_RED << "turn [factory choice] [colour choice] [pattern line choice]" 
            << C_RESET << "\n" << std::endl;
        isTurnValid = false;
    } else {
        isTurnValid = promptForFactoryChoice(factoryChoice, colourChoice, boardId) 
            && promptForPatternLineChoice(player, patternLineChoice, colourChoice, boardSize);
    }

    if(isTurnValid) {
        moveTilesToPatternLines(player, factoryChoice, patternLineChoice, colourChoice);
    } 

    return isTurnValid;
}

void GameManager::moveTilesToPatternLines(Player* player, int& factoryChoice, 
        int& patternLineChoice, char& colourChoice) {
    AbstractBoard* board = player->getBoard();
    Tile** patternLines = board->getPatternLines();
    Vector* center = table->getCenter();
    Tile* chosenFactory = table->getChosenFactory();
    LinkedList* boxLid = table->getBoxLid();
    int floorLineMaxSize = board->getFloorLineMaxSize();

    if(factoryChoice == 0) {
        moveTilesFromCenter(boxLid, patternLines, center, board, colourChoice, 
            patternLineChoice, floorLineMaxSize);
    } else {
        moveTilesFromFactory(factoryChoice, colourChoice, patternLineChoice, board, boxLid, 
            chosenFactory, patternLines, center, floorLineMaxSize);
    }
    table->clearChosenFactory();
}

void GameManager::moveTilesFromFactory(int& factoryChoice, char& colourChoice, 
        int& patternLineChoice, AbstractBoard* board, LinkedList* boxLid, Tile* chosenFactory, 
        Tile** patternLines, Vector* center, int floorLineMaxSize) {
    
    int tilesPlaced = 0;
    takeTiles(factoryChoice, colourChoice);
    for(int i = 0; i != FACTORY_SIZE; ++i) {
        // If player chooses to add to floorline instead of pattern line
        Tile tile = chosenFactory[i];
        if(tile == colourChoice && patternLineChoice == (floorLineMaxSize-1)) {
            if(board->getFloorLineLength() < floorLineMaxSize) {
                board->addFloorLine(tile);
            } else {
                boxLid->addFront(tile);
            }
        // If there's already placed tiles in the pattern line, keep moving to the next index.
        } else if(tile == colourChoice && tilesPlaced < patternLineChoice) {
            if(patternLines[patternLineChoice - 1][tilesPlaced] != NO_TILE) {
                while(patternLines[patternLineChoice - 1][tilesPlaced] != NO_TILE) {
                    ++tilesPlaced;
                }
                // When the first empty slot has been found place the tile
                board->addPatternLines(patternLineChoice - 1, tilesPlaced, tile);
                ++tilesPlaced;
            // Otherwise just place the tile in the first spot of the pattern line
            } else {
                board->addPatternLines(patternLineChoice - 1, tilesPlaced, tile);
                ++tilesPlaced;
            }       
        // If it's not the picked colour, move the tiles to the centre
        } else if(tile != colourChoice){
            center->add(tile);
        // If the pattern line is full, move the remaining tiles of that colour to the floor line.
        } else if(tile == colourChoice && tilesPlaced >= patternLineChoice) {
            if(board->getFloorLineLength() < floorLineMaxSize) {
                board->addFloorLine(tile);
            } else {
                boxLid->addFront(tile);
            }
        }
    }
}

void GameManager::moveTilesFromCenter(LinkedList* boxLid, Tile** patternLines, Vector* center, 
        AbstractBoard* board, char& colourChoice, int& patternLineChoice, int floorLineMaxSize) {
    int tilesPlaced = 0;
    for(unsigned int i = 0; i != center->size(); ++i) {
        Tile tile = center->get(i);
        // Gives the first player tile to whoever takes from the centre of the board first
        if(tile == FIRST_PLAYER) {
            if(board->getFloorLineLength() == floorLineMaxSize) {
                boxLid->addFront(board->getFloorLine()[0]);
                board->getFloorLine()[0] = tile;
            } else {
                board->addFloorLine(tile); 
            }
        }
        // If player chooses to place tiles in floor line.
        if(tile == colourChoice && patternLineChoice == (floorLineMaxSize-1)) {
            if(board->getFloorLineLength() < floorLineMaxSize) {
                board->addFloorLine(tile);
            } else {
                boxLid->addFront(tile);
            }
        // Same as above, move along if there's already tiles in the pattern line.
        } else if(tile == colourChoice && tilesPlaced < patternLineChoice) {
            if(patternLines[patternLineChoice - 1][tilesPlaced] != NO_TILE) {
                while(patternLines[patternLineChoice - 1][tilesPlaced] != NO_TILE) {
                    ++tilesPlaced;
                }
                board->addPatternLines(patternLineChoice - 1, tilesPlaced, tile);
                ++tilesPlaced;
            // Otherwise just place the tile in the first spot of the pattern line
            } else {
                board->addPatternLines(patternLineChoice - 1, tilesPlaced, tile);
                ++tilesPlaced;
            }
        // If the pattern line is full, move the remaining tiles of that colour to the floor line.
        } else if(tile == colourChoice && tilesPlaced >= patternLineChoice) {
            if(board->getFloorLineLength() < floorLineMaxSize) {
                board->addFloorLine(tile);
            } else {
                // If the floor line is full, add to the box
                boxLid->addFront(tile);
            }
        }
    }
    for(int i = center->size(); i >= 0; --i) {
        Tile tile = center->get(i);
        if(tile == colourChoice || tile == FIRST_PLAYER) {
            center->remove(i);
        }
    }
}

bool GameManager::promptForFactoryChoice(int& factoryChoice, char& colourChoice, int boardId) {
    bool isValid = false;
    if(promptForColourChoice(colourChoice, boardId)) {
        if(factoryChoice == 0 && table->findColourInCenter(colourChoice)) {
            isValid = true;
        } else if (1 <= factoryChoice && factoryChoice <= 5 
                && table->findColourInFactory(factoryChoice, colourChoice)) {
            isValid = true;  
        } else if (factoryChoice < 0 || factoryChoice > 5) {
            std::cout << "\n" << C_RED << "Factory choice varies from 0 to 5" 
                << C_RESET << "\n" << std::endl;
        }
    }
    return isValid;
}
    
bool GameManager::promptForColourChoice(char& colourChoice, int boardId) {
    bool isValid = true;
    if(colourChoice != RED && colourChoice != YELLOW && colourChoice != DARK_BLUE     
            && colourChoice != LIGHT_BLUE && colourChoice != BLACK) {
        if(boardId == REGULAR_BOARD || boardId == GREY_BOARD) {
            std::cout << "\n" << C_RED << "Invalid choice of colour. Should be "
                << "'R', 'Y', 'B', 'L' or 'B'" << C_RESET << "\n" << std::endl;
            isValid = false;
        } else if(boardId == ADVANCED_6TILE_BOARD && colourChoice != ORANGE) {
            std::cout << "\n" << C_RED << "Invalid choice of colour. Should be "
                << "'R', 'Y', 'B', 'L', 'B' or 'O'" << C_RESET << "\n" << std::endl;
            isValid = false;
        }
    }
    return isValid;
}

bool GameManager::promptForPatternLineChoice(Player* player, int& patternLineChoice, 
        char& colourChoice, int boardSize) {
    bool isValid = true;
    if(patternLineChoice == (boardSize+1)) {
        isValid = true;
    } else if (0 < patternLineChoice && patternLineChoice <= boardSize) {
        if(player->getBoard()->findColourInBoard(colourChoice, patternLineChoice, boardSize)) {
            std::cout << "\n" << C_RED << "Cannot place tiles to that pattern lines" 
                << C_RESET << "\n" << std::endl;
            isValid = false;
        }
    } else {
        std::cout << "\n" << C_RED << "Pattern lines choice varies from 1 to " << (boardSize+1) 
            << C_RESET << "\n " << std::endl;
        isValid = false;
    }
    return isValid;
}

void GameManager::takeTiles(int& factoryChoice, char& colour) {
    table->populateChosenFactory(factoryChoice);
    table->removeFactory(factoryChoice);
}

void GameManager::swapCurrentPlayer() {
    if(getCurrentPlayerID() == player1->getID()) {
        setCurrentPlayerID(player2->getID());
    } else {
        setCurrentPlayerID(player1->getID());
    }
}

int GameManager::getCurrentPlayerID() {
    return currentPlayerID;
}

void GameManager::setCurrentPlayerID(int currentPlayerID) {
    this->currentPlayerID = currentPlayerID;
}

Player* GameManager::getPlayer(int id) {
    if(id == 1) {
        return player1;
    } else {
        return player2;
    }
}

Table* GameManager::getTable() {
    return table;
}

ScoreCalculator* GameManager::getCalculator() {
    return calculator;
}

int GameManager::moveTilesFromPatternLines(Player* player) {
    int score = 0;
    AbstractBoard* board = player->getBoard();
    int boardId = board->getBoardId();
    int boardSize = board->getBoardSize();
    LinkedList* boxLid = table->getBoxLid();
    int colPos = 0;
    bool finished = false;
    while(colPos != -1 && !finished) {
        for(int index = 0; index != boardSize; index++) {
            if(board->isPatternLinesFilled(index)) {
                if(boardId == GREY_BOARD) {
                    Tile tile = board->getPatternLines()[index][0];
                    colPos = userPromptForWall(board, index, tile)-1;
                }
                if(colPos != -1) {
                    Tile tile = board->removeFromPatternLines(index);
                    for(int tileIndex = 0; tileIndex != (index+1); tileIndex++) {
                        if(tileIndex != index) {
                            boxLid->addFront(tile);
                        } else {
                            if(boardId == REGULAR_BOARD || boardId == ADVANCED_6TILE_BOARD) {
                                colPos = board->addWallForColorBoard(index, tile);
                            } else if(boardId == GREY_BOARD) {
                                board->addWall(index, colPos, tile);
                            }
                            score += calculator->calculateScoreFromWall(board->getWall(), 
                                colPos, index, boardSize);
                        }
                    }
                } else {
                    index = (boardSize-1);
                }
            }
            if(index == (boardSize-1)) {
                finished = true;
            }
        }
    }
    if(colPos == -1) {
        score = -1;
    }
    return score;
}

int GameManager::userPromptForWall(AbstractBoard* board, int index, Tile tile) {
    std::cout << "\n" << "Pick a position where you want to move the tile " << colour(tile) 
        << tile << C_RESET << " at pattern lines " << (index+1) << std::endl;
    std::cout << "\n" << "Enter a number from 1 to 5" << "\n" << std::endl;
    std::cout << C_LIGHTYELLOW << USER_PROMPT << C_RESET << " ";
    std::string input;
    bool isTurnFinished = false;
    bool isEOF = false;
    int colPos = 0;
    
    while(!isTurnFinished && getline(std::cin, input)) {
        if(input == COMMAND_EXIST) {
            isTurnFinished = true;
            isEOF = true;
        } else if(input == COMMAND_HELP) {
            std::cout << "\n" << "Enter from 1 to 5. Choose a empty position that does not" 
                << " have that colour in a corresponding row and column" << "\n" << std::endl;
        } else {
            try {
                colPos = std::stoi(input);
            } catch (const std::invalid_argument&) {
                
            } catch (const std::out_of_range&) {
                
            }
            if(0 < colPos && colPos <= board->getBoardSize()) {
                if(!board->isWallPositionFilled(index, colPos-1, tile)) {
                    std::cout << "\n" << C_GREEN << "Turn successfully" 
                        << C_RESET << std::endl;
                    isTurnFinished = true;
                } 
            } else {
                std::cout << "\n" << C_RED << "Please enter a number from 1 to 5" 
                    << C_RESET << "\n" << std::endl;
            }
        }
        if(!isTurnFinished) {
            std::cout << C_LIGHTYELLOW << USER_PROMPT << C_RESET << " ";
        }
    }

    if(std::cin.eof()) {
        isEOF = true;
    }
    if(isEOF) {
        colPos = -1;
    } 
    return colPos;
}

void GameManager::showWinner() {
    Player* winner = nullptr;
    int player1Points = player1->getPoints();
    int player2Points = player2->getPoints();
    int player1NumberOfRows = player1->getBoard()->getNumberOfRowsCompleted();
    int player2NumberOfRows = player2->getBoard()->getNumberOfRowsCompleted();

    if(player1Points > player2Points || 
            (player1Points == player2Points && player1NumberOfRows > player2NumberOfRows)) {
        winner = player1;
    } else if(player1Points < player2Points ||
            (player1Points == player2Points && player2NumberOfRows > player1NumberOfRows)) {
        winner = player2;
    } 
    if(winner != nullptr) {
        std::cout << C_REDORANGE << "Player " << winner->getName() 
            << " wins!" << C_RESET << "\n" << std::endl;
    } else {
        std::cout << C_REDORANGE << "Victory is shared for " << player1->getName() << " and " 
            << player2->getName() << "!" << C_RESET << "\n" << std::endl;
    }
    std::cout << C_GREEN << BREAK_LINE << C_RESET << std::endl;
}