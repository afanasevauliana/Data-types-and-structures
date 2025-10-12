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
        return new TreeNode(std::to_string(value));
    }
    
    int nodeValue = std::stoi(node->data);
    if (value < nodeValue) {
        node->left = insert(node->left, value);
    } else if (value > nodeValue) {
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
    if (node == nullptr) return nullptr;
    
    int nodeValue = std::stoi(node->data);
    if (nodeValue == value) {
        return node;
    }
    
    if (value < nodeValue) {
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
    
    int nodeValue = std::stoi(node->data);
    if (value < nodeValue) {
        node->left = deleteNode(node->left, value);
    } else if (value > nodeValue) {
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
        int tempValue = std::stoi(temp->data);
        node->right = deleteNode(node->right, tempValue);
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

void BinaryTree::buildExpressionTree() {
    clear();
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

void BinaryTree::infixTraversal(TreeNode* node, std::string& result) {
    if (!node) return;

    bool needsParentheses = (node->left || node->right) && 
                           (node->data == "+" || node->data == "-" || node->data == "*" || node->data == "/");
    if (needsParentheses) result += "(";
    infixTraversal(node->left, result);
    result += node->data;
    infixTraversal(node->right, result);
    if (needsParentheses) result += ")";
}

void BinaryTree::prefixTraversal(TreeNode* node, std::string& result) {
    if (!node) return;
    result += node->data + " ";
    prefixTraversal(node->left, result);
    prefixTraversal(node->right, result);
}

void BinaryTree::postfixTraversal(TreeNode* node, std::string& result) {
    if (!node) return;
    postfixTraversal(node->left, result);
    postfixTraversal(node->right, result);
    result += node->data + " ";
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

void BinaryTree::printTree(TreeNode* node, int level, std::string& result) {
    if (!node) return;
    printTree(node->left, level + 1, result);
    for (int i = 0; i < level; i++) {
        result += "    ";
    }
    result += node->data + "\n";
    printTree(node->right, level + 1, result);
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
        throw TreeException("Не удалось открыть входной файл: " + filename);
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
        throw TreeException("Не удалось открыть выходной файл: " + filename);
    }
    file << "    ИНФОРМАЦИЯ О ДЕРЕВЕ\n";
    file << "Инфиксная запись: " << getInfixNotation() << "\n";
    file << "Префиксная запись: " << getPrefixNotation() << "\n";
    file << "Постфиксная запись: " << getPostfixNotation() << "\n\n";
    file << "    ВИЗУАЛИЗАЦИЯ ДЕРЕВА\n";
    file << printTreeVisual() << "\n";
    file << "    СТАТИСТИКА\n";
    file << "Количество узлов: " << countNodes() << "\n";
    file << "Высота дерева: " << getHeight() << "\n";
    
    file.close();
}