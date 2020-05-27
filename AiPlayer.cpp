#include "AiPlayer.h"

AiPlayer::AiPlayer() :
    Player("Computer", 3) {
        tilesMove = {};
        tilesMoveLength = 0;
    };


void AiPlayer::makeMove(Table* table, Board* playerBoard) {

}

void AiPlayer::makeFactoryChoice(Factory* factories, Vector* center) {

}

void AiPlayer::makePatternLinesChoice(Board* playerBoard) {
    Tile** patternLines = playerBoard->getPatternLines();
    for(int i = 0; i != PATTERN_LINES_SIZE; i++) {
        int index = i+1;
        if(!playerBoard->isPatternLinesFilled(i) && !playerBoard->isPatternLinesEmpty(index)) {
            addPossibleTiles(patternLines[i][0]);
        }
    }

}

void AiPlayer::addPossibleTiles(Tile tile) {
    tilesMove[tilesMoveLength] = tile;
    tilesMoveLength++;
}