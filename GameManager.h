#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Types.h"
#include "LinkedList.h"
#include "Player.h"
#include "Vector.h"
#include <iostream>

class GameManager {
    public:

    GameManager();

    ~GameManager();

    void newGame();
    
    void loadGame(std::string filename);

    void saveGame(std::string filename);

    void swapCurrentPlayer();

    int getCurrentPlayerID();

    void setCurrentPlayerID(int currentPlayerID);

    private:

    LinkedList* tileBag;

    LinkedList* boxLid;

    Factory factories[NUMBER_OF_FACTORY];

    Vector* centerOfTable;

    Player* player1;
    Player* player2;

    int currentPlayerID;

    int seedNumber;

};

#endif //GAMEMANAGER_H

