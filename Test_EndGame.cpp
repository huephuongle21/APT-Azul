#include <iostream>
#include "Utility.h"
#include "GameManager.h"

int main(void) {
    GameManager* gm = new GameManager("Alice", "Bob");
    Player* player1 = gm->getPlayer(1);
    Player* player2 = gm->getPlayer(2);
    Board* board1 = player1->getBoard();
    Board* board2 = player2->getBoard();

    //Player1 has higher points than player2
    player1->addPoints(100);
    player2->addPoints(50);

    //Player2 has higher points than player1
    player2->addPoints(100);

    //Victory shared for 2 players
    player1->addPoints(50);

    //Player1 wins with higher number of completed rows
    board1->addWall(0,0,YELLOW);
    board1->addWall(0,1,BLACK);
    board1->addWall(0,2,BLACK);
    board1->addWall(0,3,DARK_BLUE);
    board1->addWall(0,4,LIGHT_BLUE);

    board2->addWall(1,0,YELLOW);
    board2->addWall(1,2,BLACK);
    board2->addWall(1,3,DARK_BLUE);
    board2->addWall(1,4,LIGHT_BLUE);
    board2->addWall(1,1,YELLOW);

    board2->addWall(0,1,YELLOW);
    board2->addWall(0,2,BLACK);
    board2->addWall(0,3,DARK_BLUE);
    board2->addWall(0,4,LIGHT_BLUE);
    board2->addWall(0,0,LIGHT_BLUE);

    if(gm->isEndGame()) {
        gm->showWinner();
    }

    // No row from board1 and board2 is completed
    // board1->addWall(0,1,RED);
    // board2->addWall(1,1,YELLOW);

    // gm->printTableAndBoard(player1);
    // gm->printTableAndBoard(player2);
    // std::cout << (gm->isEndGame() == true ? "true" : "false") << std::endl;
    // std::cout << player1->getName() << " completes " << board1->getNumberOfRowsCompleted() << " rows." << std::endl;
    // std::cout << player2->getName() << " completes " << board2->getNumberOfRowsCompleted() << " rows." << std::endl;

    // 1 row is completed from board1
    // board1->addWall(0,0,YELLOW);
    // board1->addWall(0,2,BLACK);
    // board1->addWall(0,3,DARK_BLUE);
    // board1->addWall(0,4,LIGHT_BLUE);

    // gm->printTableAndBoard(player1);
    // gm->printTableAndBoard(player2);
    // std::cout << (gm->isEndGame() == true ? "true" : "false") << std::endl;
    // std::cout << player1->getName() << " completes " << board1->getNumberOfRowsCompleted() << " rows." << std::endl;
    // std::cout << player2->getName() << " completes " << board2->getNumberOfRowsCompleted() << " rows." << std::endl;

    // 1 row is completed from board2 (comment out board1->addWall)
    // board2->addWall(1,0,YELLOW);
    // board2->addWall(1,2,BLACK);
    // board2->addWall(1,3,DARK_BLUE);
    // board2->addWall(1,4,LIGHT_BLUE);

    // 1 row is completed from board1 and 2 from board2
    // board2->addWall(0,1,YELLOW);
    // board2->addWall(0,2,BLACK);
    // board2->addWall(0,3,DARK_BLUE);
    // board2->addWall(0,4,LIGHT_BLUE);
    // board2->addWall(0,0,LIGHT_BLUE);

    
    // gm->printTableAndBoard(player1);
    // gm->printTableAndBoard(player2);
    // std::cout << (gm->isEndGame() == true ? "true" : "false") << std::endl;
    // std::cout << player1->getName() << " completes " << board1->getNumberOfRowsCompleted() << " rows." << std::endl;
    // std::cout << player2->getName() << " completes " << board2->getNumberOfRowsCompleted() << " rows." << std::endl;

    delete gm;
}

