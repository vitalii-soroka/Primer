#ifndef TreeNode_h
#define TreeNode_h

#pragma once
#include <string>
#include <iostream>

// Value like Tree Node class
class TreeNode {
public:
	TreeNode() : value(), count(new int(1)), left(nullptr), right(nullptr) {}
	TreeNode(std::string val) : value(val), count(new int(1)), left(nullptr), right(nullptr) {}
	TreeNode(const TreeNode& rhs) :
		value(rhs.value), count(rhs.count),
		left(rhs.left), right(rhs.right) {
		++* count;
	}
	TreeNode& operator=(const TreeNode&);
	~TreeNode();
private:
	std::string value;
	int		*	count;
	TreeNode*	left;
	TreeNode*	right;
};
class BinStrTree {
public:
	BinStrTree(): root(new TreeNode()){}
	BinStrTree(const BinStrTree& bst) :
		root(new TreeNode(*bst.root)){}
	BinStrTree& operator=(const BinStrTree&);
	~BinStrTree() { delete root; }
private:
	TreeNode* root;
};

#endif // 