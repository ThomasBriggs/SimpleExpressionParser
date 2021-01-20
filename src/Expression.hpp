#pragma once

#include <string>
#include <memory>

class Expression
{
public:
    float eval();
    static Expression parse(std::string s);

    enum class op_precedence
    {
        LOW,
        MED,
        HIGH,
        NON_OP
    };

    struct op
    {
        Expression::op_precedence pres;
        float (*operation)(float, float);
    };

private:
    std::string symbol;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    Expression(std::string symbol, std::unique_ptr<Expression> &&left, std::unique_ptr<Expression> &&right);

    static Expression parseRec(const std::string &s);
    static op_precedence precedence(char ch);
};