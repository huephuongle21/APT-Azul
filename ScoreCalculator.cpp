#include "ScoreCalculator.h"

ScoreCalculator::ScoreCalculator() {

}

ScoreCalculator::~ScoreCalculator() {

}

int ScoreCalculator::calculateScoreEachRound(Player* player, int& addScore) {

    int floorLineLength = player->getBoard()->getLength();
    int i = 0;
    int score = 0;

    // Subtract for broken tiles
    if(floorLineLength != 0) {
        while(i < floorLineLength) {
            if(0 <= i && i <= 1) {
                score -= 1;
            } else if(2 <= i && i <= 4) {
                score -= 2;
            } else {
                score -= 3;
            }
            i++;
        }
    }

    // Calculate points player get each round by subtract from floor line and add from wall
    score += addScore;

    // Set points to player
    player->addPoints(score);

    return score;
}

void ScoreCalculator::calculateScoreEndOfGame(Player* player) {

}

int ScoreCalculator::calculateScoreFromWall(Wall& wall, int& colPos, int& rowPos) {
    int score = 0;
    int countRow = 0;
    int countCol = 0;

    for(int row = 0; row != WALL_DIM; row++) {
        for(int col = 0; col != WALL_DIM; col++) {
            if(row == rowPos) {
                Tile tile = wall[row][col];
                if(tile >= 'A' && tile <= 'Z') {
                    score++;
                    countRow++;
                }              
            } else {
                if(col == colPos) {
                    Tile tile = wall[row][col];
                    if(tile >= 'A' && tile <= 'Z') {
                        score++;
                        countCol++;
                    }
                }
            }
        }
    }

    // Check whether tile is a part of both row and column
    if(countRow >= 2 && countCol >= 2) {
        score++;
    }

    return score;

}