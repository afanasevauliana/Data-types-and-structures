#include "Expression.h"

BinaryTree Expression::parseExpression(const std::string& expression) {
    BinaryTree tree;
    tree.buildFromExpression(expression);
    return tree;
}

bool Expression::isValidExpression(const std::string& expression) {
    int balance = 0;
    for (char c : expression) {
        if (c == '(') balance++;
        else if (c == ')') balance--;
        if (balance < 0) return false;
    }
    return balance == 0;
}