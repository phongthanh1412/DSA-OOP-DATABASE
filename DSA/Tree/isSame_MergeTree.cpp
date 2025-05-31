#include<iostream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

struct myTree {
	TreeNode* root;
};

// Khởi tạo 1 cây rỗng
void init(myTree& Tree) {
	Tree.root = NULL;
}
// Tạo 1 TreeNode
TreeNode* createTreeNode(int val) {
	TreeNode* newTreeNode = new TreeNode;
	newTreeNode->val = val;
	newTreeNode->left = NULL;
	newTreeNode->right = NULL;
	return newTreeNode;
}
// Thêm TreeNode vào cây
void addTreeNode(TreeNode*& root, int val) {
	if (root == NULL)
		root = createTreeNode(val);
	else {
		if (root->val == val)
			return;
		else if (root->val < val)
			addTreeNode(root->right, val);
		else if (root->val > val)
			addTreeNode(root->left, val);
	}
}
// Tạo 1 cây 
void createTree(myTree& Tree) {
	init(Tree);
	int val;
	for (int i = 0; i < 5; i++) {
		cin >> val;
		addTreeNode(Tree.root, val);
	}
}

// Duyệt và in ra cây
void showTreeLNR(TreeNode* root) {
	if (!root)
		return;
	else {
		showTreeLNR(root->left);
		cout << root->val << " ";
		showTreeLNR(root->right);
	}
}

TreeNode* insertIntoBST(TreeNode* root, int val) {
	if (!root) {
		TreeNode* newNode = createTreeNode(val);
		return newNode;
	}
	if (root->val > val) {
		root->left = insertIntoBST(root->left, val);
	}
	else
		root->right = insertIntoBST(root->right, val);
	return root;
}
void demoAddNode(TreeNode*& root, TreeNode*& newNode) {
	if (!root)
		return;
	else {
		demoAddNode(root->left, newNode);
		newNode = insertIntoBST(newNode, root->val);
		demoAddNode(root->right, newNode);
	}
}

TreeNode* mergeTree(TreeNode*& root1, TreeNode*& root2) {
	TreeNode* newNode = NULL;
	demoAddNode(root1, newNode);
	demoAddNode(root2, newNode);
	return newNode;
}
bool isSameTree(TreeNode*& root1, TreeNode*& root2) {
	if (!root1 && !root2)
		return 1;
	if (!root1 || !root2)
		return 0;
	return (root1->val == root2->val) 
		&& isSameTree(root1->left, root2->left) 
		&& isSameTree(root1->right, root2->right);
}

void showSmallerX(TreeNode* root, int val) {
	if (!root)
		return;
	else {
		showSmallerX(root->left, val);
		if (root->val <= val)
			cout << root->val << " ";
		showSmallerX(root->right, val);
	}
}
// Giải phóng bộ nhớ
void Free(TreeNode* root) {
	if (root) {
		Free(root->left);
		Free(root->right);
		delete(root);
	}
}
int main() {
	myTree Tree1, Tree2;
	createTree(Tree1);
	showTreeLNR(Tree1.root);
	cout << endl;
	createTree(Tree2);
	showTreeLNR(Tree2.root);
	cout << endl;
	/*if (isSameTree(Tree1.root, Tree2.root))
		cout << "Tree1 is the same as Tree2!";
	else 
		cout << "Tree1 is not the same as Tree2!";*/
	TreeNode* newNode = mergeTree(Tree1.root, Tree2.root);
	showTreeLNR(newNode);

	Free(newNode);
	Free(Tree2.root);
	Free(Tree1.root);
	return 0;
}