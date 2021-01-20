#include "Expression.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    std::string output;
    for (size_t i = 1; i < argc; i++)
    {
        output.append(argv[i]);
    }
    std::cout << Expression::parse(output).eval() << '\n';
    return 0;
}
