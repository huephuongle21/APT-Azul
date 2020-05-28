#include "Player.h"
#include "RegularBoard.h"
#include "GreyBoard.h"
#include "Advanced6TileBoard.h"

Player::Player(std::string playerName, int id, int boardId) {
    this->playerName = playerName;
    this->id = id;
    this->playerPoints = 0;
    createBoard(boardId);
}

Player::Player(int id) {
    this->playerName = "";
    this->id = id;
    this->playerPoints = 0;
    this->playerBoard = nullptr;
}

void Player::createBoard(int boardId) {
    if(boardId == REGULAR_BOARD) {
        this->playerBoard = new RegularBoard();
    } else if(boardId == GREY_BOARD) {
        this->playerBoard = new GreyBoard();
    } else if(boardId == ADVANCED_6TILE_BOARD) {
        this->playerBoard = new Advanced6TileBoard();
    }
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

AbstractBoard* Player::getBoard() {
    return this->playerBoard;
}

void Player::toStringEndOfGame() {
    std::cout << playerName << ": " << playerPoints << " points and " 
        << playerBoard->getNumberOfRowsCompleted() << " completed rows." << "\n" << std::endl;  
}

void Player::toStringEndOfRound(int& addScore, int& roundCount) {
    if(addScore == 0) {
        std::cout << playerName << " remains the same points in round " 
            << roundCount << "." << std::endl;
    } else if(addScore < 0) {
        int subtractScore = -(addScore);
        std::cout << playerName << " loses " << subtractScore << " points from round " 
            << roundCount << "." << std::endl;
    } else {
        std::cout << playerName << " gets " << addScore << " points from round " 
            << roundCount << "." << std::endl;
    }
    std::cout << "Total points for " << playerName << ": " << playerPoints << "\n" << std::endl;
}
