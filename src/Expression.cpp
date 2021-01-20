#include "Expression.hpp"
#include <algorithm>
#include <cmath>
#include <unordered_map>

static const std::unordered_map<char, Expression::operation> operations_map{
    {'+', {Expression::op_precedence::LOW, [](float a, float b) { return a + b; }}},
    {'-', {Expression::op_precedence::LOW, [](float a, float b) { return a - b; }}},
    {'*', {Expression::op_precedence::MED, [](float a, float b) { return a * b; }}},
    {'/', {Expression::op_precedence::MED, [](float a, float b) { return a / b; }}},
    {'^', {Expression::op_precedence::HIGH, [](float a, float b) { return std::pow(a, b); }}},
    {'&', {Expression::op_precedence::HIGH, [](float a, float b) { return std::pow(a, (1 / b)); }}}};

Expression::Expression(std::string symbol, std::unique_ptr<Expression> &&left, std::unique_ptr<Expression> &&right)
    : symbol(symbol), left(std::move(left)), right(std::move(right)) {}

float Expression::eval()
{
    auto current_operation = operations_map.find(symbol[0]);
    return current_operation == operations_map.end() ? std::stof(symbol) : (*current_operation).second.operation(left->eval(), right->eval());
}

Expression Expression::parse(std::string s)
{
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end()); //Remove whitespace
    return parseRec(s);
}

Expression::op_precedence Expression::precedence(char ch)
{
    auto current_op{operations_map.find(ch)};
    return current_op == operations_map.end() ? op_precedence::NON_OP : (*current_op).second.pres;
}

Expression Expression::parseRec(const std::string &s)
{
    if (s.empty())
        return Expression("0", nullptr, nullptr);

    std::string::const_iterator lowestOp = s.begin();
    int openBrackets = 0;
    for (std::string::const_iterator i = s.begin(); i != s.end(); i++)
    {
        switch (*i)
        {
        case '(':
            openBrackets++;
            break;
        case ')':
            openBrackets--;
            break;
        }
        if (openBrackets == 0)
            if (precedence(*i) < precedence(*lowestOp))
                lowestOp = i;
    }
    if (*lowestOp == '(')
        return parseRec(s.substr(1, s.length() - 2));
    else if (precedence(*lowestOp) == op_precedence::NON_OP)
        return Expression(s, nullptr, nullptr);
    else
    {
        return Expression(std::string(1, *lowestOp),
                          std::make_unique<Expression>(parseRec(s.substr(0, lowestOp - s.begin()))),
                          std::make_unique<Expression>(parseRec(s.substr(lowestOp - s.begin() + 1))));
    }
};