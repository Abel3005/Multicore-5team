#include "Tree.h"
#include "Box.h"

TreeNode::TreeNode(Box data , TreeNode* left , TreeNode* right)
{
	this->data = data;
	this->left = left;
	this->right = right;
}
TreeNode::TreeNode(Box data)
{
	this->data = data;
	this->left = nullptr;
	this->right = nullptr;
}

TreeNode::TreeNode()
{
	this->left = nullptr;
	this->right = nullptr;
}

Tree::Tree(Box data) {
	root = new TreeNode(data);
}

Tree::Tree(TreeNode* node) {
	root = node;
}

TreeNode* Tree::getRoot() {
	return root;
}

void Tree::visit(TreeNode* current) {
	auto cur = current->data;
	//(Box)cur.drawBox(img);
}

void Tree::preorder(TreeNode* current) {
	if (current != nullptr) {
		visit(current);
		preorder(current->left);
		preorder(current->right);
	}
}

void Tree::inorder(TreeNode* current) {
	if (current != nullptr) {
		preorder(current->left);
		visit(current);
		preorder(current->right);
	}
}

void Tree::postorder(TreeNode* current) {
	if (current != nullptr) {
		preorder(current->left);
		preorder(current->right);
		visit(current);
	}
}