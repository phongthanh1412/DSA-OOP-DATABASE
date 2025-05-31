/**
 * Homework 1: Stack
 * @date 2024-10-23
 *
 * Vui lòng làm theo các hướng dẫn trong bài. Bài làm sai quy định sẽ nhận điểm 0 (zero).
 */
#include <iostream>
#include <cassert>
#include <vector> // dùng để test.

using namespace std;

// Vui lòng KHÔNG sửa các định nghĩa struct này.

// Định nghĩa một Node trong danh sách liên kết đôi (DLL).
struct Node
{
    int key;
    Node* pNext;
    Node* pPrev;
};

// Định nghĩa của Stack.
struct Stack
{
    Node* pTop;
    int size;
};

// Các bạn code từ đây
// Tạo node: tùy ý.
Node* createNode(int key)
{
    Node* newNode = new Node;
    newNode->key = key;
    newNode->pNext = NULL;
    newNode->pPrev = NULL;
    return newNode;
}
// Hàm 1: khởi tạo Stack từ một key cho trước
Stack* init(int key)
{
    Node* newNode = createNode(key);
    Stack* stk = new Stack;
    stk->pTop = newNode;
    stk->size = 0;
    return stk;
}

// Hàm 2: push một key vào Stack
void push(Stack*& stk, int key)
{
    Node* newNode = createNode(key);
    if (!stk->pTop)
    {
        stk->pTop = newNode;
        stk->size++;
    }
    else
    {
        newNode->pNext = stk->pTop;
        stk->pTop = newNode;
        stk->size++;
    }
}

// Hàm 3: pop node top ra khỏi Stack, trả về giá trị node này.
// Nếu stack rỗng, thông báo ra màn hình "EMPTY STACK" và trả về giá trị -1.
int pop(Stack*& stk)
{
    if (!stk->pTop)
    {
        cout << "EMPTY STACK!";
        return -1;
    }
    else
    {
        Node* temp = stk->pTop;
        stk->pTop = stk->pTop->pNext;
        return temp->key;
    }
}

// Hàm 4: Đếm số lượng node trong Stack (kích thước Stack)
int size(Stack* stk)
{
    Node* temp = stk->pTop;
    int count = 0;
    while (temp)
    {
        count++;
        temp = temp->pNext;
    }
    return count;
}

// Hàm 5: Kiểm tra Stack có rỗng hay không
bool isEmpty(Stack* stk)
{
    return stk->pTop == NULL;
}

// Hàm 6: Hủy stack
void destroy(Stack*& stk)
{
    Node* temp = stk->pTop;
    while (temp)
    {
        Node* cur = temp;
        temp = temp->pNext;
        delete cur;
    }
    stk->pTop = NULL;
    stk->size = 0;
    delete stk;
    stk = NULL;
}

// Các bạn có thể modify hàm main để test, sau đó nhớ restore lại hàm main ban đầu.

int main()
{
    vector<int> test = { 1, 3, 2, 9, 6, 5 };

    Stack* stk = init(test[0]);

    for (int i : test)
    {
        push(stk, i);
    }

    // Cài sai các hàm push(), size(), isEmpty()
    // sẽ gây lỗi.
    assert(size(stk) == 7);
    assert(isEmpty(stk) == false);

    // Expected answer: 5
    cout << pop(stk) << "\n";

    // Expected answer: 6
    cout << pop(stk) << "\n";

    push(stk, 121);

    // Expected answer: 6
    cout << size(stk) << "\n";

    int currentTop = pop(stk);
    assert(currentTop == 121);

    destroy(stk);

    // Xóa stack không thành công sẽ báo lỗi ngay đây.
    assert(stk == NULL);

    return 0;
}