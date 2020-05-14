#include "GameManager.h"
#include "SetupManager.h"
#include "Utility.h"

#include <iostream>
#include <string>
#include <fstream>

GameManager::GameManager() {

    this->player1 = new Player("Alice", 1);
    this->player2 = new Player("Bob", 2);

    currentPlayerID = player1->getID();

    this->table = new Table();

}

GameManager::~GameManager() {
    delete player1;
    delete player2;
    delete table;
}

void GameManager::newGame() {

    // SetupManager* sm = new SetupManager(table->getSeedNumber());

    // sm->populateTileBag(table->getTileBag());
    // sm->populateFactories(table->getTileBag(), table->getFactories(), table->getBoxLid());
    
}

void GameManager::loadGame(std::string filename) {
    std::ifstream inFile;
    inFile.open(filename);

    if(inFile.fail()) {
        std::cout << "File does not exist" << std::endl;
    } else {
        readGame(inFile, table, &currentPlayerID, player1, player2);
        inFile.close();
    }
    printGame(std::cout, table, currentPlayerID, player1, player2);
}

void GameManager::saveGame(std::string filename) {
    std::ofstream outFile;
    outFile.open(filename);

    if(outFile.fail()) {
        std::cout << "File does not exist" << std::endl;
    } else {
        printGame(outFile, table, currentPlayerID, player1, player2);
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

Player* GameManager::getPlayer(int id) {
    if(id == 1) {
        return player1;
    } else {
        return player2;
    }
}
