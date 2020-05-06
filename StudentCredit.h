<<<<<<< HEAD
=======

>>>>>>> master
#ifndef STUDENTCREDIT_H
#define STUDENTCREDIT_H

#include <iostream>
#include <string>

<<<<<<< HEAD
#include "Types.h"
=======
#include "Utility.h"
>>>>>>> master

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