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
	for (int i = 0; i < 8; i++) {
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

// Giải phóng bộ nhớ
void Free(TreeNode* root) {
	if (root) {
		Free(root->left);
		Free(root->right);
		delete(root);
	}
}
// Tìm node kế tiếp của 1 node bất kỳ
TreeNode* minVal(TreeNode* root) {
	TreeNode* minNode = root;
	while (minNode && minNode->left)
		minNode = minNode->left;
	return minNode;
}

TreeNode* demoNextNode(TreeNode* root, TreeNode* node, TreeNode* nextNode) {
	if (!root)
		return NULL;
	else {
		if (root->val > node->val)
			return demoNextNode(root->left, node, root);
		else if (root->val < node->val)
			return demoNextNode(root->right, node, nextNode);
		else {
			if (node->right)
				return minVal(node->right);
			else
				return nextNode;
		}
	}
}

TreeNode* findNextNode(TreeNode* root, TreeNode* node) {
	return demoNextNode(root, node, NULL);
}
int main() {
	myTree Tree;
	createTree(Tree);
	showTreeLNR(Tree.root);
	cout << endl;
	TreeNode* node = Tree.root->left;
	TreeNode* nextNode = findNextNode(Tree.root, node);
	cout << nextNode->val;

	Free(Tree.root);
	return 0;
}