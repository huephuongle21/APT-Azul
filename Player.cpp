#include "Player.h"

Player::Player(std::string playerName, int id) {
    this->playerName = playerName;
    this->id = id;
    this->playerPoints = 0;
    this->playerBoard = new Board();
}

Player::Player() {
    this->playerName = "";
    this->id = 0;
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
}

Board* Player::getBoard() {
    return this->playerBoard;
}
