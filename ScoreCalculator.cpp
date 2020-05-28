#include "ScoreCalculator.h"

ScoreCalculator::ScoreCalculator() {

}

ScoreCalculator::~ScoreCalculator() {

}

int ScoreCalculator::calculateScoreEachRound(Player* player, int& addScore) {
    int floorLineLength = player->getBoard()->getFloorLineLength();
    int i = 0;
    int score = 0;
    // Subtract for broken tiles
    if(floorLineLength != 0) {
        while(i < floorLineLength) {
            if(0 <= i && i <= 1) {
                score -= 1;
            } else if(2 <= i && i <= 4) {
                score -= 2;
            } else if(5 <= i && i <= 6) {
                score -= 3;
            } else if(i == 7) {
                score -= 4;
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

int ScoreCalculator::calculateScoreFromWall(Wall wall, int& colPos, int& rowPos, int boardSize) {
    int score = 0;
    int countRow = 0;
    int countCol = 0;
    for(int row = 0; row != boardSize; row++) {
        Tile tile = wall[row][colPos];
        if(tile >= 'A' && tile <= 'Z') {
            score++;
            countCol++;
        }
    }
    for(int col = 0; col != boardSize; col++) {
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
    AbstractBoard* board = player->getBoard();
    Wall wall = board->getWall();
    int boardSize = board->getBoardSize();
    int boardId = board->getBoardId();
    
    // Check for entire row
    int numberOfRowsCompleted = board->getNumberOfRowsCompleted();
    score += (numberOfRowsCompleted*POINT_HORIZONTAL);
   
    // Check for any 5 of 1 colour and any entire column
    bool isColumnFilled = true;
    int nTileRed = 0;
    int nTileYellow = 0;
    int nTileDarkBlue = 0;
    int nTileLightBlue = 0;
    int nTileBlack = 0;
    int nTileOrange = 0;
    for(int row = 0; row != boardSize; row++) {
        for(int col = 0; col != boardSize; col++) {
            Tile colorTile = wall[row][col];
            if(colorTile == RED) {
                nTileRed++;
            } else if(colorTile == YELLOW) {
                nTileYellow++;
            } else if(colorTile == DARK_BLUE) {
                nTileDarkBlue++;
            } else if(colorTile == LIGHT_BLUE) {
                nTileLightBlue++;
            } else if(colorTile == BLACK) {
                nTileBlack++;
            } else if(boardId == ADVANCED_6TILE_BOARD && colorTile == ORANGE) {
                nTileOrange++;
            }
            Tile colTile = wall[col][row];
            if((colTile >= 'a' && colTile <= 'z') || colTile == NO_TILE) {
                isColumnFilled = false;
            }
        }
        if(isColumnFilled) {
            score += POINT_VERTICAL;
        }
        isColumnFilled = true;
    }

    if(nTileRed == boardSize) {
        score += POINT_1_COLOUR;
    }
    if(nTileYellow == boardSize) {
        score += POINT_1_COLOUR;
    }
    if(nTileDarkBlue == boardSize) {
        score += POINT_1_COLOUR;
    }
    if(nTileLightBlue == boardSize) {
        score += POINT_1_COLOUR;
    }
    if(nTileBlack == boardSize) {
        score += POINT_1_COLOUR;
    }
    if(nTileOrange == boardSize) {
        score += POINT_1_COLOUR;
    }
    // Set points for player
    player->addPoints(score);
}