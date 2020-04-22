#include "StudentCredit.h"
#include <iostream>

StudentCredit::StudentCredit(std::string name, std::string email, std::string id) {
    this->name = name;
    this->email = email;
    this->id = id;
}

StudentCredit::~StudentCredit() {

}

void StudentCredit::getDetails() {
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Student ID: " << this->id << std::endl;
    std::cout << "Email: " << this->email << std::endl;
}