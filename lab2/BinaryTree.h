#pragma once
#include "TreeNode.h"
#include <string>
#include <vector>

class BinaryTree {
private:
    TreeNode* root;
    
    void clear(TreeNode* node);
    void printTree(TreeNode* node, int level) const;
    void prefixTraversal(TreeNode* node, std::vector<std::string>& result) const;
    void infixTraversal(TreeNode* node, std::vector<std::string>& result) const;
    void postfixTraversal(TreeNode* node, std::vector<std::string>& result) const;
    
public:
    BinaryTree();
    ~BinaryTree();
    
    void buildFromExpression(const std::string& expression);
    void print() const;
    
    std::vector<std::string> getPrefixNotation() const;
    std::vector<std::string> getInfixNotation() const; 
    std::vector<std::string> getPostfixNotation() const;
    
    TreeNode* getRoot() const { return root; }
};