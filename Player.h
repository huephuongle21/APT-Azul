#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
#include <iostream>

class Player {
    public:

    Player();

    ~Player();

    void setCurrent(bool isCurrent);

    int getPoints();

    std::string getName();

    void addPoints(int points);

    Board* getBoard();

    bool isCurrent();

    private:

    std::string playerName;

    int playerPoints;
    
    Board* playerBoard;
    
    bool isCurrentPlayer;

};

#endif // PLAYER_H