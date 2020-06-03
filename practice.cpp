#include <iostream>

int main(void) {
    std::string b = "\u2630";
    std::cout << b << std::endl;
    std::string c = "\u2714";
    std::cout << "\033[32m" << c << std::endl;
    std::string d = "\u2716";
    std::cout << d << std::endl;
    std::string e = "\u279E";
    std::cout << e << std::endl;
    std::string f = "🖩";
    std::cout << f << std::endl;
}