#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "StudentCredit.h"
#include "GameManager.h"
#include "Types.h"
#include "Player.h"
#include "Utility.h"

// Process command line args for seed.
void processSeed(int argc, char** argv, int* seed);

void printMenu();
void printBoardOption();

Option resolveInput(std::string input);
BoardOption resolveBoardInput(std::string input);

bool startNewGame(int seed);
bool loadGameFromFile();

int main(int argc, char** argv) {

    int seed;
    processSeed(argc, argv, &seed);

    StudentCredit* studentArr = new StudentCredit();

    std::cout << C_GREEN << BREAK_LINE << C_RESET << std::endl;
    std::cout << C_BOLDBLUE << "Welcome to Azul!" << C_RESET << std::endl;
    std::cout << C_GREEN << BREAK_LINE << C_RESET << std::endl;
    printInstructions();
    std::cout << '\n' <<C_GREEN << BREAK_LINE << C_RESET << "\n" << std::endl;
    
    printMenu();
    std::cout << "\n" <<C_LIGHTYELLOW << USER_PROMPT << C_RESET " ";
    bool isQuit = false;
    std::string input;
    
    while(!isQuit && getline(std::cin, input)) {
        Option option = resolveInput(input);
        if(option == newGame) {
            if(!startNewGame(seed)) {
                printMenu();
            } else {
                isQuit = true;
            }
        } else if(option == loadGame) {
            if(!loadGameFromFile()) {
                printMenu();
            } else {
                isQuit = true;
            }
        } else if(option == displayCredits) {
            studentArr->printDetails();
            printMenu();
        } else if(option == quit) {
            isQuit = true;
        } else {
            std::cout << "\n" << C_RED << "Invalid Input" << C_RESET << "\n" << std::endl;
        }
        if(!isQuit && !std::cin.eof()) {
            std::cout << C_LIGHTYELLOW << USER_PROMPT << C_RESET " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Goodbye" << std::endl;

    delete studentArr;
}

void processSeed(int argc, char** argv, int* seed) {
    if (argc == 3) {      
        std::string modeInput(argv[1]);
        std::string seedInput(argv[2]);
        if (modeInput != "-s") {
            std::cout << "Mode invalid. Proceeding with random seed." << std::endl;
            *seed = static_cast<int> (time(NULL));
        } else {
            try { 
                *seed = std::stoi(seedInput);
            } catch (std::invalid_argument const &e) {
		        std::cout << "Invalid seed input. Proceeding with random seed." << std::endl;
                *seed = static_cast<int> (time(NULL));
            } catch (std::out_of_range const &e) {
		        std::cout << "Seed input out of range. Proceeding with random seed." << std::endl;
                *seed = static_cast<int> (time(NULL));
            }
        }
    } else {
       std::cout << "No seed provided. Proceeding with random seed." << "\n" << std::endl;
       *seed = static_cast<int> (time(NULL));
   }

}

void printMenu() {
    std::cout << std::endl;
    std::cout << C_BOLDBLUE << "Menu" << C_RESET << std::endl;
    std::cout << C_GREEN << "----" << C_RESET << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Display Credits" << std::endl;
    std::cout << "4. Quit" << std::endl;  
    std::cout << "\n" << "(Choose '1', '2', '3' or '4')" << "\n" << std::endl;  
}

void printBoardOption() {
    std::cout << std::endl;
    std::cout << C_BOLDBLUE << "Choose one type of board which you want to play" << C_RESET << std::endl;
    std::cout << C_GREEN << BREAK_LINE << C_RESET << std::endl;
    std::cout << "1. Regular Board" << std::endl;
    std::cout << "2. Advanced Grey Board" << std::endl;
    std::cout << "3. Advanced 6-tile Modes" << std::endl; 
    std::cout << "\n" << "(Choose '1', '2' or '3')" << "\n" << std::endl;
}

Option resolveInput(std::string input) {
    Option option = OptionInvalid;
    if(input == "1") {
        option = newGame;
    } else if (input == "2") {
        option = loadGame;
    } else if (input == "3") {
        option = displayCredits;
    } else if(input == "4") {
        option = quit;
    }
    return option;
}

BoardOption resolveBoardInput(std::string input) {
    BoardOption option = invalidBoard;
    if(input == "1") {
        option = regular;
    } else if (input == "2") {
        option = grey;
    } else if (input == "3") {
        option = advanced6Tile;
    } 
    return option;
}

bool startNewGame(int seed) {
    int boardId = 0;
    bool isEOF = true;
    std::cout << "\n" << C_BOLDBLUE << "Starting a New Game" << C_RESET << std::endl;

    printBoardOption();
    std::cout << C_LIGHTYELLOW << USER_PROMPT << C_RESET << " ";
    bool isQuit = false;
    std::string input;
    
    while(!isQuit && getline(std::cin, input)) {
        BoardOption option = resolveBoardInput(input);
        if(option == regular) {
            boardId = REGULAR_BOARD;
            isQuit = true;
        } else if(option == grey) {
            boardId = GREY_BOARD;
            isQuit = true;
        } else if(option == advanced6Tile) {
            boardId = ADVANCED_6TILE_BOARD;
            isQuit = true;
        } else {
            std::cout << "\n" << C_RED << "Invalid Input" 
                << C_RESET << "\n" << std::endl;
        }
        if(!isQuit && !std::cin.eof()) {
            std::cout << C_LIGHTYELLOW << USER_PROMPT << C_RESET << " ";
        }
    }

    bool is2PlayerMode = true;

    if(!std::cin.eof() && boardId == REGULAR_BOARD) {
        std::cout << std::endl;
        std::cout << C_BOLDBLUE << "Choose a mode to play" << C_RESET << std::endl;
        std::cout << C_GREEN << BREAK_LINE << C_RESET << std::endl;
        std::cout << "1. Single-player mode" << std::endl;
        std::cout << "2. Two-player mode" << std::endl;
        std::cout << C_LIGHTYELLOW << USER_PROMPT << C_RESET << " ";
        bool isQuit = false;
        std::string input;
        while(!isQuit && getline(std::cin, input)) {
            if(input == "1") {
                is2PlayerMode = false;
                isQuit = true;
            } else if(input == "2") {
                isQuit = true;
            } else {
                std::cout << "\n" << C_RED << "Invalid Input" 
                    << C_RESET << "\n" << std::endl;
            }
            if(!isQuit && !std::cin.eof()) {
                std::cout << C_LIGHTYELLOW << USER_PROMPT << C_RESET << " ";
            }
        }
    }
    if(!std::cin.eof() && is2PlayerMode) {
        std::cout << "\n" << "Enter a name for player 1" << "\n\n" << C_LIGHTYELLOW 
            << USER_PROMPT << C_RESET " ";    
        std::string player1Name;
        getline(std::cin, player1Name);
        while(player1Name.empty() && !std::cin.eof()) {
            std::cout << "\n" << C_RED << "Please enter name" << C_RESET 
                << "\n\n" << C_LIGHTYELLOW << USER_PROMPT << C_RESET " ";
            getline(std::cin, player1Name);
        }  
        if(!std::cin.eof()) {
            std::cout << "\n" << "Enter a name for player 2" << "\n\n" << C_LIGHTYELLOW 
                << USER_PROMPT << C_RESET " ";
            std::string player2Name;
            getline(std::cin, player2Name);
            while(player2Name.empty() && !std::cin.eof()) {
                std::cout << "\n" << C_RED << "Please enter name" << C_RESET 
                    << "\n\n" << C_LIGHTYELLOW << USER_PROMPT << C_RESET " ";
                getline(std::cin, player2Name);
            }
            if(!std::cin.eof()) {
                std::cout << std::endl;        
                GameManager* gm = new GameManager(player1Name, player2Name, seed, boardId);
                isEOF = gm->startGame(true);
                delete gm;
            }
        }  
    } else if(!std::cin.eof() && !is2PlayerMode) {
        std::cout << "\n" << "Enter a name for player" << "\n\n" << C_LIGHTYELLOW 
            << USER_PROMPT << C_RESET " ";    
        std::string playerName;
        getline(std::cin, playerName);
        while(playerName.empty() && !std::cin.eof()) {
            std::cout << "\n" << C_RED << "Please enter name" << C_RESET 
                << "\n\n" << C_LIGHTYELLOW << USER_PROMPT << C_RESET " ";
            getline(std::cin, playerName);
        }
        if(!std::cin.eof()) {
            std::cout << std::endl;        
            GameManager* gm = new GameManager(playerName, seed);
            isEOF = gm->startGame(true);
            delete gm;
        }
    }
    return isEOF;
}

bool loadGameFromFile() {
    bool isEOF = true;
    GameManager* gm = new GameManager();
    std::cout << "\n" << "Enter the filename from which load a game" << "\n\n" 
        << C_LIGHTYELLOW << USER_PROMPT << C_RESET " ";
    std::string filename;
    getline(std::cin, filename);
    
    while(!gm->loadGame(filename) && !std::cin.eof()) {
        if(filename.empty()) {
            std::cout << "\n" << C_RED << "Please enter file name" << 
                C_RESET << "\n\n" << C_LIGHTYELLOW << USER_PROMPT << C_RESET " ";
        } else {
            std::cout << "Please enter again" << "\n\n" 
                << C_LIGHTYELLOW << USER_PROMPT << C_RESET " ";
        }
        getline(std::cin, filename);
    }
    if(!std::cin.eof()) {
        isEOF = gm->startGame(false);
    }         
    delete gm;
    return isEOF;
}