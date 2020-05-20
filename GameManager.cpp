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
    this->table = new Table();
    this->calculator = new ScoreCalculator();
    this->roundCount = 1;
}

GameManager::GameManager(std::string player1Name, std::string player2Name) {
    this->player1 = new Player(player1Name, 1);
    this->player2 = new Player(player2Name, 2);
    currentPlayerID = player1->getID();
    this->table = new Table();
    this->calculator = new ScoreCalculator();
    this->roundCount = 1;
}

GameManager::~GameManager() {
    delete player1;
    delete player2;
    delete table;
    delete calculator;
}

void GameManager::startGame(bool isNewGame) {
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
}

void GameManager::commenceEndOfGame() {
    calculator->calculateScoreEndOfGame(player1);
    calculator->calculateScoreEndOfGame(player2);

    std::cout << "=== GAME OVER ===" << std::endl;
    player1->toString();
    player2->toString();
    showWinner();
}

bool GameManager::loadGame(std::string filename) {
    bool isLoaded = true;

    std::ifstream inFile;
    inFile.open(filename);

    if(inFile.fail()) {
        isLoaded = false;
    } else {
        readGame(inFile, table, &currentPlayerID, player1, player2);
        inFile.close();
        std::cout << "Azul game successfully loaded" << std::endl;
    }
    return isLoaded;
}

bool GameManager::saveGame(std::string input) {
    std::stringstream saveGame(input);
    std::string command;
    std::string savePath;
    bool saved = false;
    if(saveGame >> command >> savePath) {
        std::ofstream os;
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
        std::cout << "=== END OF ROUND ===" << std::endl;
        commenceEndOfRound(player1);
        commenceEndOfRound(player2);
        endRound = isEOF;
    }

    return endRound;
    
}

void GameManager::commenceEndOfRound(Player* player) {
    // Move tiles from patternLines to Wall and Box Lid
    int addScore = moveTilesFromPatternLines(player);

    // Calculate score and of round
    int score = calculator->calculateScoreEachRound(player, addScore);

    Board* board = player->getBoard();
    unsigned int floorLineLength = board->getFloorLineLength();
    LinkedList* boxLid = table->getBoxLid();
    LinkedList* tileBag = table->getTileBag();
    std::array<Tile, FLOOR_LINE_SIZE>& floorLine = board->getFloorLine();

    // Clear floor line after each round
    for(unsigned int index = 0; index != floorLineLength; index++) {
        Tile tile = floorLine[index];
        if(tile == FIRST_PLAYER) {
            tileBag->addFront(tile);
        } else if(tile != FIRST_PLAYER && tile != NO_TILE) {
            boxLid->addBack(tile);
        }
    }
    board->clearFloorLine();

    // Print player's board and their updating points
    printBoard(std::cout, board->getWall(), board->getPatternLines(), board->getFloorLine(), board->getFloorLineLength());
        
    std::cout << player->getName() << " gets " << score << " from round " << roundCount << "." << std::endl;
    std::cout << "Total score for " << player->getName() << ": " << player->getPoints() << std::endl;
}

void GameManager::printTableAndBoard(Player* player) {

    Board* board = player->getBoard();

    std::cout << std::endl;
    std::cout << "TURN FOR PLAYER: " << player->getName() << std::endl;

    std::cout << "Center of Table (Factory 0): " << std::endl;
    printCenter(std::cout, table->getCenter());

    std::cout << "Factories (From 1 to 5): " << std::endl;
    printFactory(std::cout, table->getFactories());
    std::cout << std::endl;

    std::cout << "Mosaic for " << player->getName() << ":" << std::endl;
    printBoard(std::cout, board->getWall(), board->getPatternLines(), board->getFloorLine(), board->getFloorLineLength());
}

bool GameManager::commenceTurn(Player* player) {

    std::cout << USER_PROMPT << " ";
    std::string input;
    bool isTurnFinished = false;
    bool isEOF = false;
    
    while(!isTurnFinished && getline(std::cin, input)) {

        std::string typeOfCommand = input.substr(0, 4);

        if(typeOfCommand == COMMAND_TURN && playerTurn(player, input)) {
            std::cout << "Turn successful." << std::endl;
            isTurnFinished = true;
        } else if(typeOfCommand == COMMAND_SAVE && saveGame(input)) {
            std::cout << "Please continue your turn" << std::endl;
        } else if(typeOfCommand != COMMAND_TURN && typeOfCommand != COMMAND_SAVE) {
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

    if(!(playerTurn >> command >> factoryChoice >> colourChoice >> patternLineChoice)) {
        std::cout << "Invalid turn command" << std::endl;
        isTurnValid = false;
    } else {
        isTurnValid = promptForFactoryChoice(factoryChoice, colourChoice) 
            && promptForPatternLineChoice(player, patternLineChoice, colourChoice);
    }

    if(isTurnValid) {
        takeTiles(factoryChoice, colourChoice);
        int tilesPlaced = 0;

        for(int i = 0; i != FACTORY_SIZE; ++i) {
            if(table->getChosenFactory()[i] == colourChoice &&
               tilesPlaced < patternLineChoice) {

                player->getBoard()->addPatternLines(patternLineChoice-1, tilesPlaced, colourChoice);
                ++tilesPlaced;
            } else {
                table->getCenter()->addTile(table->getChosenFactory()[i]);
            }
        }

        table->clearChosenFactory();

    } 

    return isTurnValid;
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
    if(player->getBoard()->findColourInBoard(colourChoice, patternLineChoice)) {
        std::cout << "Invalid choice of pattern lines" << std::endl;
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
    for(int patternLineIndex = 0; patternLineIndex != PATTERN_LINES_SIZE; patternLineIndex++) {
        if(board->isPatternLinesFilled(patternLineIndex)) {
            Tile tile = board->removeFromPatternLines(patternLineIndex);
            for(int tileIndex = 0; tileIndex != (patternLineIndex+1); tileIndex++) {
                if(tileIndex != patternLineIndex) {
                    table->getBoxLid()->addBack(tile);
                } else {
                    int colPos = board->addWall(patternLineIndex, tile);
                    score += calculator->calculateScoreFromWall(board->getWall(), colPos, patternLineIndex);
                }
            }
        }
    }
    return score;
}

void GameManager::moveTilesToPatternLines(Player* player) {
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
        std::cout << "Victory is shared for " << player1->getName() << " and " << player2->getName() << "!" << std::endl;
    }
}