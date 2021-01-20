#include <iostream>
#include "Expression.hpp"

int main(int argc, char const *argv[])
{
    Expression a = Expression::parse("2 + 5 * 10");
    if (a.eval() == 52) {
        return 0;
    } else {
        return 1;
    }
}
