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
#include "AiManager.h"

class GameManager {
    public:

    // Constructor to load game from file
    GameManager();

    // Constructor to start new game
    GameManager(std::string player1Name, std::string player2Name, int seed, 
            int boardId, bool isSingleMode);

    ~GameManager();

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
                   help
    */
    bool playerTurn(Player* player, std::string performTurn);

    bool promptForFactoryChoice(int& factoryChoice, char& colourChoice, int boardId);
    
    bool promptForColourChoice(char& colourChoice, int boardId);

    bool promptForPatternLineChoice(Player* player, int& patternLineChoice, 
        char& colourChoice, int boardSize);

    void takeTiles(int& factoryChoice, char& colour);

    void printTableAndBoard(Player* player);

    Table* getTable();

    ScoreCalculator* getCalculator();

    int moveTilesFromPatternLines(Player* player);

    void moveTilesFromFactory(Player* player);

    bool commenceEndOfRound(Player* player);

    void commenceEndOfGame();

    /* Player with higher points wins the game. In case of a tie, player 
    with more horizontal lines completed wins. Otherwise, victory is shared. */
    void showWinner();

    void moveTilesToPatternLines(Player* player, int& factoryChoice, 
        int& patternLineChoice, char& colourChoice);

    int moveTilesFromCenter(LinkedList* boxLid, Tile** patternLines, Vector* center, 
        AbstractBoard* board, char& colourChoice, int& patternLineChoice, int floorLineMaxSize);

    int moveTilesFromFactory(int& factoryChoice, char& colourChoice, int& patternLineChoice, 
        AbstractBoard* board, LinkedList* boxLid, Tile* chosenFactory, Tile** patternLines, 
        Vector* center, int floorLineMaxSize);

    int userPromptForWall(AbstractBoard* board, int index, Tile tile);

    private:

    Table* table;

    Player* player1;
    Player* player2;

    ScoreCalculator* calculator;
    
    int currentPlayerID;

    int roundCount;

    bool isSingleMode;

    AiManager* am;

};

#endif //GAMEMANAGER_H

