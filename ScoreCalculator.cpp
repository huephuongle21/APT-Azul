#include "ScoreCalculator.h"

ScoreCalculator::ScoreCalculator() {

}

ScoreCalculator::~ScoreCalculator() {

}

int ScoreCalculator::calculateScoreEachRound(Player* player, int& addScore) {
    unsigned int floorLineLength = player->getBoard()->getFloorLineLength();
    unsigned int i = 0;
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
    // Calculate points getting each round by subtract from floor line and add from wall
    score += addScore;
    // Set points to player
    player->addPoints(score);
    return score;
}

int ScoreCalculator::calculateScoreFromWall(Wall& wall, int& colPos, int& rowPos) {
    int score = 0;
    int countRow = 0;
    int countCol = 0;
    for(int row = 0; row != WALL_DIM; row++) {
        Tile tile = wall[row][colPos];
        if(tile >= 'A' && tile <= 'Z') {
            score++;
            countCol++;
        }
    }
    for(int col = 0; col != WALL_DIM; col++) {
        Tile tile = wall[rowPos][col];
        if(tile >= 'A' && tile <= 'Z') {
            score++;
            countRow++;
        }
    }
    if(countRow == 1 || countCol == 1) {
        score--;
    }
    return score;
}

void ScoreCalculator::calculateScoreEndOfGame(Player* player) {
    int score = 0;
    Board* board = player->getBoard();
    Wall& wall = board->getWall();
    
    // Check for entire row
    unsigned int numberOfRowsCompleted = board->getNumberOfRowsCompleted();
    score += (numberOfRowsCompleted*POINT_HORIZONTAL);
   
    // Check for any 5 of 1 colour and any entire column
    bool isColumnFilled = true;
    int nTileRed = 0;
    int nTileYellow = 0;
    int nTileDarkBlue = 0;
    int nTileLightBlue = 0;
    int nTileBlack = 0;
    for(int row = 0; row != WALL_DIM; row++) {
        for(int col = 0; col != WALL_DIM; col++) {
            Tile tile = wall[row][col];
            if(tile == RED) {
                nTileRed++;
            } else if(tile == YELLOW) {
                nTileYellow++;
            } else if(tile == DARK_BLUE) {
                nTileDarkBlue++;
            } else if(tile == LIGHT_BLUE) {
                nTileLightBlue++;
            } else if(tile == BLACK) {
                nTileBlack++;
            } 
            if(wall[col][row] >= 'a' && wall[col][row] <= 'z') {
                isColumnFilled = false;
            }
        }
        if(isColumnFilled) {
            score += POINT_VERTICAL;
        }
        isColumnFilled = true;
    }

    if(nTileRed == 5) {
        score += POINT_1_COLOUR;
    }
    if(nTileYellow == 5) {
        score += POINT_1_COLOUR;
    }
    if(nTileDarkBlue == 5) {
        score += POINT_1_COLOUR;
    }
    if(nTileLightBlue == 5) {
        score += POINT_1_COLOUR;
    }
    if(nTileBlack == 5) {
        score += POINT_1_COLOUR;
    }
    // Set points for player
    player->addPoints(score);
}