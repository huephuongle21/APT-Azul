#include <iostream>
#include <string>

#include "StudentCredit.h"
#include "GameADT.h"
#include "Utility.h"

// Seed for generating random numbers
void processArgcs(int argc, char** argv);
void printMenu();
Option resolveInput(std::string input);

int main(int argc, char** argv) {
    GameADT* game = new GameADT();
    StudentCredit* studentArr = new StudentCredit();
    printMenu();
    std::cout << USER_PROMPT << " ";
    bool isQuit = false;
    std::string input;
    
    while(!isQuit && getline(std::cin, input)) {
        Option option = resolveInput(input);
        if(option == Option1) {
            game->newGame();
        } else if(option == Option2) {
            game->loadGame();
        } else if(option == Option3) {
            studentArr->printDetails();
        } else if(option == Option4) {
            isQuit = true;
        } else {
            std::cout << "Invalid Input" << std::endl;
        }
        if(option != Option4 && !std::cin.eof()) {
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
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;    
}

Option resolveInput(std::string input) {
    Option option = OptionInvalid;
    if(input == "1") {
        option = Option1;
    } else if (input == "2") {
        option = Option2;
    } else if (input == "3") {
        option = Option3;
    } else if(input == "4") {
        option = Option4;
    }
    return option;
}
