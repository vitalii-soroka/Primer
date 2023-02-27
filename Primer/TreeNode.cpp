#include "TreeNode.h"

TreeNode& TreeNode::operator=(const TreeNode& rhs) {
	++* rhs.count;
	if (-- * count == 0) {
		delete left;
		delete right;
		delete count;
	}
	value = rhs.value;
	left = rhs.left;
	right = rhs.right;
	count = rhs.count;
	return *this;

}
TreeNode::~TreeNode() {
	if (-- * count == 0) {
		delete left;
		delete right;
		delete count;
	}
}
BinStrTree& BinStrTree::operator=(const BinStrTree& rhs){
	TreeNode* new_root = new TreeNode(*rhs.root);
	delete root;
	root = new_root;
	return *this;
}