#include "AiTurn.h"

AiTurn::AiTurn(int factoryChoice, Tile tileChoice, int patternLinesChoice, bool valid) {
    this->factoryChoice = factoryChoice;
    this->tileChoice = tileChoice;
    this->patternLinesChoice = patternLinesChoice;
    this->valid = valid;
}

AiTurn::~AiTurn() {

}

int AiTurn::getFactoryChoice() const {
    return factoryChoice;
}

Tile AiTurn::getTileChoice() const {
    return tileChoice;
}

int AiTurn::getPatternLinesChoice() const {
    return patternLinesChoice;
}

std::string AiTurn::toString() {
    std::string turn;
    turn += "turn ";
    turn += std::to_string(factoryChoice);
    turn += " ";
    turn += tileChoice;
    turn += " ";
    turn += std::to_string(patternLinesChoice);
    return turn;
}

void AiTurn::setValid(bool valid) {
    this->valid = valid;
}

bool AiTurn::isValid() {
    return this->valid;
}

