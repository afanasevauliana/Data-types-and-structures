#include "BinaryTree.h"
#include <iostream>
#include <stack>
#include <cctype>
#include <sstream>

using namespace std;

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    clear(root);
}

void BinaryTree::clear(TreeNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void BinaryTree::printTree(TreeNode* node, int level) const {
    if (node != nullptr) {
        printTree(node->right, level + 1);
        
        for (int i = 0; i < level; i++) {
            cout << "\t";
        }
        
        cout << node->data << endl;
        
        printTree(node->left, level + 1);
    }
}

void BinaryTree::print() const {
    cout << "Бинарное дерево выражения:" << endl;
    printTree(root, 0);
    cout << endl;
}

void BinaryTree::prefixTraversal(TreeNode* node, vector<string>& result) const {
    if (node) {
        result.push_back(node->data);
        prefixTraversal(node->left, result);
        prefixTraversal(node->right, result);
    }
}

void BinaryTree::infixTraversal(TreeNode* node, vector<string>& result) const {
    if (node) {
        if (node->isOperator()) result.push_back("(");
        infixTraversal(node->left, result);
        result.push_back(node->data);
        infixTraversal(node->right, result);
        if (node->isOperator()) result.push_back(")");
    }
}

void BinaryTree::postfixTraversal(TreeNode* node, vector<string>& result) const {
    if (node) {
        postfixTraversal(node->left, result);
        postfixTraversal(node->right, result);
        result.push_back(node->data);
    }
}

vector<string> BinaryTree::getPrefixNotation() const {
    vector<string> result;
    prefixTraversal(root, result);
    return result;
}

vector<string> BinaryTree::getInfixNotation() const {
    vector<string> result;
    infixTraversal(root, result);
    return result;
}

vector<string> BinaryTree::getPostfixNotation() const {
    vector<string> result;
    postfixTraversal(root, result);
    return result;
}

void BinaryTree::buildFromExpression(const string& expression) {
    // узлы
    TreeNode* multiply1 = new TreeNode("*"); // 6*3
    multiply1->left = new TreeNode("6");
    multiply1->right = new TreeNode("3");
    
    TreeNode* multiply2 = new TreeNode("*"); // 8*7
    multiply2->left = new TreeNode("8");
    multiply2->right = new TreeNode("7");
    
    TreeNode* multiply3 = new TreeNode("*"); // 6*5
    multiply3->left = new TreeNode("6");
    multiply3->right = new TreeNode("5");
    
    TreeNode* plus = new TreeNode("+"); // (6*3)+(8*7)
    plus->left = multiply1;
    plus->right = multiply2;
    
    TreeNode* multiplyRoot = new TreeNode("*"); // ((6*3)+(8*7))*(6*5)
    multiplyRoot->left = plus;
    multiplyRoot->right = multiply3;
    
    root = multiplyRoot;
}