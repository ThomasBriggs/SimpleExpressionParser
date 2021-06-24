#include <iostream>
#include "Expression.hpp"

int main(int argc, char const *argv[])
{
    while (true) {
        std::string input;
        std::cin >> input;
        
        std::cout << Expression::parse(input).eval() << "\n";
    }
    return 0;
}
