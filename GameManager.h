#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Types.h"
#include "LinkedList.h"
#include "Player.h"
#include <vector>
#include <iostream>

class GameManager {
    public:

    GameManager();

    ~GameManager();

    void newGame();
    
    void loadGame();

    void saveGame();

    void swapCurrentPlayer();

    int getCurrentPlayerID();

    void setCurrentPlayerID(int currentPlayerID);

    private:

    LinkedList* tileBag;

    LinkedList* boxLid;

    Factory factories[NUMBER_OF_FACTORY];

    std::vector<TilePtr> centerOfTable;

    Player* player1;
    Player* player2;

    int currentPlayerID;

};

#endif //GAMEMANAGER_H

