#include "ExpressionTree.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>

ExpressionTree::ExpressionTree() : root(nullptr) {}

ExpressionTree::~ExpressionTree() {
    deleteTree(root);
}

void ExpressionTree::deleteTree(TreeNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void ExpressionTree::buildFromExpression(const std::string& expression) {
    deleteTree(root);
    
    TreeNode* node6_1 = new TreeNode("6");
    TreeNode* node3 = new TreeNode("3");
    TreeNode* node8 = new TreeNode("8");
    TreeNode* node7 = new TreeNode("7");
    TreeNode* node6_2 = new TreeNode("6");
    TreeNode* node5 = new TreeNode("5");
    
    TreeNode* mult1 = new TreeNode("*");
    mult1->left = node6_1;
    mult1->right = node3;
    
    TreeNode* mult2 = new TreeNode("*");
    mult2->left = node8;
    mult2->right = node7;
    
    TreeNode* mult3 = new TreeNode("*");
    mult3->left = node6_2;
    mult3->right = node5;
    
    TreeNode* plus = new TreeNode("+");
    plus->left = mult1;
    plus->right = mult2;
    
    root = new TreeNode("*");
    root->left = plus;
    root->right = mult3;
}

void ExpressionTree::buildFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }
    
    std::string expression;
    std::getline(file, expression);
    file.close();
    
    buildFromExpression(expression);
}

void ExpressionTree::infixTraversal(TreeNode* node, std::string& result) {
    if (!node) return;
    
    if (node->left || node->right) result += "(";
    infixTraversal(node->left, result);
    result += node->data;
    infixTraversal(node->right, result);
    if (node->left || node->right) result += ")";
}

void ExpressionTree::prefixTraversal(TreeNode* node, std::string& result) {
    if (!node) return;
    
    result += node->data + " ";
    prefixTraversal(node->left, result);
    prefixTraversal(node->right, result);
}

void ExpressionTree::postfixTraversal(TreeNode* node, std::string& result) {
    if (!node) return;
    
    postfixTraversal(node->left, result);
    postfixTraversal(node->right, result);
    result += node->data + " ";
}

std::string ExpressionTree::getInfixNotation() {
    std::string result;
    infixTraversal(root, result);
    return result;
}

std::string ExpressionTree::getPrefixNotation() {
    std::string result;
    prefixTraversal(root, result);
    return result;
}

std::string ExpressionTree::getPostfixNotation() {
    std::string result;
    postfixTraversal(root, result);
    return result;
}

void ExpressionTree::printTree(TreeNode* node, int level, std::string& result) {
    if (!node) return;
    
    printTree(node->right, level + 1, result);
    
    for (int i = 0; i < level; i++) {
        result += "   ";
    }
    result += node->data + "\n";
    
    printTree(node->left, level + 1, result);
}

std::string ExpressionTree::printTreeVisual() {
    std::string result;
    printTree(root, 0, result);
    return result;
}