#pragma once
#include <opencv2/opencv.hpp>
#include "Box.h"
using namespace std;
class Tree;

class TreeNode {
	friend class Tree;
private:
	Box data;
public:
	TreeNode* left;
	TreeNode* right;
	TreeNode(Box data, TreeNode* left, TreeNode* right );
	TreeNode(Box data);
	TreeNode();
};

class Tree
{
private:
	TreeNode* root;
	
public:
	TreeNode* curNode;
	Tree(Box data);
	Tree(TreeNode* node);
	void buildTree();
	TreeNode* getRoot();
	void visit(TreeNode* current);
	void preorder(TreeNode* current);
	void inorder(TreeNode* current);
	void postorder(TreeNode* current);

};



