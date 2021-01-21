#include "Expression.hpp"
#include <algorithm>
#include <cmath>
#include <unordered_map>

enum class op_precedence
    {
        LOW,
        MED,
        HIGH,
        NON_OP
    };

struct operation
{
    op_precedence pres;
    float (*operation)(float, float);
};

static float factorial(float a) { return a <= 1 ? 1 : a * factorial(a - 1);}

static const std::unordered_map<char, operation> operations_map{
    {'+',
     {op_precedence::LOW,
      [](float a, float b) { return a + b; }}},
    {'-',
     {op_precedence::LOW,
      [](float a, float b) { return a - b; }}},
    {'*',
     {op_precedence::MED,
      [](float a, float b) { return a * b; }}},
    {'/',
     {op_precedence::MED,
      [](float a, float b) { return a / b; }}},
    {'^',
     {op_precedence::HIGH,
      [](float a, float b) { return std::pow(a, b); }}},
    {'&',
     {op_precedence::HIGH,
      [](float a, float b) { return std::pow(a, (1 / b)); }}},
    {'!',
     {op_precedence::HIGH,
      [](float a, float b) { return factorial(a); }}}};

static op_precedence precedence(char ch)
{
    auto op{operations_map.find(ch)};
    return op == operations_map.end() ? op_precedence::NON_OP : (*op).second.pres;
}


Expression::Expression(std::string symbol, std::unique_ptr<Expression> &&left,
                       std::unique_ptr<Expression> &&right)
    : symbol(symbol), left(std::move(left)), right(std::move(right)) {}

float Expression::eval()
{
    auto current_operation = operations_map.find(symbol[0]);
    if (current_operation != operations_map.end())
        return current_operation->second.operation(left->eval(), right->eval());
    else
        return std::stof(symbol);
}

Expression Expression::parse(std::string str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end()); //Remove whitespace
    return parseRec(str);
}

Expression Expression::parseRec(const std::string &str)
{
    if (str.empty())
        return Expression("0", nullptr, nullptr);

    std::string::const_iterator lowestOp = str.begin();
    int openBrackets = 0;
    for (std::string::const_iterator i = str.begin(); i != str.end(); i++)
    {
        switch (*i)
        {
        case '(':
            openBrackets++;
            break;
        case ')':
            openBrackets--;
            break;
        default:
            if (openBrackets == 0 &&
                precedence(*i) < precedence(*lowestOp))
                lowestOp = i;
            break;
        }
    }

    if (*lowestOp == '(')
        return parseRec(str.substr(1, str.length() - 2));
    else if (precedence(*lowestOp) == op_precedence::NON_OP)
        return Expression(str, nullptr, nullptr);
    else
    {
        return Expression(std::string(1, *lowestOp),
                          std::make_unique<Expression>(
                              parseRec(str.substr(0, lowestOp - str.begin()))),
                          std::make_unique<Expression>(
                              parseRec(str.substr(lowestOp - str.begin() + 1))));
    }
};