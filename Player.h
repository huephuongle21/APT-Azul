#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "AbstractBoard.h"
#include <iostream>
#include "AiManager.h"

class Player {

public:

    // Constructor to start a new game
    Player(std::string playerName, int id, int boardId);

    // Constructor to load game from file
    Player(int id);

    virtual ~Player();

    std::string getName();

    int getID();

    int getPoints();

    void addPoints(int points);

    AbstractBoard* getBoard();

    void setName(std::string name);
    
    // Print player name with points and number of completed rows at the end of game
    void toStringEndOfGame();

    // Print player name with updating points each round
    void toStringEndOfRound(int& addScore, int& roundCount);

    void createBoard(int boardId);
    
private:

    std::string playerName;

    int id;

    int playerPoints;
    
    AbstractBoard* playerBoard;

};

#endif // PLAYER_H