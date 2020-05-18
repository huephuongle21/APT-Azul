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
    GameManager(std::string player1Name, std::string player2Name);

    ~GameManager();

    void startGame(bool isNewGame);
    
    bool loadGame(std::string filename);

    bool saveGame(std::string savePath);

    void swapCurrentPlayer();

    int getCurrentPlayerID();

    void setCurrentPlayerID(int currentPlayerID);

    Player* getPlayer(int id);

    bool commenceRound();

    bool commenceTurn(Player* player);

    bool isEndGame(Player* player1, Player* player2);

    bool isEndRound();

    bool playerTurn(Player* player, std::string performTurn);

    bool promptForFactoryChoice(int& factoryChoice, char& colourChoice);
    
    bool promptForColourChoice(char& colourChoice);

    bool promptForPatternLineChoice(Player* player, int& patternLineChoice, char& colourChoice);

    void takeTiles(int& factoryChoice, char& colour);

    void printTableAndBoard(Player* player);

    Table* getTable();

    ScoreCalculator* getCalculator();

    int moveTilesFromPatternLines(Player* player);

    void moveTilesToPatternLines(Player* player);

    void commenceEndOfRound(Player* player);

    private:

    Table* table;

    Player* player1;
    Player* player2;

    ScoreCalculator* calculator;
    
    int currentPlayerID;

    int roundCount;

};

#endif //GAMEMANAGER_H

