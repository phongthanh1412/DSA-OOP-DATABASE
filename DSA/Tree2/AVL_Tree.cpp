#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int key;
    Node *pLeft;
    Node *pRight;
    int height;
};

Node *createNode(int data)
{
    Node *newNode = new Node;
    newNode->key = data;
    newNode->height = 1;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    return newNode;
}

void rotateLeft(Node *&pRoot)
{
    if (!pRoot)
        return;
    Node *node = pRoot->pRight;
    pRoot->pRight = node->pLeft;
    node->pLeft = pRoot;
    pRoot = node;
}

void rotateRight(Node *&pRoot)
{
    if (!pRoot)
        return;
    Node *node = pRoot->pLeft;
    pRoot->pLeft = node->pRight;
    node->pRight = pRoot;
    pRoot = node;
}

int getHeight(Node *pRoot)
{
    if (!pRoot)
        return 0;
    int leftHeight = 1 + getHeight(pRoot->pLeft);
    int rightHeight = 1 + getHeight(pRoot->pRight);
    return leftHeight > rightHeight ? leftHeight : rightHeight;
}

int differ(Node *pRoot)
{
    if (!pRoot)
        return 0;
    return getHeight(pRoot->pLeft) - getHeight(pRoot->pRight);
}

void Insert(Node *&pRoot, int x)
{
    if (!pRoot)
        pRoot = createNode(x);
    else
    {
        if (pRoot->key > x)
            Insert(pRoot->pLeft, x);
        else if (pRoot->key < x)
            Insert(pRoot->pRight, x);
        else
        {
            cout << "Value " << x << " did already exist in the AVL tree.\n";
            return;
        }
    }

    int delta = differ(pRoot);
    if (delta > 1)
    {
        if (differ(pRoot->pLeft) > 0)
            rotateRight(pRoot);
        else
        {
            rotateLeft(pRoot->pLeft);
            rotateRight(pRoot);
        }
    }
    else if (delta < -1)
    {
        if (differ(pRoot->pRight) < 0)
            rotateLeft(pRoot);
        else
        {
            rotateRight(pRoot->pRight);
            rotateLeft(pRoot);
        }
    }
}
void NLR(Node *pRoot)
{
    if (!pRoot)
        return;
    else
    {
        NLR(pRoot->pLeft);
        NLR(pRoot->pRight);
        cout << pRoot->key << " ";
    }
}
void Remove(Node *&pRoot, int x)
{
    if (!pRoot)
        return;
    else if (pRoot->key > x)
        Remove(pRoot->pLeft, x);
    else if (pRoot->key < x)
        Remove(pRoot->pRight, x);
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
            while (dummy->pLeft)
                dummy = dummy->pLeft;
            pRoot->key = dummy->key;
            Remove(pRoot->pRight, dummy->key);
        }
    }
    int delta = differ(pRoot);
    if (delta > 1)
    {
        if (differ(pRoot->pLeft) > 0)
            rotateRight(pRoot);
        else
        {
            rotateLeft(pRoot->pLeft);
            rotateRight(pRoot);
        }
    }
    else if (delta < -1)
    {
        if (differ(pRoot->pRight) < 0)
            rotateLeft(pRoot);
        else
        {
            rotateRight(pRoot->pRight);
            rotateLeft(pRoot);
        }
    }
}

bool isAVL(Node *pRoot)
{
    if (!pRoot)
        return true;
    if ((getHeight(pRoot->pLeft) - getHeight(pRoot->pRight)) > 1)
        return false;
    else if ((getHeight(pRoot->pLeft) - getHeight(pRoot->pRight)) < -1)
        return false;
    return isAVL(pRoot->pLeft) && isAVL(pRoot->pRight);
}

void createTree(Node *&pRoot)
{
    int val;
    for (int i = 0; i < 13; i++)
    {
        cin >> val;
        Insert(pRoot, val);
    }
}

void levelOrder(Node *pRoot)
{
    if (!pRoot)
        return;
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

void release(Node *&pRoot)
{
    if (!pRoot)
        return;
    else
    {
        release(pRoot->pLeft);
        release(pRoot->pRight);
        delete pRoot;
        pRoot = NULL;
    }
}

int main()
{
    Node *root = NULL;
    createTree(root);
    levelOrder(root);
    // Remove(root, 50);
    // // levelOrder(root);
    // NLR(root);
    // cout << isAVL(root);
    release(root);
    return 0;
}