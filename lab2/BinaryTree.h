#pragma once
#include "TreeNode.h"
#include <string>
#include <fstream>

class BinaryTree {
private:
    TreeNode* root;
    TreeNode* insert(TreeNode* node, int value);
    TreeNode* deleteNode(TreeNode* node, int value);
    TreeNode* findMin(TreeNode* node);
    TreeNode* findMax(TreeNode* node);
    TreeNode* search(TreeNode* node, int value);
    void destroyTree(TreeNode* node);
    void printTree(TreeNode* node, int level, std::string& result);
    void infixTraversal(TreeNode* node, std::string& result);
    void prefixTraversal(TreeNode* node, std::string& result);
    void postfixTraversal(TreeNode* node, std::string& result);
    int countNodes(TreeNode* node);
    int getHeight(TreeNode* node);
    
public:
    BinaryTree();
    ~BinaryTree();
    
    void insert(int value);
    void deleteNode(int value);
    TreeNode* search(int value);
    TreeNode* findMin();
    TreeNode* findMax();
    void clear();
    
    std::string getInfixNotation();
    std::string getPrefixNotation();
    std::string getPostfixNotation();
    
    std::string printTreeVisual();
    int getHeight();
    int countNodes();
    bool isEmpty() const { return root == nullptr; }
    
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    
    TreeNode* getRoot() const { return root; }
};