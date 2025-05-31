#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int key;
    Node *pLeft;
    Node *pRight;
};

Node *createNode(int data)
{
    Node *newNode = new Node;
    newNode->key = data;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    return newNode;
}

void Insert(Node *&pRoot, int x)
{
    if (!pRoot)
    {
        pRoot = createNode(x);
    }
    if (pRoot->key > x)
    {
        Insert(pRoot->pLeft, x);
    }
    else if (pRoot->key < x)
    {
        Insert(pRoot->pRight, x);
    }
}
void NLR(Node *pRoot)
{
    if (!pRoot)
        return;
    else
    {
        cout << pRoot->key << " ";
        NLR(pRoot->pLeft);
        NLR(pRoot->pRight);
    }
}

void LevelOrder(Node *pRoot)
{
    queue<Node *> Q;
    Q.push(pRoot);
    while (!Q.empty())
    {
        Node *node = Q.front();
        Q.pop();
        cout << node->key << " ";
        if (node->pLeft)
            Q.push(node->pLeft);
        if (node->pRight)
            Q.push(node->pRight);
    }
    cout << endl;
}

int Height(Node *pRoot)
{
    if (!pRoot)
        return 0;
    int leftHeight = 1 + Height(pRoot->pLeft);
    int rightHeight = 1 + Height(pRoot->pRight);
    return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}

int countNode(Node *pRoot)
{
    if (!pRoot)
        return 0;
    else
    {
        return 1 + countNode(pRoot->pLeft) + countNode(pRoot->pRight);
    }
}

int sumNode(Node *pRoot)
{
    if (!pRoot)
        return 0;
    else
    {
        return pRoot->key + sumNode(pRoot->pLeft) + sumNode(pRoot->pRight);
    }
}

Node *Search(Node *pRoot, int x)
{
    if (!pRoot)
        return NULL;
    else
    {
        if (pRoot->key > x)
        {
            return Search(pRoot->pLeft, x);
        }
        else if (pRoot->key < x)
        {
            return Search(pRoot->pRight, x);
        }
        else
            return pRoot;
    }
}

int countLeaf(Node *pRoot)
{
    if (!pRoot)
        return 0;
    if (!pRoot->pLeft && !pRoot->pRight)
        return 1;
    return countLeaf(pRoot->pLeft) + countLeaf(pRoot->pRight);
}

int countLess(Node *pRoot, int x)
{
    if (!pRoot)
        return 0;

    if (pRoot->key >= x)
        return countLess(pRoot->pLeft, x);
    else if (pRoot->key < x)
        return 1 + countLess(pRoot->pRight, x) + countLess(pRoot->pLeft, x);
}

bool isBSTHelper(Node *pRoot, long int minkey, long int maxkey)
{
    if (!pRoot)
        return true;
    if (pRoot->key > minkey && pRoot->key < maxkey)
    {
        bool left = isBSTHelper(pRoot->pLeft, minkey, pRoot->key);
        bool right = isBSTHelper(pRoot->pRight, pRoot->key, maxkey);
        return left && right;
    }
    return false;
}
bool isBST(Node *pRoot)
{
    return isBSTHelper(pRoot, -1e9, 1e9);
}

bool isFullBSTHelper(Node *pRoot)
{
    if (!pRoot)
        return true;
    if (!pRoot->pLeft && !pRoot->pRight)
        return true;
    if (pRoot->pLeft && pRoot->pRight)
    {
        bool left = isFullBSTHelper(pRoot->pLeft);
        bool right = isFullBSTHelper(pRoot->pRight);
        return left && right;
    }
    return false;
}

bool isFullBST(Node* root) {
    return isBST(root) && isFullBSTHelper(root);
}

Node *createBST(int arr[], int n)
{
    Node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        Insert(root, arr[i]);
    }
    return root;
}

int nodeHeight(Node *pRoot, int x)
{
    if (!pRoot)
        return -1;
    if (pRoot->key > x)
    {
        return 1 + nodeHeight(pRoot->pLeft, x);
    }
    else if (pRoot->key < x)
    {
        return 1 + nodeHeight(pRoot->pRight, x);
    }
    else
        return 1;
}

void findDummy(Node *&toDelete, Node *&dummy)
{
    while (dummy->pLeft)
    {
        dummy = dummy->pLeft;
    }
    toDelete->key = dummy->key;
}

void Remove(Node *&pRoot, int x)
{
    if (!pRoot)
        return;

    if (pRoot->key > x)
    {
        Remove(pRoot->pLeft, x);
    }
    else if (pRoot->key < x)
    {
        Remove(pRoot->pRight, x);
    }
    else
    {
        if (!pRoot->pLeft)
        {
            Node *temp = pRoot->pRight;
            delete pRoot;
            pRoot = temp;
        }
        else if (!pRoot->pRight)
        {
            Node *temp = pRoot->pLeft;
            delete pRoot;
            pRoot = temp;
        }
        else
        {
            Node *dummy = pRoot->pRight;
            findDummy(pRoot, dummy);
            Remove(pRoot->pRight, dummy->key);
        }
    }
}

void release(Node *&pRoot)
{
    if (pRoot)
    {
        release(pRoot->pLeft);
        release(pRoot->pRight);
        delete (pRoot);
        pRoot = NULL;
    }
}

int main()
{
    Node *root = NULL;
    int arr[5] = {56, 32, 87, 12, 65};
    // Insert(root, 45);
    // Insert(root, 67);
    // Insert(root, 34);
    // Insert(root, 88);
    // Insert(root, 53);
    // NLR(root);
    root = createBST(arr, 5);
    LevelOrder(root);
    // cout << Height(root);
    // cout << endl;
    // cout << countLess(root);
    // cout << endl;
    // cout << sumNode(root);
    // cout << endl;
    // cout<<countLeaf(root);
    // cout << endl;
    // cout << countLess(root, 65);
    // if (isFullBSTHelper(root))
    //     cout << 1;
    // else
    //     cout << 0;
    // cout << nodeHeight(root, 56);
    Remove(root, 32);
    LevelOrder(root);
    release(root);
    return 0;
}