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
    this->table = new Table(0);
    this->calculator = new ScoreCalculator();
    this->roundCount = 1;
}

GameManager::GameManager(std::string player1Name, std::string player2Name, int seed) {
    this->player1 = new Player(player1Name, 1);
    this->player2 = new Player(player2Name, 2);
    currentPlayerID = player1->getID();
    this->table = new Table(seed);
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

    std::cout << "Let's Play!" << "\n" << std::endl;
   
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
    calculator->calculateScoreEndOfGame(player1);
    calculator->calculateScoreEndOfGame(player2);
    std::cout << "=== GAME OVER ===" << "\n" << std::endl;
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
        std::cout << "File does not exist!" << std::endl;
        isLoaded = false;
    } else {
        if(readGame(inFile, table, &currentPlayerID, player1, player2)) {
            inFile.close();
            std::cout << "Azul game successfully loaded" << "\n" << std::endl;
        } else {
            std::cout << "File does not contain a valid game!" << std::endl;
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
            std::cout << "Could not create save." << std::endl;
        } else {
            printGame(os, table, currentPlayerID, player1, player2);
            os.close();

            std::cout << "Save successful!" << std::endl;
            std::cout << "Game saved as: '" << savePath << "'" << std::endl;
            saved = true;
        }   
    } else {
        std::cout << "Invalid save command" << std::endl;
    }     
    return saved; 
}

bool GameManager::commenceRound() {
    std::cout << "=== Start Round " << roundCount << " ===" << std::endl;
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
        // Check for EOF. If false, check for end of round and swap players. Otherwise, end the round
        if(!isEOF) {
            endRound = isEndRound(); 
            swapCurrentPlayer();
        } else if(isEOF) {
            endRound = isEOF;
        } 
    }

    // If the round ends not because of EOF, commence end of round
    if(!isEOF) {
        std::cout << "=== END OF ROUND " << roundCount << " ===" << "\n" << std::endl;
        commenceEndOfRound(player1);
        commenceEndOfRound(player2);
        endRound = isEOF;
    }

    return endRound;
    
}

void GameManager::commenceEndOfRound(Player* player) {
    // Move tiles from patternLines to Wall and Box Lid
    int addScore = moveTilesFromPatternLines(player);

    // Calculate score end of round
    int score = calculator->calculateScoreEachRound(player, addScore);

    Board* board = player->getBoard();
    unsigned int floorLineLength = board->getFloorLineLength();
    LinkedList* boxLid = table->getBoxLid();
    Vector* center = table->getCenter();
    std::array<Tile, FLOOR_LINE_SIZE>& floorLine = board->getFloorLine();

    // Print player's board and their updating points
    std::cout << "Mosaic for " << player->getName() << ": " << "\n" << std::endl;
    printBoard(std::cout, board->getWall(), board->getPatternLines(), 
        board->getFloorLine(), board->getFloorLineLength());
        
    player->toStringEndOfRound(score, roundCount);
    std::cout << BREAK_LINE << std::endl;

    // Clear floor line after each round
    for(unsigned int index = 0; index != floorLineLength; index++) {
        Tile tile = floorLine[index];
        if(tile == FIRST_PLAYER) {
            center->addTile(tile);
            setCurrentPlayerID(player->getID());
        } else if(tile != FIRST_PLAYER && tile != NO_TILE) {
            boxLid->addFront(tile);
        }
    }
    board->clearFloorLine();
}

void GameManager::printTableAndBoard(Player* player) {

    Board* board = player->getBoard();

    std::cout << std::endl;
    std::cout << "TURN FOR PLAYER: " << player->getName() << "\n" << std::endl;

    std::cout << "Factories:" << std::endl;
    std::cout << "0: ";
    printCenter(std::cout, table->getCenter());

    Factory* factory = table->getFactories();
    for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
        std::cout << (i+1) << ": ";
        printFactory(std::cout, factory[i]);
    }
    std::cout << std::endl;

    std::cout << "Mosaic for " << player->getName() << ":" << "\n" << std::endl;
    printBoard(std::cout, board->getWall(), board->getPatternLines(), 
        board->getFloorLine(), board->getFloorLineLength());
}

bool GameManager::commenceTurn(Player* player) {

    std::cout << USER_PROMPT << " ";
    std::string input;
    bool isTurnFinished = false;
    bool isEOF = false;
    
    while(!isTurnFinished && getline(std::cin, input)) {

        std::string typeOfCommand = input.substr(0, 4);

        if(typeOfCommand == COMMAND_TURN && playerTurn(player, input)) {
            std::cout << "Turn successful." << "\n" << std::endl;
            isTurnFinished = true;
        } else if(input == COMMAND_EXIST) {
            isTurnFinished = true;
            isEOF = true;
        }  else if(typeOfCommand == COMMAND_SAVE && saveGame(input)) {
            std::cout << "Please continue your turn" << std::endl;
        } else if(typeOfCommand != COMMAND_TURN && typeOfCommand != COMMAND_SAVE 
                && input != COMMAND_EXIST) {
            std::cout << "Invalid Input." << "\n";
        }
        if(!isTurnFinished && !std::cin.eof()) {
            std::cout << USER_PROMPT << " ";
        } 
    }

    if(std::cin.eof()) {
        isEOF = true;
    }
        
    return isEOF;    
}

bool GameManager::isEndGame() {
    bool endGame = false;
    Board* board1 = player1->getBoard();
    Board* board2 = player2->getBoard();
    board1->completeRows();
    board2->completeRows();

    if(board1->getNumberOfRowsCompleted() > 0 || board2->getNumberOfRowsCompleted() > 0) {
        endGame = true;
    }
    return endGame;
}

bool GameManager::isEndRound() {
    bool isEmpty = true;
    if(!table->isCenterEmpty()) {
        isEmpty = false;
    } else {
        for(int i = 0; i != NUMBER_OF_FACTORY; i++) {
            if(!table->isFactoryEmpty(i)) {
                isEmpty = false;
            }
        }
    }
    return isEmpty;
}

bool GameManager::playerTurn(Player* player, std::string input) {
    std::stringstream playerTurn(input);
    std::string command;
    int factoryChoice;
    char colourChoice;
    int patternLineChoice;
    bool isTurnValid = true;

    if(input.length() != COMMAND_TURN_LENGTH 
            || !(playerTurn >> command >> factoryChoice >> colourChoice >> patternLineChoice)
            || command != COMMAND_TURN) {
        std::cout << "Invalid turn command" << std::endl;
        isTurnValid = false;
    } else {
        isTurnValid = promptForFactoryChoice(factoryChoice, colourChoice) 
            && promptForPatternLineChoice(player, patternLineChoice, colourChoice);
    }

    if(isTurnValid) {
        moveTilesToPatternLines(player, factoryChoice, patternLineChoice, colourChoice);
    } 

    return isTurnValid;
}

void GameManager::moveTilesToPatternLines(Player* player, int& factoryChoice, 
        int& patternLineChoice, char& colourChoice) {
    Board* board = player->getBoard();
    Tile** patternLines = board->getPatternLines();
    Vector* center = table->getCenter();
    Tile* chosenFactory = table->getChosenFactory();
    LinkedList* boxLid = table->getBoxLid();

    if(factoryChoice == 0) {
        moveTilesFromCenter(boxLid, patternLines, center, board, colourChoice, patternLineChoice);
    } else {
        moveTilesFromFactory(factoryChoice, colourChoice, patternLineChoice, board, boxLid, chosenFactory,
            patternLines, center);
    }
    table->clearChosenFactory();
}

void GameManager::moveTilesFromFactory(int& factoryChoice, char& colourChoice, int& patternLineChoice, 
        Board* board, LinkedList* boxLid, Tile* chosenFactory, Tile** patternLines, Vector* center) {
    int tilesPlaced = 0;
    takeTiles(factoryChoice, colourChoice);
    for(int i = 0; i != FACTORY_SIZE; ++i) {
        // If player chooses to add to floorline instead of pattern line
        Tile tile = chosenFactory[i];
        if(tile == colourChoice && patternLineChoice == FLOORLINE_POSITION) {
            if(board->getFloorLineLength() < FLOOR_LINE_SIZE) {
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
            center->addTile(tile);
        // If the pattern line is full, move the remaining tiles of that colour to the floor line.
        } else if(tile == colourChoice && tilesPlaced >= patternLineChoice) {
            if(board->getFloorLineLength() < FLOOR_LINE_SIZE) {
                board->addFloorLine(tile);
            } else {
                boxLid->addFront(tile);
            }
        }
    }
}

void GameManager::moveTilesFromCenter(LinkedList* boxLid, Tile** patternLines, Vector* center, 
        Board* board, char& colourChoice, int& patternLineChoice) {
    int tilesPlaced = 0;
    for(int i = 0; i != center->size(); ++i) {
        Tile tile = center->get(i);
        // Gives the first player tile to whoever takes from the centre of the board first
        if(tile == FIRST_PLAYER) {
            if(board->getFloorLineLength() == FLOOR_LINE_SIZE) {
                board->getFloorLine()[0] = tile;
            } else {
                board->addFloorLine(tile); 
            }
        }
        // If player chooses to place tiles in floor line.
        if(tile == colourChoice && patternLineChoice == FLOORLINE_POSITION) {
            if(board->getFloorLineLength() < FLOOR_LINE_SIZE) {
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
            if(board->getFloorLineLength() < FLOOR_LINE_SIZE) {
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
            center->removeTile(i);
        }
    }
}

bool GameManager::promptForFactoryChoice(int& factoryChoice, char& colourChoice) {
    bool isValid = false;
    if(promptForColourChoice(colourChoice)) {
        if(factoryChoice == 0 && table->findColourInCenter(colourChoice)) {
            isValid = true;
        } else if (1 <= factoryChoice && factoryChoice <= 5 
                && table->findColourInFactory(factoryChoice, colourChoice)) {
            isValid = true;  
        } else {
            std::cout << "Invalid choice of factory." << std::endl;
        }
    }
    return isValid;
}
    
bool GameManager::promptForColourChoice(char& colourChoice) {
    bool isValid = true;
    if(colourChoice != RED && colourChoice != YELLOW && colourChoice != DARK_BLUE     
            && colourChoice != LIGHT_BLUE && colourChoice != BLACK) {
        std::cout << "Invalid choice of colour." << std::endl;
        isValid = false;
    }
    return isValid;
}

bool GameManager::promptForPatternLineChoice(Player* player, int& patternLineChoice, char& colourChoice) {
    bool isValid = true;
    if(patternLineChoice == FLOORLINE_POSITION) {
        isValid = true;
    } else if (0 < patternLineChoice && patternLineChoice <= PATTERN_LINES_SIZE) {
        if(player->getBoard()->findColourInBoard(colourChoice, patternLineChoice)) {
            std::cout << "Invalid choice of pattern lines" << std::endl;
            isValid = false;
        }
    } else {
        std::cout << "Pattern lines choice varies from 1 to 6" << std::endl;
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
    Board* board = player->getBoard();
    LinkedList* boxLid = table->getBoxLid();
    for(int index = 0; index != PATTERN_LINES_SIZE; index++) {
        if(board->isPatternLinesFilled(index)) {
            Tile tile = board->removeFromPatternLines(index);
            for(int tileIndex = 0; tileIndex != (index+1); tileIndex++) {
                if(tileIndex != index) {
                    boxLid->addFront(tile);
                } else {
                    int colPos = board->addWall(index, tile);
                    score += calculator->calculateScoreFromWall(board->getWall(), colPos, index);
                }
            }
        }
    }
    return score;
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
        std::cout << "Player " << winner->getName() << " wins!" << std::endl;
    } else {
        std::cout << "Victory is shared for " << player1->getName() << " and " 
            << player2->getName() << "!" << std::endl;
    }
    std::cout << BREAK_LINE << std::endl;
}