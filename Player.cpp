
#include "Player.h"

Player::Player() {
    this->playerPoints = 0;
    this->playerBoard = new Board();
    this->playerName = "";
    this->isCurrentPlayer = false;
}

Player::~Player() {
    delete this->playerBoard;
}

void Player::setCurrent(bool isCurrent) {
    this->isCurrentPlayer = isCurrent;
}

int Player::getPoints() {
    return this->playerPoints;
}

std::string Player::getName() {
    return this->playerName;
}

void Player::addPoints(int points) {
    this->playerPoint += points;
}

Board* Player::getBoard() {
    return this->playerBoard;
}

bool Player::isCurrent() {
    return this->isCurrentPlayer;
}
