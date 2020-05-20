#include <iostream>
#include <string>

#include "StudentCredit.h"
#include "GameManager.h"
#include "Types.h"
#include "Player.h"

// Seed for generating random numbers
void processArgcs(int argc, char** argv);
void printMenu();
Option resolveInput(std::string input);
bool startNewGame();
bool loadGameFromFile();

int main(int argc, char** argv) {

    StudentCredit* studentArr = new StudentCredit();

    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-------------------" << std::endl;
    
    printMenu();
    std::cout << USER_PROMPT << " ";
    bool isQuit = false;
    std::string input;
    
    while(!isQuit && getline(std::cin, input)) {
        Option option = resolveInput(input);
        if(option == newGame) {
            if(!startNewGame()) {
                printMenu();
            }
        } else if(option == loadGame) {
            if(!loadGameFromFile()) {
                printMenu();
            }
        } else if(option == displayCredits) {
            studentArr->printDetails();
            printMenu();
        } else if(option == quit) {
            isQuit = true;
        } else {
            std::cout << "Invalid Input" << std::endl;
        }
        if(option != quit && !std::cin.eof()) {
            std::cout << USER_PROMPT << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Goodbye" << std::endl;

    delete studentArr;

}

void processArgcs(int argc, char** argv) {
    
}

void printMenu() {
    std::cout << std::endl;
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Display Credits" << std::endl;
    std::cout << "4. Quit" << std::endl;    
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

bool startNewGame() {
    bool isEOF = true;
    std::cout << "Starting a New Game" << "\n" << std::endl;

    std::cout << "Enter a name for player 1" << "\n" << USER_PROMPT << " ";    
    std::string player1Name;
    getline(std::cin, player1Name);
    while(player1Name.empty() && !std::cin.eof()) {
        std::cout << "Please enter name" << "\n" << USER_PROMPT << " ";
        getline(std::cin, player1Name);
    }
    if(!std::cin.eof()) {
        std::cout << "Enter a name for player 2" << "\n" << USER_PROMPT << " ";
        std::string player2Name;
        getline(std::cin, player2Name);
        while(player2Name.empty() && !std::cin.eof()) {
            std::cout << "Please enter name" << "\n" << USER_PROMPT << " ";
            getline(std::cin, player2Name);
        }
        if(!std::cin.eof()) {
            std::cout << std::endl;        
            GameManager* gm = new GameManager(player1Name, player2Name);
            isEOF = gm->startGame(true);
            delete gm;
        }
    }  
    return isEOF;
}

bool loadGameFromFile() {
    bool isEOF = true;
    GameManager* gm = new GameManager();
    std::cout << "Enter the filename from which load a game" << "\n" << USER_PROMPT << " ";
    std::string filename;
    getline(std::cin, filename);
    while(!gm->loadGame(filename) && !std::cin.eof()) {
        std::cout << "File does not exist. Please enter again" << "\n" << USER_PROMPT << " ";
        getline(std::cin, filename);
    }
    if(!std::cin.eof()) {
        isEOF = gm->startGame(false);
    }
            
    delete gm;

    return isEOF;
}
