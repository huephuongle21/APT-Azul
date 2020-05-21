#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
#include <iostream>

class Player {

public:

    // Constructor to start a new game
    Player(std::string playerName, int id);

    // Constructor to load game from file
    Player(int id);

    ~Player();

    std::string getName();

    int getID();

    int getPoints();

    void addPoints(int points);

    Board* getBoard();

    void setName(std::string name);
    
    // Print player name with points and number of completed rows at the end of game
    void toStringEndOfGame();

    // Print player name with updating points each round
    void toStringEndOfRound(int& addScore, unsigned int& roundCount);

private:

    std::string playerName;

    int id;

    int playerPoints;
    
    Board* playerBoard;

};

#endif // PLAYER_H