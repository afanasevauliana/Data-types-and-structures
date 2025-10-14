#pragma once
#include "BinaryTree.h"
#include <string>

class Expression {
public:
    static BinaryTree parseExpression(const std::string& expression);
    static bool isValidExpression(const std::string& expression);
};