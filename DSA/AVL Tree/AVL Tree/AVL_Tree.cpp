#include<iostream>
using namespace std;

struct AVL_Node {
	int val;
	AVL_Node* left;
	AVL_Node* right;
	int height;
};

AVL_Node* createAVL_Node(int val) {
	AVL_Node* newNode = new AVL_Node;
	newNode->val = val;
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

int getHeight(AVL_Node* root) {

	if (!root) return 0;
	int hl = 1 + getHeight(root->left);
	int hr = 1 + getHeight(root->right);
	if (hl > hr) return hl;
	else return hr;
}

void rotateRight(AVL_Node*& root) {

	if (!root || !root->left) return;
	AVL_Node* x = root->left;
	root->left = x->right;
	x->right = root;
	root->height = getHeight(root);
	x->height = getHeight(x);
	root = x;
}

void rotateLeft(AVL_Node*& root) {

	if (!root || !root->right) return;
	AVL_Node* y = root->right;
	root->right = y->left;
	y->left = root;
	root->height = getHeight(root);
	y->height = getHeight(y);
	root = y;
}

void add_AVL_Tree(AVL_Node*& root, int val) {
	if (root == NULL)
		root = createAVL_Node(val);
	else {
		if (root->val == val)
			return;
		else if (root->val < val)
			add_AVL_Tree(root->right, val);
		else if (root->val > val)
			add_AVL_Tree(root->left, val);
	}

	int height = getHeight(root);
	int valBalance = getHeight(root->left) - getHeight(root->right);

	//left-left
	if (valBalance > 1 && val < root->left->val) rotateRight(root);
	//right-right
	if (valBalance < -1 && val > root->right->val) rotateLeft(root);
	//left-right
	if (valBalance > 1 && val > root->left->val) {
		rotateLeft(root->left);
		rotateRight(root);
	}
	//right-left
	if (valBalance < -1 && val < root->right->val) {
		rotateRight(root->right);
		rotateLeft(root);
	}
}

// Tạo 1 cây 
void create_AVL_Tree(AVL_Node*& root) {
	int val;
	for (int i = 0; i < 8; i++) {
		cin >> val;
		add_AVL_Tree(root, val);
	}
}

// Duyệt và in ra cây
void showTreeLRN(AVL_Node* root) {
	if (!root)
		return;
	else {
		showTreeLRN(root->left);
		showTreeLRN(root->right);
		cout << root->val << " ";
	}
}

// Giải phóng bộ nhớ
void Free(AVL_Node* root) {
	if (root) {
		Free(root->left);
		Free(root->right);
		delete(root);
	}
}

int main() {
	AVL_Node* Tree = NULL;
	create_AVL_Tree(Tree);
	showTreeLRN(Tree);

	Free(Tree);
	return 0;
}