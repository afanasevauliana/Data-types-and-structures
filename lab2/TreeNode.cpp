#include "TreeNode.h"

TreeNode::TreeNode(const std::string& value) 
    : data(value), left(nullptr), right(nullptr) {}

TreeNode::~TreeNode() {
    delete left;
    delete right;
}