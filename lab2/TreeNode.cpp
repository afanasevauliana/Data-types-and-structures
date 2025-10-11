#include "TreeNode.h"

TreeNode::TreeNode(int value) 
    : data(value), left(nullptr), right(nullptr) {}

TreeNode::~TreeNode() {
    delete left;
    delete right;
}