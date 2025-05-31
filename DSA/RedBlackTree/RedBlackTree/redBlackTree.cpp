#include <iostream>
using namespace std;

enum COLOR { red, black };

struct RBTreeNode {
	int val;
	COLOR color;
	RBTreeNode* left;
	RBTreeNode* right;
	RBTreeNode* parent;
};

struct RBTree {
	RBTreeNode* ROOT;
	RBTree() {
		ROOT = NULL;
	}
};

RBTreeNode* createRBTreeNode(int val) {
	RBTreeNode* newNode = new RBTreeNode;
	newNode->val = val;
	newNode->color = red;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	return newNode;
}

void rightRotate(RBTreeNode*& root, RBTree& Tree) {
	if (!root || !root->left) return;
	RBTreeNode* x = root->left;
	root->left = x->right;
	if (x->right) x->right->parent = root;
	x->parent = root->parent;
	if (!root->parent) Tree.ROOT = x;
	else if (root == root->parent->left) root->parent->left = x;
	else root->parent->right = x;
	x->right = root;
	root->parent = x;
}

void leftRotate(RBTreeNode*& root, RBTree& Tree) {
	if (!root || !root->right) return;
	RBTreeNode* y = root->right;
	root->right = y->left;
	if (y->left) y->left->parent = root;
	y->parent = root->parent;
	if (!root->parent) Tree.ROOT = y;
	else if (root == root->parent->right) root->parent->right = y;
	else root->parent->left = y;
	y->left = root;
	root->parent = y;
}

void fixedInsert(RBTreeNode*& newNode, RBTree& Tree) {
	while (newNode != Tree.ROOT && newNode->parent->color == red) {
		if (newNode->parent == newNode->parent->parent->left) {
			RBTreeNode* uncle = newNode->parent->parent->right;
			if (uncle && uncle->color == red) {
				newNode->parent->parent->color = red;
				newNode->parent->color = black;
				uncle->color = black;
				newNode = newNode->parent->parent;
			}
			else {
				if (newNode == newNode->parent->right) {
					newNode = newNode->parent;
					leftRotate(newNode, Tree);
				}
				newNode->parent->color = black;
				newNode->parent->parent->color = red;
				rightRotate(newNode->parent->parent, Tree);
			}
		}
		else {
			RBTreeNode* uncle = newNode->parent->parent->left;
			if (uncle && uncle->color == red) {
				newNode->parent->parent->color = red;
				newNode->parent->color = black;
				uncle->color = black;
				newNode = newNode->parent->parent;
			}
			else {
				if (newNode == newNode->parent->left) {
					newNode = newNode->parent;
					rightRotate(newNode, Tree);
				}
				newNode->parent->color = black;
				newNode->parent->parent->color = red;
				leftRotate(newNode->parent->parent, Tree);
			}
		}
	}
	Tree.ROOT->color = black;
}

RBTreeNode* addRBTreeNode(RBTreeNode*& root, int val) {
	if (!root) {
		root = createRBTreeNode(val);
		return root;
	}
	else {
		RBTreeNode* newNode = NULL;
		if (root->val == val) return NULL;
		else if (root->val < val) newNode = addRBTreeNode(root->right, val);
		else if (root->val > val) newNode = addRBTreeNode(root->left, val);
		if (newNode) newNode->parent = root;
	}
}

void createRBTree(RBTreeNode*& root, RBTree& Tree) {
	int val;
	for (int i = 0; i < 8; i++) {
		cin >> val;
		RBTreeNode* newNode = addRBTreeNode(Tree.ROOT, val);
		if (newNode) fixedInsert(newNode, Tree);
	}
}

void showTreeLRN(RBTreeNode* root) {
	if (!root)
		return;
	else {
		showTreeLRN(root->left);
		showTreeLRN(root->right);
		cout << root->val << " ";
	}
}

void Free(RBTreeNode* root) {
	if (root) {
		Free(root->left);
		Free(root->right);
		delete(root);
	}
}

int main() {
	RBTree Tree;
	createRBTree(Tree.ROOT, Tree);
	showTreeLRN(Tree.ROOT);

	Free(Tree.ROOT);
	return 0;
}
