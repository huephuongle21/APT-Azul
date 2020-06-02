#include "AiTurn.h"

AiTurn::AiTurn(int factoryChoice, Tile tileChoice, 
        int patternLinesChoice, bool valid, int numTilesTaken) {
    this->factoryChoice = factoryChoice;
    this->tileChoice = tileChoice;
    this->patternLinesChoice = patternLinesChoice;
    this->valid = valid;
    this->numTilesTaken = numTilesTaken;
    this->validPatternLines = true;
}

AiTurn::AiTurn(Tile tileChoice, int patternLinesChoice) {
    this->tileChoice = tileChoice;
    this->patternLinesChoice = patternLinesChoice;
    this->valid = false;
    this->validPatternLines = false;
    this->numTilesTaken = 0;
    this->factoryChoice = -1;
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

void AiTurn::setNumTilesTaken(int num) {
    this->numTilesTaken = num;
} 

int AiTurn::getNumTilesTaken() {
    return this->numTilesTaken;
}

void AiTurn::setPatternLines(bool valid) {
    this->validPatternLines = valid;
}

bool AiTurn::isPatternLinesValid() {
    return validPatternLines;
}
