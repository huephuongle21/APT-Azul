#include "AITurn.h"

AITurn::AITurn(int factoryChoice, Tile tileChoice, int patternLinesChoice) {
    this->factoryChoice = factoryChoice;
    this->tileChoice = tileChoice;
    this->patternLinesChoice = patternLinesChoice;
}

AITurn::~AITurn() {

}

int AITurn::getFactoryChoice() const {
    return factoryChoice;
}

Tile AITurn::getTileChoice() const {
    return tileChoice;
}

int AITurn::getPatternLinesChoice() const {
    return patternLinesChoice;
}

std::string AITurn::toString() {
    std::string turn;
    turn += "turn ";
    turn += std::to_string(factoryChoice);
    turn += " ";
    turn += tileChoice;
    turn += " ";
    turn += std::to_string(patternLinesChoice);
    return turn;
}

