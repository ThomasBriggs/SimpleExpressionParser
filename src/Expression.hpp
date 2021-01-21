#pragma once

#include <string>
#include <memory>

class Expression
{
public:
    float eval();
    static Expression parse(std::string s);

private:
    std::string symbol;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    Expression(std::string symbol, std::unique_ptr<Expression> &&left,
               std::unique_ptr<Expression> &&right);

    static Expression parseRec(const std::string &str);
};