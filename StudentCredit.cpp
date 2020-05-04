#include "StudentCredit.h"

StudentCredit::StudentCredit() {
    for(int i = 0; i != STUDENT_CREDITS_LENGTH; ++i) {
        this->studentArr[i] = nullptr;
    }

    createStudentInfo();
}

StudentCredit::~StudentCredit() {
    for(int i = 0; i != STUDENT_CREDITS_LENGTH; ++i) {
        if(studentArr[i] != nullptr) {
            delete studentArr[i];
            this->studentArr[i] = nullptr;
        }
    }
}

 void StudentCredit::createStudentInfo() {
    std::string* student_1 = new std::string ("Name: Hue Phuong Le \nEmail: s3687477@student.rmit.edu.au \nStudent ID: s3687477\n");
    std::string* student_2 = new std::string ("Name: Erik Olivesjoe \ns3810119@student.rmit.edu.au \nStudent ID: s3810119\n");
    std::string* student_3 = new std::string ("Name: Matt Meskell \nEmail: s3385819@student.rmit.edu.au \nStudent ID: s3385819\n");

    studentArr[0] = student_1;
    studentArr[1] = student_2;
    studentArr[2] = student_3;
}

void StudentCredit::printDetails() {
    std::cout << "---------------------------------" << std::endl;
    for(int i = 0; i < STUDENT_CREDITS_LENGTH; i++) {
        std::cout << *studentArr[i] << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
}