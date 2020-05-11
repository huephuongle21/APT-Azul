#include "GameManager.h"
#include "Utility.h"

#include <iostream>
#include <string>
#include <fstream>

GameManager::GameManager() {

    this->tileBag = new LinkedList();
    this->boxLid = new LinkedList();

    this->player1 = new Player("Alice", 1);
    this->player2 = new Player("Bob", 2);

    currentPlayerID = player1->getID();

    seedNumber = 10;

    for(int i = 0; i < NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j < FACTORY_SIZE; j++) {
            factories[i][j] = nullptr;
        }
    }

    centerOfTable = new Vector();

}

GameManager::~GameManager() {
    delete player1;
    delete player2;
    delete tileBag;
    delete boxLid;

    for(int i = 0; i < NUMBER_OF_FACTORY; i++) {
        for(int j = 0; j < FACTORY_SIZE; j++) {
            delete this->factories[i][j];
            this->factories[i][j] = nullptr;
        }
    }

    delete centerOfTable;
}

void GameManager::newGame() {
    
}

void GameManager::loadGame(std::string filename) {
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

LinkedList* GameManager::getTileBag() {
    return tileBag;
}

LinkedList* GameManager::getBoxLid() {
    return boxLid;
}

Factory* GameManager::getFactory() {
    return factories;
}

Vector* GameManager::getCenter() {
    return centerOfTable;
}

Player* GameManager::getPlayer(int id) {
    if(id == 1) {
        return player1;
    } else {
        return player2;
    }
}

int GameManager::getSeedNumber() {
    return seedNumber;
}
