#pragma once
#include <string>

class TreeNode {
public:
    std::string data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(const std::string& value);
    ~TreeNode();
    
    bool isOperator() const;
    bool isNumber() const;
    double getNumberValue() const;
};