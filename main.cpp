#include <iostream>
#include <string>
#include "StudentCredit.h"
#include "GameADT.h"
#include "Utility.h"

void printMenu();
StudentCredit* createStudentInfo();
void printDetails(StudentCredit* studentArr);

Option resolveInput(std::string input);

// Seed for generating random numbers
void processArgcs(int argc, char** argv);

int main(int argc, char** argv) {
    GameADT* game = new GameADT();
    StudentCredit* studentArr = createStudentInfo();
    printMenu();
    std::cout << USER_PROMPT << " ";
    bool isQuit = false;
    std::string input;
    
    while(!isQuit && getline(std::cin, input)) {
        switch(resolveInput(input)) {
            case Option1:
                game->newGame();
                // if one player win => isQuit = true
                break;
            case Option2: 
                game->loadGame();
                break;
            case Option3: 
                printDetails(studentArr);
                break;
            case Option4:
                isQuit = true;
                break;
            default:
                std::cout << "Invalid Input" << std::endl;
                break;
        }
        if(resolveInput(input) != Option4 && !std::cin.eof()) {
            std::cout << USER_PROMPT << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Goodbye" << std::endl;

    delete[] studentArr;
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

StudentCredit* createStudentInfo() {
    StudentCredit* student_1 = new StudentCredit("Hue Phuong Le", "s3687477@student.rmit.edu.au", "s3687477");
    StudentCredit* student_2 = new StudentCredit("Erik Olivesjoe", "s3810119@student.rmit.edu.au", "s3810119");
    StudentCredit* student_3 = new StudentCredit("Matt Meskell", "s3385819@student.rmit.edu.au", "s3385819");
    StudentCredit* studentArr = new StudentCredit[STUDENT_CREDITS_LENGTH] {*student_1, *student_2, *student_3};
    delete student_1;
    delete student_2;
    delete student_3;
    return studentArr;
}

void printDetails(StudentCredit* studentArr) {
    std::cout << "---------------------------------" << std::endl;
    for(int i = 0; i < STUDENT_CREDITS_LENGTH; i++) {
        studentArr[i].getDetails();
        std::cout << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
}

Option resolveInput(std::string input) {
    if(input == "1") {
        return Option1;
    } else if (input == "2") {
        return Option2;
    } else if (input == "3") {
        return Option3;
    } else if(input == "4") {
        return Option4;
    } else {
        return OptionInvalid;
    }
}