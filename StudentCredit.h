#include <string>
#include <iostream>

class StudentCredit {
    public:

    StudentCredit(std::string name, std::string email, std::string id);

    ~StudentCredit();

    void getDetails();

    private:

    std::string name;

    std::string email;

    std::string id;

};