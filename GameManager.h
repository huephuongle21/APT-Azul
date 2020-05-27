#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Types.h"
#include "LinkedList.h"
#include "Player.h"
#include "Vector.h"
#include "Table.h"
#include "ScoreCalculator.h"
#include <iostream>
#include <string>

class GameManager {
    public:

    // Constructor to load game from file
    GameManager();

    // Constructor to start new game
    GameManager(std::string player1Name, std::string player2Name, int seed, int boardId);

    ~GameManager();

    // Set up table if isNewGame is true, otherwise, continue with the current state loaded from file
    bool startGame(bool isNewGame);
    
    bool loadGame(std::string filename);

    bool saveGame(std::string savePath);

    void swapCurrentPlayer();

    int getCurrentPlayerID();

    void setCurrentPlayerID(int currentPlayerID);

    Player* getPlayer(int id);

    bool commenceRound();

    bool commenceTurn(Player* player);

    bool isEndGame();

    bool isEndRound();

    /* Valid Turn: turn <factory> <colour> <storage row>
                   save <filename>
                   quit
    */
    bool playerTurn(Player* player, std::string performTurn);

    bool promptForFactoryChoice(int& factoryChoice, char& colourChoice, int boardId);
    
    bool promptForColourChoice(char& colourChoice, int boardId);

    bool promptForPatternLineChoice(Player* player, int& patternLineChoice, char& colourChoice, int boardSize);

    void takeTiles(int& factoryChoice, char& colour);

    void printTableAndBoard(Player* player);

    Table* getTable();

    ScoreCalculator* getCalculator();

    // Move tiles from patternLines to Wall and Box Lid, and calculate points for that corresponding tile. 
    int moveTilesFromPatternLines(Player* player);

    void moveTilesFromFactory(Player* player);

    bool commenceEndOfRound(Player* player);

    // Calculate score end of game and show the winner
    void commenceEndOfGame();

    /* Player with higher points wins the game. In case of a tie, player 
    with more horizontal lines completed wins. Otherwise, victory is shared. */
    void showWinner();

    void moveTilesToPatternLines(Player* player, int& factoryChoice, int& patternLineChoice, char& colourChoice);

    void moveTilesFromCenter(LinkedList* boxLid, Tile** patternLines, Vector* center, 
        AbstractBoard* board, char& colourChoice, int& patternLineChoice, int floorLineMaxSize);

    void moveTilesFromFactory(int& factoryChoice, char& colourChoice, int& patternLineChoice, 
        AbstractBoard* board, LinkedList* boxLid, Tile* chosenFactory, Tile** patternLines, Vector* center,
        int floorLineMaxSize);

    int userPromptForWall(AbstractBoard* board, int index);

    private:

    Table* table;

    Player* player1;
    Player* player2;

    ScoreCalculator* calculator;
    
    int currentPlayerID;

    int roundCount;

};

#endif //GAMEMANAGER_H

