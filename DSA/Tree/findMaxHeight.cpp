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
	for (int i = 0; i < 6; i++) {
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

void demoFindMax(TreeNode* root, int depth, int& maxDepth, TreeNode*& leafNode) {
	if (!root)
		return;
	else {
		if (!root->left && !root->right) {
			if (depth > maxDepth) {
				maxDepth = depth;
				leafNode = root;
			}
		}
		demoFindMax(root->left, depth + 1, maxDepth, leafNode);
		demoFindMax(root->right, depth + 1, maxDepth, leafNode);
	}
}

void findMaxDepth(TreeNode* root, TreeNode*& leafNode) {
	int maxDepth = -1e9;
	demoFindMax(root, 0, maxDepth, leafNode);
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
	myTree Tree;
	createTree(Tree);
	showTreeLNR(Tree.root);
	cout << endl;
	TreeNode* leafNode = NULL;
	findMaxDepth(Tree.root, leafNode);
	cout << leafNode->val;

	Free(Tree.root);
	return 0;
}