#pragma once
#include "TreeNode.h"
#include <vector>

class BinarySearchTree {
private:
    TreeNode* root;
    
    void clear(TreeNode* node);
    TreeNode* insert(TreeNode* node, int value);
    TreeNode* remove(TreeNode* node, int value);
    TreeNode* findMin(TreeNode* node);
    TreeNode* findMax(TreeNode* node);
    TreeNode* search(TreeNode* node, int value);
    void printTree(TreeNode* node, int level) const;
    void inOrderTraversal(TreeNode* node, std::vector<int>& result) const;
    
public:
    BinarySearchTree();
    ~BinarySearchTree();
    
    void insert(int value);
    void remove(int value);
    bool search(int value);
    int findMin();
    int findMax();
    void print();
    void clear();
    
    TreeNode* getRoot() const { return root; }
};