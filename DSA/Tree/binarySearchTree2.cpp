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

// Duyệt trung tự
void showTreeLNR(TreeNode* root) {
	if (!root)
		return;
	else {
		showTreeLNR(root->left);
		cout << root->val << " ";
		showTreeLNR(root->right);
	}
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

int findLevel(TreeNode* root, int val) {
	if (!root)
		return -1;
	else {
		if (root->val > val)
			int level = 1 + findLevel(root->left, val);
		else if (root->val < val)
			int level = 1 + findLevel(root->right, val);
		else
			return 0;
	}
}

int countSmaller_K_Level(TreeNode* root, int i, int k, int& cnt) {
	if (!root)
		return 0;
	if (i < k)
		cnt++;
	countSmaller_K_Level(root->left, i + 1, k, cnt);
	countSmaller_K_Level(root->right, i + 1, k, cnt);
	return cnt;
}

TreeNode* minVal(TreeNode* root) {
	if (!root)
		return NULL;
	else {
		if (root->left)
			return minVal(root->left);
	}
}

TreeNode* maxVal(TreeNode* root) {
	if (!root)
		return NULL;
	else {
		if (root->right)
			return maxVal(root->right);
	}
}

bool checkZero(TreeNode* root) {
	if (!root)
		return 0;
	if (root->val == 0)
		return 1;
	return checkZero(root->left) || checkZero(root->right);
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

	/*int x = 0;
	cin >> x;
	showSmallerX(Tree.root, x);*/

	/*int val = 0;
	cin >> val;
	cout << findLevel(Tree.root, val);*/

	/*int k = 0, cnt = 0;
	cin >> k;
	cout << countSmaller_K_Level(Tree.root, 0, k, cnt);*/

	/*TreeNode* mini = minVal(Tree.root);
	cout << mini->val;
	cout << endl;
	TreeNode* maxi = maxVal(Tree.root);
	cout << maxi->val;*/

	cout << checkZero(Tree.root);
	
	Free(Tree.root);
	return 0;
}