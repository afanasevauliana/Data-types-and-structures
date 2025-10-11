#pragma once
#include <string>

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int value);
    ~TreeNode();
};