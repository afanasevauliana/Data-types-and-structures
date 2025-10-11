#include "BinaryTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    destroyTree(root);
}

void BinaryTree::destroyTree(TreeNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

TreeNode* BinaryTree::insert(TreeNode* node, int value) {
    if (node == nullptr) {
        return new TreeNode(value);
    }
    
    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    
    return node;
}

void BinaryTree::insert(int value) {
    root = insert(root, value);
}

TreeNode* BinaryTree::findMin(TreeNode* node) {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

TreeNode* BinaryTree::findMin() {
    return findMin(root);
}

TreeNode* BinaryTree::findMax(TreeNode* node) {
    if (node == nullptr) return nullptr;
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

TreeNode* BinaryTree::findMax() {
    return findMax(root);
}

TreeNode* BinaryTree::search(TreeNode* node, int value) {
    if (node == nullptr || node->data == value) {
        return node;
    }
    
    if (value < node->data) {
        return search(node->left, value);
    } else {
        return search(node->right, value);
    }
}

TreeNode* BinaryTree::search(int value) {
    return search(root, value);
}

TreeNode* BinaryTree::deleteNode(TreeNode* node, int value) {
    if (node == nullptr) return nullptr;
    
    if (value < node->data) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->data) {
        node->right = deleteNode(node->right, value);
    } else {
        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        TreeNode* temp = findMin(node->right);
        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data);
    }
    
    return node;
}

void BinaryTree::deleteNode(int value) {
    root = deleteNode(root, value);
}

void BinaryTree::clear() {
    destroyTree(root);
    root = nullptr;
}

void BinaryTree::infixTraversal(TreeNode* node, std::string& result) { // обходы дерева
    if (!node) return;
    
    if (node->left) {
        result += "(";
        infixTraversal(node->left, result);
    }
    
    result += std::to_string(node->data);
    
    if (node->right) {
        infixTraversal(node->right, result);
        result += ")";
    }
}

void BinaryTree::prefixTraversal(TreeNode* node, std::string& result) {
    if (!node) return;
    
    result += std::to_string(node->data) + " ";
    prefixTraversal(node->left, result);
    prefixTraversal(node->right, result);
}

void BinaryTree::postfixTraversal(TreeNode* node, std::string& result) {
    if (!node) return;
    
    postfixTraversal(node->left, result);
    postfixTraversal(node->right, result);
    result += std::to_string(node->data) + " ";
}

std::string BinaryTree::getInfixNotation() {
    std::string result;
    infixTraversal(root, result);
    return result;
}

std::string BinaryTree::getPrefixNotation() {
    std::string result;
    prefixTraversal(root, result);
    return result;
}

std::string BinaryTree::getPostfixNotation() {
    std::string result;
    postfixTraversal(root, result);
    return result;
}

void BinaryTree::printTree(TreeNode* node, int level, std::string& result) { // визуализация дерева
    if (!node) return;
    
    printTree(node->right, level + 1, result);
    
    for (int i = 0; i < level; i++) {
        result += "   ";
    }
    result += std::to_string(node->data) + "\n";
    
    printTree(node->left, level + 1, result);
}

std::string BinaryTree::printTreeVisual() {
    std::string result;
    printTree(root, 0, result);
    return result;
}

int BinaryTree::getHeight(TreeNode* node) {
    if (node == nullptr) return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

int BinaryTree::getHeight() {
    return getHeight(root);
}

int BinaryTree::countNodes(TreeNode* node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int BinaryTree::countNodes() {
    return countNodes(root);
}

void BinaryTree::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file: " + filename);
    }
    
    clear();
    
    int value;
    while (file >> value) {
        insert(value);
    }
    
    file.close();
}

void BinaryTree::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }
    
    file << "Дерево: " << getInfixNotation() << "\n";
    file << "Визуализация:\n" << printTreeVisual();
    file << "Количество узлов: " << countNodes() << "\n";
    file << "Высота: " << getHeight() << "\n";
    
    file.close();
}