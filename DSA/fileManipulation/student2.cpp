#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

struct Student
{
    string studentID;
    string studentName;
    int studentHeight, studentWeight;
    string bloodType;
};

struct Node
{
    Student s;
    Node *pLeft;
    Node *pRight;
    int height;
};

Node *createNode(Student student)
{
    Node *newStudent = new Node;
    newStudent->s = student;
    newStudent->pLeft = NULL;
    newStudent->pRight = NULL;
    newStudent->height = 1;
    return newStudent;
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

void updateHeight(Node *pRoot)
{
    if (!pRoot)
        return;
    pRoot->height = getHeight(pRoot);
}

int getBalanceFactor(Node *pRoot)
{
    if (!pRoot)
        return 0;
    return getHeight(pRoot->pLeft) - getHeight(pRoot->pRight);
}

void balancing(Node *&pRoot)
{
    if (!pRoot)
        return;
    int differ = getBalanceFactor(pRoot);
    if (differ > 1)
    {
        if (getBalanceFactor(pRoot->pLeft) > 0)
            rotateRight(pRoot);
        else
        {
            rotateLeft(pRoot->pLeft);
            rotateRight(pRoot);
        }
    }
    else if (differ < -1)
    {
        if (getBalanceFactor(pRoot->pRight) < 0)
            rotateLeft(pRoot);
        else
        {
            rotateRight(pRoot->pRight);
            rotateLeft(pRoot);
        }
    }
}

void Insert(Node *&pRoot, Node *newStudent)
{
    if (!pRoot)
        pRoot = newStudent;
    else if (pRoot->s.studentID > newStudent->s.studentID)
        Insert(pRoot->pLeft, newStudent);
    else if (pRoot->s.studentID < newStudent->s.studentID)
        Insert(pRoot->pRight, newStudent);
    else
        return;
    balancing(pRoot);
    updateHeight(pRoot);
}

void NLR(Node *pRoot)
{
    if (!pRoot)
        return;
    cout << pRoot->s.studentID << ' ' << pRoot->s.studentName << ' ' << pRoot->s.studentHeight << ' ' << pRoot->s.studentWeight
         << ' ' << pRoot->s.bloodType << endl;
    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
}

Node *readStudent(string info)
{
    stringstream stream(info);
    string content;
    Student student;
    getline(stream, content, '|');
    student.studentID = content;
    getline(stream, content, '|');
    student.studentName = content;
    stream >> student.studentHeight;
    stream.ignore(1);
    stream >> student.studentWeight;
    stream.ignore(1);
    getline(stream, content, ' ');
    student.bloodType = content;

    return createNode(student);
}

Node *readStudentList(string fileName)
{
    ifstream inFile(fileName);
    if (inFile.eof())
    {
        cout << "File is not found.";
        return NULL;
    }

    string line;
    Node *studentList = NULL;
    getline(inFile, line);
    while (getline(inFile, line))
    {
        Node *newStudent = readStudent(line);
        Insert(studentList, newStudent);
    }
    inFile.close();
    return studentList;
}

void demolishTree(Node *&pRoot)
{
    if (pRoot == NULL)
    {
        return;
    }

    demolishTree(pRoot->pLeft);
    demolishTree(pRoot->pRight);
    delete pRoot;
    pRoot = NULL;
}
int main()
{
    Node *studentList;
    studentList = readStudentList("student2.txt");
    NLR(studentList);
    demolishTree(studentList);
    return 0;
}