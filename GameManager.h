#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Types.h"
#include "LinkedList.h"
#include "Player.h"
#include "Vector.h"
#include "Table.h"
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

    Player* getPlayer(int id);

    private:

    Table* table;

    Player* player1;
    Player* player2;
    

    int currentPlayerID;

};

#endif //GAMEMANAGER_H

