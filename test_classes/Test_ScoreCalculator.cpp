#include "GameManager.h"
#include "Utility.h"

int main(void) {
    GameManager* gm = new GameManager("Alice","Bob",5);
    Player* player = gm->getPlayer(1);
    Board* board = player->getBoard();
    ScoreCalculator* cal = gm->getCalculator();
    // printWall(std::cout, board->getWall());
    // std::cout << std::endl;

    int rowPos = 1;
    int colPos = 2;
    board->addWall(rowPos, colPos, LIGHT_BLUE);
    board->addWall(0,0,RED);
    // board->addWall(1,1,RED);
    // board->addWall(2,3,RED);
    board->addWall(3,4,RED);
    // board->addWall(4,0,RED);

    board->addWall(0,3,DARK_BLUE);
    board->addWall(1,0,DARK_BLUE);
    board->addWall(3,3,DARK_BLUE);
    board->addWall(4,4,DARK_BLUE);
    board->addWall(3,1,DARK_BLUE);

    board->addWall(2,0, YELLOW);
    // board->addWall(3,0, RED);
    // board->addWall(4,0,LIGHT_BLUE);

    board->addWall(0,4, YELLOW);
    board->addWall(1,4, BLACK);
    board->addWall(2,4, BLACK);

    board->addWall(1,3, BLACK);
    board->addWall(4,3, BLACK);

    board->addWall(2,1, LIGHT_BLUE);
    board->addWall(0,1, YELLOW);
    board->addWall(4,1, YELLOW);

    board->addWall(0,2,LIGHT_BLUE);
    board->addWall(2,2,YELLOW);
    board->addWall(4,2,LIGHT_BLUE);
    board->addWall(3,2,BLACK);

    printWall(std::cout, board->getWall());
    std::cout << "Initial points: " << player->getPoints() << std::endl;
    board->completeRows();
    cal->calculateScoreEndOfGame(player);
    std::cout << "Points end of game: " << player->getPoints() << std::endl;

    // board->addWall(1,3,BLACK);
    // board->addWall(4,3,YELLOW);
    // board->addWall(1,4,LIGHT_BLUE);

    // printWall(std::cout, board->getWall());
    // std::cout << "Initial points: " << player->getPoints() << std::endl;
    // cal->calculateScoreEndOfGame(player);
    // std::cout << "Points end of game: " << player->getPoints() << std::endl;


    // // No tiles directly adjacent
    // int score = cal->calculateScoreFromWall(board->getWall(), colPos, rowPos);
    // std::cout << "Score for row " << rowPos << " column " << colPos << ": " << score << std::endl;

    // board->addWall(1, 3, RED);
    // board->addWall(1, 4, YELLOW);
    // printWall(std::cout, board->getWall());

    // // Tile is a part of row
    // score = cal->calculateScoreFromWall(board->getWall(), colPos, rowPos);
    // std::cout << "Score for row " << rowPos << " column " << colPos << ": " << score << std::endl;

    // board->addWall(1, 3, NO_TILE);
    // board->addWall(1, 4, NO_TILE);
    // board->addWall(2, 2, BLACK);
    // board->addWall(3, 2, DARK_BLUE);
    // printWall(std::cout, board->getWall());

    // // Tile is a part of column
    // score = cal->calculateScoreFromWall(board->getWall(), colPos, rowPos);
    // std::cout << "Score for row " << rowPos << " column " << colPos << ": " << score << std::endl;

    // board->addWall(1, 3, RED);
    // board->addWall(1, 4, YELLOW);
    // board->addWall(1, 1, YELLOW);
    // printWall(std::cout, board->getWall());

    // // Tile is a part of both row and column
    // score = cal->calculateScoreFromWall(board->getWall(), colPos, rowPos);
    // std::cout << "Score for row " << rowPos << " column " << colPos << ": " << score << std::endl;

    // std::cout << "Added score is " << score << std::endl;

    // // Floor line with no broken tiles
    // printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    // int scoreEndOfRound = cal->calculateScoreEachRound(player, score);
    // std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    // std::cout << std::endl;

    // // Floor line with 1 broken tile
    // board->addFloorLine(RED);
    // printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    // scoreEndOfRound = cal->calculateScoreEachRound(player, score);
    // std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    // std::cout << std::endl;

    // // Floor line with 2 broken tiles
    // board->addFloorLine(RED);
    // printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    // scoreEndOfRound = cal->calculateScoreEachRound(player, score);
    // std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    // std::cout << std::endl;

    // // Floor line with 3 broken tiles
    // board->addFloorLine(RED);
    // printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    // scoreEndOfRound = cal->calculateScoreEachRound(player, score);
    // std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    // std::cout << std::endl;

    // // Floor line with 4 broken tiles
    // board->addFloorLine(RED);
    // printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    // scoreEndOfRound = cal->calculateScoreEachRound(player, score);
    // std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    // std::cout << std::endl;

    // // Floor line with 5 broken tiles
    // board->addFloorLine(RED);
    // printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    // scoreEndOfRound = cal->calculateScoreEachRound(player, score);
    // std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    // std::cout << std::endl;

    // // Floor line with 6 broken tile
    // board->addFloorLine(RED);
    // printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    // scoreEndOfRound = cal->calculateScoreEachRound(player, score);
    // std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    // std::cout << std::endl;

    // // Floor line with 7 broken tile
    // board->addFloorLine(RED);
    // printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    // scoreEndOfRound = cal->calculateScoreEachRound(player, score);
    // std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    // std::cout << std::endl;

    delete gm;

}