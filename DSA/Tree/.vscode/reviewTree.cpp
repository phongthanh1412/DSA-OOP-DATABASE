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
	for (int i = 0; i < 15; i++) {
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
		showTreeLNR(root->right);
		cout << root->val << " ";
	}
}
// Xoá 1 nút trong cây
void findDummy(TreeNode*& toDelete, TreeNode*& dummy) {
	while (dummy->left) {
		dummy = dummy->left;
	}
	toDelete->val = dummy->val;
}

TreeNode* deleteTreeNode(TreeNode* root, int key) {
	if (!root)
		return nullptr;

	if (root->val > key) {
		root->left = deleteTreeNode(root->left, key);
	}
	else if (root->val < key) {
		root->right = deleteTreeNode(root->right, key);
	}
	else {
		if (!root->left) {
			TreeNode* temp = root->right;
			delete root;
			return temp;
		}
		else if (!root->right) {
			TreeNode* temp = root->left;
			delete root;
			return temp;
		}
		else {
			TreeNode* dummy = root->right;
			findDummy(root, dummy);
			root->right = deleteTreeNode(root->right, dummy->val);
		}
	}
	return root;
}
// Đếm số nút của cây nhị phân tìm kiếm 
// Cách 1
// Đếm số nút lá
int countLeafTreeNode(TreeNode* root) {
	int cnt = 0;
	if (!root)
		return 0;
	if (!root->left && !root->right)
		return 1;
	if (root->left)
		cnt = countLeafTreeNode(root->left);
	if (root->right)
		cnt = cnt + countLeafTreeNode(root->right);
	return cnt;
}
// Đếm số nút có 1 con
int countTreeNode1(TreeNode* root) {
	int cnt = 0;
	if (!root)
		return 0;
	if (!root->left && !root->right)
		return 0;
	if (root->left && root->right)
		cnt = 0;
	else
		cnt = 1;
	cnt = cnt + countTreeNode1(root->left) + countTreeNode1(root->right);
	return cnt;

}
// Đếm số nút có 2 con
int countTreeNode2(TreeNode* root) {
	int cnt = 0;
	if (!root)
		return 0;
	if (!root->left && !root->right)
		return 0;
	if (root->left && root->right)
		cnt = 1;
	else
		cnt = 0;
	cnt = cnt + countTreeNode2(root->left) + countTreeNode2(root->right);
	return cnt;

}
// Cách 2
void countTreeNode(TreeNode* root, int& cnt1, int& cnt2, int& cnt3) {
	if (!root)
		return;
	else {
		countTreeNode(root->left, cnt1, cnt2, cnt3);
		if (!root->left && !root->right)
			cnt1++;
		else if (!root->left || !root->right)
			cnt2++;
		else
			cnt3++;
		countTreeNode(root->right, cnt1, cnt2, cnt3);
	}
}
// Tìm 1 TreeNode xuất hiện trong cây
TreeNode* findTreeNode(TreeNode* root, int k) {
	if (!root)
		return NULL;
	if (root->val > k)
		return findTreeNode(root->left, k);
	else if (root->val < k)
		return findTreeNode(root->right, k);
}
// Tìm chiều cao của cây 
int findHeight(TreeNode* root) {
	if (!root)
		return 0;
	else {
		int hl = 1 + findHeight(root->left);
		int hr = 1 + findHeight(root->right);
		if (hl > hr)
			return hl;
		else
			return hr;
	}
}
// Hiển thị các node ở mức K của cây
void showK(TreeNode* root, int i, int k) {
	if (!root)
		return;
	else {
		i++;
		showK(root->left, i, k);
		if (i == k)
			cout << root->val << " ";
		showK(root->right, i, k);
	}
}
// Kiểm tra một cây nhị phân có phải cây nhị phân tìm kiếm không
bool isBST(TreeNode* root, int mini, int maxi) {
	if (!root)
		return 1;
	if (root->val <= mini || root->val >= maxi)
		return 0;
	return isBST(root->left, mini, root->val) && isBST(root->left, root->val, maxi);
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
	/*if (isBST(Tree.root, -1e9, 1e9))
		cout << "Binary search tree!";
	else cout << "Not Binary search tree!";
	cout << endl;

	int k = 0;
	cin >> k;
	TreeNode* TreeNode = findTreeNode(Tree.root, k);
	cout << TreeNode->val;
	deleteTreeNode(Tree.root, k);
	showTreeLNR(Tree.root);

	int cnt1 = 0, cnt2 = 0, cnt3 = 0;
	countTreeNode(Tree.root, cnt1, cnt2, cnt3);
	cout << cnt1 << endl;
	cout << cnt2 << endl;
	cout << cnt3 << endl;

	cout << findHeight(Tree.root);

	showK(Tree.root, -1, k);*/

	Free(Tree.root);
	return 0;
}