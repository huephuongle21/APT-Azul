#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include "Player.h"

class ScoreCalculator {

public:

    ScoreCalculator();

    ~ScoreCalculator();

    int calculateScoreEachRound(Player* player);

    void calculateScoreEndOfGame(Player* player);

private:

};

#endif // SCORECALCULATOR_H