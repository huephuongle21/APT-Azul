<<<<<<< HEAD
#ifndef GAMEADT_H
#define GAMEADT_H

#include "Types.h"
#include "LinkedList.h"
#include "Player.h"
#include <vector>
#include <iostream>
=======

#ifndef GAMEADT_H
#define GAMEADT_H

>>>>>>> master

class GameADT {
    public:

    GameADT();

    ~GameADT();

    void newGame();
    
    void loadGame();

    void saveGame();

    private:
<<<<<<< HEAD

    LinkedList* tileBag;

    LinkedList* boxLid;

    Factory factories[NUMBER_OF_FACTORY];

    std::vector<TilePtr> centerOfTable;

    Player* player1;
    Player* player2;

};

#endif //GAMEADT_H

=======
};

#endif //GAMEADT_H
>>>>>>> master
