#include "GameManager.h"
#include "Utility.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

GameManager::GameManager() {

    this->tileBag = new LinkedList();
    this->boxLid = new LinkedList();

    this->player1 = new Player("Alice", 1);
    this->player2 = new Player("Bob", 2);

    currentPlayerID = player1->getID();

    seedNumber = 10;

    for(int i = 0; i < NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j < FACTORY_SIZE; j++) {
            this->factories[i][j] = nullptr;
        }
    }

    centerOfTable = new Vector();

    tileBag->addBack(new Tile(RED));
    tileBag->addFront(new Tile(YELLOW));
    boxLid->addBack(new Tile(BLACK));
    boxLid->addFront(new Tile(YELLOW));

    factories[0][1] = new Tile(RED);
    factories[1][2] = new Tile(YELLOW);
    factories[3][4] = new Tile(DARK_BLUE);
    centerOfTable->addTile(new Tile(YELLOW));
    centerOfTable->addTile(new Tile(DARK_BLUE));


}

GameManager::~GameManager() {
    delete player1;
    delete player2;
    delete tileBag;
    delete boxLid;

    for(int i = 0; i < NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j < FACTORY_SIZE; j++) {
            this->factories[i][j] = nullptr;
            delete this->factories[i][j];
        }
    }

    delete centerOfTable;
}

void GameManager::newGame() {
    
}

void GameManager::loadGame(std::string filename) {
    std::string filename(filename);
    std::ifstream inFile;
    inFile.open(filename);

    if(inFile.fail()) {
        std::cout << "File does not exist" << std::endl;
    } else {
        readGame(inFile, tileBag, boxLid, &currentPlayerID, player1, player2, factories, centerOfTable, &seedNumber);
        inFile.close();
    }
    printGame(std::cout, tileBag, boxLid, currentPlayerID, player1, player2, factories, centerOfTable, seedNumber);
}

void GameManager::saveGame(std::string filename) {
    std::string filename(filename);
    std::ofstream outFile;
    outFile.open(filename);

    if(outFile.fail()) {
        std::cout << "File does not exist" << std::endl;
    } else {
        printGame(outFile, tileBag, boxLid, currentPlayerID, player1, player2, factories, centerOfTable, seedNumber);
        outFile.close();
    }   
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
