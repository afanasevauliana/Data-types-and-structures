#pragma once
#include "TreeNode.h"
#include <string>
#include <fstream>

class ExpressionTree {
private:
    TreeNode* root;
    
    void deleteTree(TreeNode* node);
    void infixTraversal(TreeNode* node, std::string& result);
    void prefixTraversal(TreeNode* node, std::string& result);
    void postfixTraversal(TreeNode* node, std::string& result);
    void printTree(TreeNode* node, int level, std::string& result);
    
public:
    ExpressionTree();
    ~ExpressionTree();
    
    void buildFromExpression(const std::string& expression);
    void buildFromFile(const std::string& filename);
    
    std::string getInfixNotation();
    std::string getPrefixNotation();
    std::string getPostfixNotation();
    std::string printTreeVisual();
    
    TreeNode* getRoot() const { return root; }
};