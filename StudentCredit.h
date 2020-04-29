
#ifndef STUDENTCREDIT_H
#define STUDENTCREDIT_H

#include <iostream>
#include <string>

#include "Utility.h"

class StudentCredit {
    public:

    StudentCredit();

    ~StudentCredit();

    void createStudentInfo();

    void printDetails();

    private:

    std::string* studentArr[STUDENT_CREDITS_LENGTH];

};

#endif // STUDENTCREDIT_H