#pragma once
#include <string>

class TreeNode {
public:
    std::string data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(const std::string& value);
    ~TreeNode();
};