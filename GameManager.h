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
    GameManager(std::string player1Name, std::string player2Name, int seed);

    ~GameManager();

    // Set up table if isNewGame is true, otherwise, continue the current state loaded from file
    void startGame(bool isNewGame);
    
    // Load game from a file when player inputs option loadGame from Menu
    bool loadGame(std::string filename);

    // Save game to a file when player enters "save filename" command
    bool saveGame(std::string savePath);

    void swapCurrentPlayer();

    int getCurrentPlayerID();

    void setCurrentPlayerID(int currentPlayerID);

    Player* getPlayer(int id);

    bool commenceRound();

    bool commenceTurn(Player* player);

    // Return true if number of completed rows for either player 1 or player 2 greater than 0
    bool isEndGame();

    // Return true if both center of table and all factories are empty
    bool isEndRound();

    /* Valid Turn: turn <factory> <colour> <storage row>
                   save <filename>
    */
    bool playerTurn(Player* player, std::string performTurn);

    // factoryChoice from 0 to 5 (not empty) and that factory has colourChoice 
    bool promptForFactoryChoice(int& factoryChoice, char& colourChoice);
    
    // Check for valid colourChoice
    bool promptForColourChoice(char& colourChoice);

    bool promptForPatternLineChoice(Player* player, int& patternLineChoice, char& colourChoice);

    void takeTiles(int& factoryChoice, char& colour);

    void takeFromCentre(Player* player);

    void printTableAndBoard(Player* player);

    Table* getTable();

    ScoreCalculator* getCalculator();

    // Move tiles from patternLines to Wall and Box Lid, and calculate points for that corresponding tile. 
    int moveTilesFromPatternLines(Player* player);

    void commenceEndOfRound(Player* player);

    // Calculate score end of game and show the winner
    void commenceEndOfGame();

    /* Player with higher points wins the game. In case of a tie, player 
    with more horizontal lines completed wins. Otherwise, victory is shared. */
    void showWinner();

    private:

    Table* table;

    Player* player1;
    Player* player2;

    ScoreCalculator* calculator;
    
    int currentPlayerID;

    int roundCount;

};

#endif //GAMEMANAGER_H

