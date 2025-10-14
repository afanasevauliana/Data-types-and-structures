#include "BinarySearchTree.h"
#include <iostream>
#include <limits>

using namespace std;

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    clear(root);
}

void BinarySearchTree::clear(TreeNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void BinarySearchTree::clear() {
    clear(root);
    root = nullptr;
}

// Добавление вершины (из методички)
TreeNode* BinarySearchTree::insert(TreeNode* node, int value) {
    if (node == nullptr) {
        return new TreeNode(to_string(value));
    }
    
    if (value < node->getNumberValue()) {
        node->left = insert(node->left, value);
    } else if (value > node->getNumberValue()) {
        node->right = insert(node->right, value);
    }
    
    return node;
}

void BinarySearchTree::insert(int value) {
    root = insert(root, value);
}

// Поиск минимума (из методички)
TreeNode* BinarySearchTree::findMin(TreeNode* node) {
    if (node == nullptr || node->left == nullptr) {
        return node;
    }
    return findMin(node->left);
}

int BinarySearchTree::findMin() {
    TreeNode* minNode = findMin(root);
    return minNode ? minNode->getNumberValue() : numeric_limits<int>::min();
}

// Поиск максимума (из методички)
TreeNode* BinarySearchTree::findMax(TreeNode* node) {
    if (node == nullptr || node->right == nullptr) {
        return node;
    }
    return findMax(node->right);
}

int BinarySearchTree::findMax() {
    TreeNode* maxNode = findMax(root);
    return maxNode ? maxNode->getNumberValue() : numeric_limits<int>::max();
}

// Поиск вершины (из методички)
TreeNode* BinarySearchTree::search(TreeNode* node, int value) {
    if (node == nullptr || node->getNumberValue() == value) {
        return node;
    }
    
    if (value < node->getNumberValue()) {
        return search(node->left, value);
    } else {
        return search(node->right, value);
    }
}

bool BinarySearchTree::search(int value) {
    return search(root, value) != nullptr;
}

// Удаление вершины (из методички)
TreeNode* BinarySearchTree::remove(TreeNode* node, int value) {
    if (node == nullptr) return nullptr;
    
    if (value < node->getNumberValue()) {
        node->left = remove(node->left, value);
    } else if (value > node->getNumberValue()) {
        node->right = remove(node->right, value);
    } else {
        // Найден узел для удаления
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        } else {
            // У узла два потомка
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->getNumberValue());
        }
    }
    return node;
}

void BinarySearchTree::remove(int value) {
    root = remove(root, value);
}

// Вывод дерева (из методички)
void BinarySearchTree::printTree(TreeNode* node, int level) const {
    if (node != nullptr) {
        printTree(node->right, level + 1);
        for (int i = 0; i < level; i++) {
            cout << "    ";
        }
        cout << node->data << endl;
        printTree(node->left, level + 1);
    }
}

void BinarySearchTree::print() {
    cout << "Двоичное дерево поиска:" << endl;
    printTree(root, 0);
    cout << endl;
}