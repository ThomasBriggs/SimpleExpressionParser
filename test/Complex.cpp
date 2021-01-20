#include <iostream>
#include "Expression.hpp"

int main(int argc, char const *argv[])
{
    Expression a = Expression::parse("5 * 5 / 5 - 5");
    float result = a.eval();
    if (result == 0)
    {
        return 0;
    }
    else
    {
        std::cout << result << '\n';
        return 1;
    }
}