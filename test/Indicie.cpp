#include <iostream>
#include "Expression.hpp"

int main(int argc, char const *argv[])
{
    Expression a = Expression::parse("2 ^ 2 * 4");
    if (a.eval() == 16) {
        return 0;
    } else {
        return 1;
    }
}