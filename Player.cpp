#include "Player.h"

Player::Player(std::string playerName, int id) {
    this->playerName = playerName;
    this->id = id;
    this->playerPoints = 0;
    this->playerBoard = new Board();
}

Player::Player(int id) {
    this->playerName = "";
    this->id = id;
    this->playerPoints = 0;
    this->playerBoard = new Board();
}

Player::~Player() {
    delete this->playerBoard;
}

std::string Player::getName() {
    return this->playerName;
}

int Player::getID() {
    return this->id;
}

int Player::getPoints() {
    return this->playerPoints;
}

void Player::setName(std::string name) {
    this->playerName = name;
}

void Player::addPoints(int points) {
    this->playerPoints += points;
    if(playerPoints < 0) {
        playerPoints = 0;
    }
}

Board* Player::getBoard() {
    return this->playerBoard;
}

void Player::toStringEndOfGame() {
    std::cout << playerName << ": " << playerPoints << " points and " 
        << playerBoard->getNumberOfRowsCompleted() << " completed rows." << std::endl;  
}

void Player::toStringEndOfRound(int& addScore, unsigned int& roundCount) {
    if(addScore == 0) {
        std::cout << playerName << " remains the same points in round " 
            << roundCount << "." << std::endl;
    } else if(addScore < 0) {
        unsigned int subtractScore = -(addScore);
        std::cout << playerName << " loses " << subtractScore << " points from round " 
            << roundCount << "." << std::endl;
    } else {
        std::cout << playerName << " gets " << addScore << " points from round " 
            << roundCount << "." << std::endl;
    }
    std::cout << "Total points for " << playerName << ": " << playerPoints << "\n" << std::endl;
}
