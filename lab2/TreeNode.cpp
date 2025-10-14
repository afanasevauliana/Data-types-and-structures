#include "TreeNode.h"
#include <sstream>

TreeNode::TreeNode(const std::string& value) : data(value), left(nullptr), right(nullptr) {}

TreeNode::~TreeNode() {
    // Деструктор будет рекурсивно удалять потомков
}

bool TreeNode::isOperator() const {
    return data == "+" || data == "-" || data == "*" || data == "/";
}

bool TreeNode::isNumber() const {
    std::istringstream iss(data);
    double value;
    return (iss >> value) && iss.eof();
}

double TreeNode::getNumberValue() const {
    if (isNumber()) {
        return std::stod(data);
    }
    return 0.0;
}