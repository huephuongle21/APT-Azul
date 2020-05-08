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



    for(int i = 0; i < NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j < FACTORY_SIZE; j++) {
            this->factories[i][j] = nullptr;
        }
    }

    this->centerOfTable = {};
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

    for(unsigned int i = 0; i < centerOfTable.size(); ++i) {
        delete centerOfTable[i];
    }
    centerOfTable.clear();
}

void GameManager::newGame() {
    
}

void GameManager::loadGame() {
    std::string filename("azul.txt");
    std::ifstream inFile;
    inFile.open(filename);

    if(inFile.fail()) {
        std::cout << "File does not exist" << std::endl;
    } else {
        readGame(inFile, tileBag, boxLid, player1, player2, factories, centerOfTable);
        inFile.close();
    }
}

void GameManager::saveGame() {
    std::string filename("azul.txt");
    std::ofstream outFile;
    outFile.open(filename);

    if(outFile.fail()) {
        std::cout << "File does not exist" << std::endl;
    } else {
        printGame(outFile, tileBag, boxLid, player1, player2, factories, centerOfTable);
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
