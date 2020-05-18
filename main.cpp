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
void startNewGame();
void loadGameFromFile();

int main(int argc, char** argv) {

    StudentCredit* studentArr = new StudentCredit();
    
    printMenu();
    std::cout << USER_PROMPT << " ";
    bool isQuit = false;
    std::string input;
    
    while(!isQuit && getline(std::cin, input)) {
        Option option = resolveInput(input);
        if(option == newGame) {
            startNewGame();
        } else if(option == loadGame) {
            loadGameFromFile();
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

void startNewGame() {
    std::cout << "Starting a New Game" << "\n" << std::endl;

    std::cout << "Enter a name for player 1" << "\n" << USER_PROMPT << " ";    
    std::string player1Name;
    getline(std::cin, player1Name);
    while(player1Name.empty()) {
        std::cout << "Please enter name" << "\n" << USER_PROMPT << " ";
        getline(std::cin, player1Name);
    }

    std::cout << "Enter a name for player 2" << "\n" << USER_PROMPT << " ";
    std::string player2Name;
    getline(std::cin, player2Name);
    while(player2Name.empty()) {
        std::cout << "Please enter name" << "\n" << USER_PROMPT << " ";
        getline(std::cin, player2Name);
    }

    std::cout << std::endl;

    GameManager* gm = new GameManager(player1Name, player2Name);
    gm->startGame(true);

    delete gm;

}

void loadGameFromFile() {
    GameManager* gm = new GameManager();
    std::cout << "Enter the filename from which load a game" << "\n" << USER_PROMPT << " ";
    std::string filename;
    getline(std::cin, filename);
    while(!gm->loadGame(filename)) {
        std::cout << "File does not exist. Please enter again" << "\n" << USER_PROMPT << " ";
        getline(std::cin, filename);
    }
    gm->startGame(false);
            
    delete gm;

}
