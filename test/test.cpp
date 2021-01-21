#include <iostream>
#include "Expression.hpp"

int main(int argc, char const *argv[])
{
    using namespace std;
    cout << Expression::parse("3! * 2").eval() << '\n';
 }
 