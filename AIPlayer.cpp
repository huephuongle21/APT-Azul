#include "AIPlayer.h"

AIPlayer::AIPlayer() :
    Player("Computer", 3) {
        tilesMove = {};
        tilesMoveLength = 0;
    };


void AIPlayer::makeMove(Table* table, Board* playerBoard) {

}

void AIPlayer::makeFactoryChoice(Factory* factories, Vector* center) {

}

void AIPlayer::makePatternLinesChoice(Board* playerBoard) {
    Tile** patternLines = playerBoard->getPatternLines();
    for(int i = 0; i != PATTERN_LINES_SIZE; i++) {
        int index = i+1;
        if(!playerBoard->isPatternLinesFilled(i) && !playerBoard->isPatternLinesEmpty(index)) {
            addPossibleTiles(patternLines[i][0]);
        }
    }

}

void AIPlayer::addPossibleTiles(Tile tile) {
    tilesMove[tilesMoveLength] = tile;
    tilesMoveLength++;
}