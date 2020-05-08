#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
#include <iostream>

class Player {

    public:

    Player(std::string playerName, int id);

    ~Player();

    std::string getName();

    int getID();

    int getPoints();

    void addPoints(int points);

    Board* getBoard();

private:

    std::string playerName;

    int id;

    int playerPoints;
    
    Board* playerBoard;

};

#endif // PLAYER_H