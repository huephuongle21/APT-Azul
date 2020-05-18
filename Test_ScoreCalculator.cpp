#include "GameManager.h"
#include "Utility.h"

int main(void) {
    GameManager* gm = new GameManager("Alice","Bob");
    Board* board = gm->getPlayer(1)->getBoard();
    printWall(std::cout, board->getWall());
    std::cout << std::endl;

    int rowPos = 1;
    int colPos = 2;
    board->addWall(rowPos, colPos, LIGHT_BLUE);
    printWall(std::cout, board->getWall());

    // No tiles directly adjacent
    int score = gm->getCalculator()->calculateScoreFromWall(board->getWall(), colPos, rowPos);
    std::cout << "Score for row " << rowPos << " column " << colPos << ": " << score << std::endl;

    board->addWall(1, 3, RED);
    board->addWall(1, 4, YELLOW);
    printWall(std::cout, board->getWall());

    // Tile is a part of row
    score = gm->getCalculator()->calculateScoreFromWall(board->getWall(), colPos, rowPos);
    std::cout << "Score for row " << rowPos << " column " << colPos << ": " << score << std::endl;

    board->addWall(1, 3, NO_TILE);
    board->addWall(1, 4, NO_TILE);
    board->addWall(2, 2, BLACK);
    board->addWall(3, 2, DARK_BLUE);
    printWall(std::cout, board->getWall());

    // Tile is a part of column
    score = gm->getCalculator()->calculateScoreFromWall(board->getWall(), colPos, rowPos);
    std::cout << "Score for row " << rowPos << " column " << colPos << ": " << score << std::endl;

    board->addWall(1, 3, RED);
    board->addWall(1, 4, YELLOW);
    board->addWall(1, 1, YELLOW);
    printWall(std::cout, board->getWall());

    // Tile is a part of both row and column
    score = gm->getCalculator()->calculateScoreFromWall(board->getWall(), colPos, rowPos);
    std::cout << "Score for row " << rowPos << " column " << colPos << ": " << score << std::endl;

    std::cout << "Added score is " << score << std::endl;

    // Floor line with no broken tiles
    printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    int scoreEndOfRound = gm->getCalculator()->calculateScoreEachRound(gm->getPlayer(1), score);
    std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    std::cout << std::endl;

    // Floor line with 1 broken tile
    board->addFloorLine(RED);
    printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    scoreEndOfRound = gm->getCalculator()->calculateScoreEachRound(gm->getPlayer(1), score);
    std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    std::cout << std::endl;

    // Floor line with 2 broken tiles
    board->addFloorLine(RED);
    printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    scoreEndOfRound = gm->getCalculator()->calculateScoreEachRound(gm->getPlayer(1), score);
    std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    std::cout << std::endl;

    // Floor line with 3 broken tiles
    board->addFloorLine(RED);
    printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    scoreEndOfRound = gm->getCalculator()->calculateScoreEachRound(gm->getPlayer(1), score);
    std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    std::cout << std::endl;

    // Floor line with 4 broken tiles
    board->addFloorLine(RED);
    printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    scoreEndOfRound = gm->getCalculator()->calculateScoreEachRound(gm->getPlayer(1), score);
    std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    std::cout << std::endl;

    // Floor line with 5 broken tiles
    board->addFloorLine(RED);
    printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    scoreEndOfRound = gm->getCalculator()->calculateScoreEachRound(gm->getPlayer(1), score);
    std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    std::cout << std::endl;

    // Floor line with 6 broken tile
    board->addFloorLine(RED);
    printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    scoreEndOfRound = gm->getCalculator()->calculateScoreEachRound(gm->getPlayer(1), score);
    std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    std::cout << std::endl;

    // Floor line with 7 broken tile
    board->addFloorLine(RED);
    printFloorLine(std::cout, board->getFloorLine(), board->getLength());
    scoreEndOfRound = gm->getCalculator()->calculateScoreEachRound(gm->getPlayer(1), score);
    std::cout << "Score end of round: " << scoreEndOfRound << " with " << board->getLength() << " number of broken tiles." << std::endl;
    std::cout << std::endl;

}