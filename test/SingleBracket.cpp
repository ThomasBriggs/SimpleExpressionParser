#include "Expression.hpp"

int main(int argc, char const *argv[])
{
    Expression a = Expression::parse("(2 + 3)");
    auto result = a.eval();
    if (result == 5) {
        return 0;
    } else {
        return 1;
    }
}
