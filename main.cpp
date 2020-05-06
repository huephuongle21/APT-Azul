#include <iostream>
#include <string>

#include "StudentCredit.h"
#include "GameADT.h"
#include "Types.h"
#include "Player.h"

// Seed for generating random numbers
void processArgcs(int argc, char** argv);
void printMenu();
Option resolveInput(std::string input);

int main(int argc, char** argv) {
    GameADT* game = new GameADT();
    StudentCredit* studentArr = new StudentCredit();
    
    game->saveGame();
    
    printMenu();
    std::cout << USER_PROMPT << " ";
    bool isQuit = false;
    std::string input;
    
    while(!isQuit && getline(std::cin, input)) {
        Option option = resolveInput(input);
        if(option == newGame) {
            game->newGame();
        } else if(option == loadGame) {
            game->loadGame();
        } else if(option == displayCredits) {
            studentArr->printDetails();
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
    delete game;
}

void processArgcs(int argc, char** argv) {
    
}

void printMenu() {
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-------------------" << std::endl;
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
