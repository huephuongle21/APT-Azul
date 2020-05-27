#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include "Player.h"

class ScoreCalculator {

public:

    ScoreCalculator();

    ~ScoreCalculator();

    int calculateScoreEachRound(Player* player, int& addScore);

    void calculateScoreEndOfGame(Player* player);

    int calculateScoreFromWall(Wall wall, int& colPos, int& rowPos);

};

#endif // SCORECALCULATOR_H