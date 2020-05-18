#include "GameManager.h"
#include "SetupManager.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>

GameManager::GameManager() {
    this->player1 = new Player();
    this->player2 = new Player();

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
        if(isEOF) {
            gameOver = isEOF;
        } else if(!isEOF) {
            bool endGame = isEndGame(player1, player2);
            if(!endGame) {
                table->refillTable();
                roundCount++;
            }
            gameOver = endGame;
        }
    }
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

bool GameManager::saveGame(std::string savePath) {

    bool saved = false;

    std::ofstream os;
    os.open(savePath);

    if (os.fail()) {
        std::cout << "Could not create save." << std::endl;
    } else {
        
        printGame(os, table, currentPlayerID, player1, player2);
        os.close();
        
        std::cout << "Save successful!" << std::endl;
        std::cout << "Game saved as: '" << savePath << "'" << std::endl;
        saved = true;
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

        if(!isEOF) {
            endRound = isEndRound(); 
            swapCurrentPlayer();
        } else if(isEOF) {
            endRound = isEOF;
        } 
    }

    if(!isEOF) {
        commenceEndOfRound(player1);
        commenceEndOfRound(player2);
        endRound = isEOF;
    }

    return endRound;
    
}

void GameManager::commenceEndOfRound(Player* player) {
    moveTilesFromPatternLines(player);
    int score = calculator->calculateScoreEachRound(player);

    printBoard(std::cout, player->getBoard()->getWall(), player->getBoard()->getPatternLines(), 
        player->getBoard()->getFloorLine(), player->getBoard()->getLength());
        
    std::cout << player->getName() << " gets " << score << " from round " << roundCount << "." << std::endl;
    std::cout << "Total score for " << player->getName() << ": " << player->getPoints() << std::endl;
}

void GameManager::printTableAndBoard(Player* player) {
    std::cout << std::endl;
    std::cout << "TURN FOR PLAYER: " << player->getName() << std::endl;

    std::cout << "Center of Table (Factory 0): " << std::endl;
    printCenter(std::cout, table->getCenter());

    std::cout << "Factories (From 1 to 5): " << std::endl;
    printFactory(std::cout, table->getFactories());
    std::cout << std::endl;

    std::cout << "Mosaic for " << player->getName() << ":" << std::endl;
    printBoard(std::cout, player->getBoard()->getWall(), player->getBoard()->getPatternLines(), 
        player->getBoard()->getFloorLine(), player->getBoard()->getLength());
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
        } else {
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

bool GameManager::isEndGame(Player* player1, Player* player2) {
    return false;
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
    playerTurn >> command >> factoryChoice >> colourChoice >> patternLineChoice;

    bool isTurnValid = promptForFactoryChoice(factoryChoice, colourChoice) 
        && promptForPatternLineChoice(player, patternLineChoice, colourChoice);

    if(isTurnValid) {
        takeTiles(factoryChoice, colourChoice);
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

void GameManager::moveTilesFromPatternLines(Player* player) {
    for(int patternLineIndex = 0; patternLineIndex != PATTERN_LINES_SIZE; patternLineIndex++) {
        if(player->getBoard()->isPatternLinesFilled(patternLineIndex)) {
            Tile tile = player->getBoard()->removeFromPatternLines(patternLineIndex);
            for(int tileIndex = 0; tileIndex != (patternLineIndex+1); tileIndex++) {
                if(tileIndex != patternLineIndex) {
                    table->getBoxLid()->addBack(tile);
                } else {
                    player->getBoard()->addWall(patternLineIndex, tile);
                }
            }
        }
    }
}
