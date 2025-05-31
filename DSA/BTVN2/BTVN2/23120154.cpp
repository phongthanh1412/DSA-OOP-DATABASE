//
// Template cho Homework 2 - AVL
//
// Miêu tả homework:
// Trong Homework 2, sinh viên sẽ cài đặt lại cây AVL cùng một số thao tác cơ bản trên cây AVL
// i.e. chèn node, xóa node, duyệt cây, ..etc.
//
// Cách thức chấm điểm:
// Bài làm sẽ được chấm trên nhiều testcase, mỗi testcase là một tập tin .txt gồm 3 dòng: 
//
// Ví dụ:
//
// 10 3
// 3 4 2 7 6 8 19 22 1 9
// 2 19 1
//
// Trong đó
// - Dòng đầu tiên gồm 2 số nguyên dương n and k:
//    - n: tổng số node của cây
//    - k: tổng số node sẽ bị xóa khỏi cây.
//
// - Dòng thứ 2 gồm n số nguyên dương phân biệt bởi dấu khoảng trắng -- giá trị các node chèn vào cây.
// - Dòng thứ 3 gồm k số nguyên dương phân biệt bởi dấu khoảng trắng -- giá trị các node được xóa khỏi cây.
//
// Ví dụ: input_sample.txt
//
// Hướng dẫn:
// 1. Điền code vào các mục <// TODO: YOUR CODE HERE>.
// 2. Không nên chỉnh sửa các đoạn code trong mục <// DO NOT MODIFY CODE INSIDE THIS ZONE>
//    để tránh trường hợp gây bug cho trình chấm.
// 3. Sinh viên có thể viết thêm hàm, nhưng không được chỉnh sửa các nguyên mẫu hàm/struct đã có.
// 4. Sinh viên có thể chỉnh sửa hàm main() để test, nhưng lưu ý phải restore lại hàm main() ban đầu
//    trước khi nộp bài. 
//
// Have fun!
// Last updated: Jul 24, 2024.
//

#include<iostream>
#include<cassert>
#include<vector>
#include<queue>
#include<math.h>

using namespace std;

// ---------------------------------------------------
// DO NOT MODIFY CODE INSIDE THIS ZONE

struct NODE {
    int key;
    NODE* pLeft;
    NODE* pRight;
    int height;
};

// Destroy a tree.
void demolishTree(NODE*& pRoot) {
    if (pRoot == NULL) {
        return;
    }

    demolishTree(pRoot->pLeft);
    demolishTree(pRoot->pRight);
    delete pRoot; pRoot = NULL;
}

// ---------------------------------------------------
// YOUR WORK

NODE* createNode(int data) {
    // TODO: YOUR CODE HERE
    NODE* newNode = new NODE;
    newNode->height = 1;
    newNode->key = data;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    return newNode;
}

int height(NODE* pRoot) {
    // TODO: YOUR CODE HERE
    if (!pRoot)return 0;
    int leftHeight = 1 + height(pRoot->pLeft);
    int rightHeight = 1 + height(pRoot->pRight);
    return leftHeight > rightHeight ? leftHeight : rightHeight;
}

void updateHeight(NODE* pRoot) {
    if (!pRoot)return;
    pRoot->height = height(pRoot);
}

void rotateLeft(NODE*& pRoot) {
    if (!pRoot)return;
    NODE* node = pRoot->pRight;
    pRoot->pRight = node->pLeft;
    node->pLeft = pRoot;
    pRoot = node;
}

void rotateRight(NODE*& pRoot) {
    if (!pRoot)return;
    NODE* node = pRoot->pLeft;
    pRoot->pLeft = node->pRight;
    node->pRight = pRoot;
    pRoot = node;
}

int getBalanceFactor(NODE* pRoot) {
    if (!pRoot) return 0;
    return height(pRoot->pLeft) - height(pRoot->pRight);
}

void balancing(NODE*& pRoot) {
    if (!pRoot)return;
    int differ = getBalanceFactor(pRoot);
    if (differ > 1) {
        if (getBalanceFactor(pRoot->pLeft) > 0)
            rotateRight(pRoot);
        else {
            rotateLeft(pRoot->pLeft);
            rotateRight(pRoot);
        }
    }
    else if (differ < -1) {
        if (getBalanceFactor(pRoot->pRight) < 0)
            rotateLeft(pRoot);
        else {
            rotateRight(pRoot->pRight);
            rotateLeft(pRoot);
        }
    }
}


void Insert(NODE*& pRoot, int x) {
    // TODO: YOUR CODE HERE
    if (!pRoot)
        pRoot = createNode(x);
    else {
        if (pRoot->key > x) {
            Insert(pRoot->pLeft, x);
        }
        else if (pRoot->key < x) {
            Insert(pRoot->pRight, x);
        }
        else return;
    }
    balancing(pRoot);
    updateHeight(pRoot);

}

//
// Trong trường hợp xóa node có đủ 2 con, node thay thế sẽ là NODE CON LỚN NHẤT CỦA CÂY CON BÊN TRÁI.
//

void Remove(NODE*& pRoot, int x) {
    // TODO: YOUR CODE HERE
    if (!pRoot)return;
    else if (pRoot->key > x) {
        Remove(pRoot->pLeft, x);
    }
    else if (pRoot->key < x) {
        Remove(pRoot->pRight, x);
    }
    else {
        if (!pRoot->pLeft) {
            NODE* temp = pRoot->pRight;
            delete pRoot;
            pRoot = temp;
        }
        else if (!pRoot->pRight) {
            NODE* temp = pRoot->pLeft;
            delete pRoot;
            pRoot = temp;
        }
        else {
            NODE* dummy = pRoot->pLeft;
            while (dummy->pRight) dummy = dummy->pRight;
            pRoot->key = dummy->key;
            Remove(pRoot->pLeft, dummy->key);
        }
    }
    if (pRoot) {
        balancing(pRoot);
        updateHeight(pRoot);
    }
}

bool isAVL(NODE* pRoot) {
    // TODO: YOUR CODE HERE
    if (!pRoot)return true;
    if (abs(height(pRoot->pLeft) - height(pRoot->pRight)) > 1)return false;
    return isAVL(pRoot->pLeft) && isAVL(pRoot->pRight);
}

//
// Với các hàm duyệt cây, sinh viên in giá trị các node cách nhau bởi dấu khoảng trắng,
// không in thêm dấu xuống dòng.
//
// VD: 1 2 3 4 5 6

void LRN(NODE* pRoot) {
    // TODO: YOUR CODE HERE
    if (!pRoot)return;
    LRN(pRoot->pLeft);
    LRN(pRoot->pRight);
    cout << pRoot->key << " ";
}

void NLR(NODE* pRoot) {
    // TODO: YOUR CODE HERE
    if (!pRoot)return;
    cout << pRoot->key << " ";
    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
}

void LNR(NODE* pRoot) {
    // TODO: YOUR CODE HERE
    if (!pRoot)return;
    LNR(pRoot->pLeft);
    cout << pRoot->key << " ";
    LNR(pRoot->pRight);
}

void LevelOrder(NODE* pRoot) {
    // TODO: YOUR CODE HERE
    if (!pRoot)return;
    queue<NODE*>Q;
    Q.push(pRoot);
    while (!Q.empty()) {
        NODE* node = Q.front();
        Q.pop();
        cout << node->key << " ";
        if (node->pLeft)Q.push(node->pLeft);
        if (node->pRight)Q.push(node->pRight);
    }
}

// ---------------------------------------------------
// DO NOT MODIFY CODE INSIDE THIS ZONE

// Create the tree from a given array (std::vector)
NODE* createTreeFromArray(const vector<int>& arr) {
    NODE* pRoot = NULL;
    for (int i = 0; i < arr.size(); ++i) {
        Insert(pRoot, arr[i]);
    }
    return pRoot;
}

// ---------------------------------------------------

int main() {
    // All testcases will be load from files and printed into file.
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);



    int n, k; cin >> n >> k;
    vector<int> arr(n); for (auto& i : arr) cin >> i;
    vector<int> del(k); for (auto& i : del) cin >> i;

    NODE* pRoot = createTreeFromArray(arr);

    assert(isAVL(pRoot));

    // LRN order
    LRN(pRoot); cout << "\n";
    LNR(pRoot); cout << "\n";
    NLR(pRoot); cout << "\n";

    // Print the tree height
    cout << height(pRoot) << "\n";

    // Removing nodes 
    for (const auto i : del) {
        Remove(pRoot, i);
    }

    // Print the tree after removal
    LRN(pRoot); cout << "\n";
    LNR(pRoot); cout << "\n";
    NLR(pRoot); cout << "\n";

    // Print the tree height after removal
    cout << height(pRoot) << "\n";


    demolishTree(pRoot);
    assert(pRoot == NULL);

    return 0;
}