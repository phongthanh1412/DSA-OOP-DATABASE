#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

struct Student
{
    string studentName, studentID, bloodType;
    int age, math, physics, chemistry, foreign_language, programming;
    double gpa;
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

void Insert(Node *&pRoot, Student student)
{
    if (!pRoot)
        pRoot = createNode(student);
    else if (pRoot->s.gpa > student.gpa)
        Insert(pRoot->pLeft, student);
    else if (pRoot->s.gpa < student.gpa)
        Insert(pRoot->pRight, student);
    else
        return;
    balancing(pRoot);
    updateHeight(pRoot);
}

Node *readStudent(string info)
{
    stringstream stream(info);
    string content;
    Student student;
    getline(stream, content, ';');
    student.studentID = content;
    getline(stream, content, ';');
    student.studentName = content;
    stream >> student.age;
    stream.ignore(1);
    stream >> student.math;
    stream.ignore(1);
    stream >> student.physics;
    stream.ignore(1);
    stream >> student.chemistry;
    stream.ignore(1);
    stream >> student.foreign_language;
    stream.ignore(1);
    stream >> student.programming;
    stream.ignore(1);
    stream >> student.gpa;
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
        cout << "file is not found.";
        return NULL;
    }
    string line;
    Node *studentList = NULL;
    getline(inFile, line);
    while (getline(inFile, line))
    {
        Node *newStudent = readStudent(line);
        Insert(studentList, newStudent->s);
    }
    inFile.close();
    return studentList;
}

void findMaxMinGPAHelper(Node *pRoot, Node *&minNode, Node *&maxNode)
{
    if (!pRoot)
        return;
    if (!minNode || pRoot->s.gpa < minNode->s.gpa)
        minNode = pRoot;
    if (!maxNode || pRoot->s.gpa > maxNode->s.gpa)
        maxNode = pRoot;
    findMaxMinGPAHelper(pRoot->pLeft, minNode, maxNode);
    findMaxMinGPAHelper(pRoot->pRight, minNode, maxNode);
}

void findMaxMinGPA(Node *pRoot)
{
    Node *minNode = NULL, *maxNode = NULL;
    findMaxMinGPAHelper(pRoot, minNode, maxNode);
    cout << minNode->s.gpa << ' ' << maxNode->s.gpa << endl;
}

void printStudentWithinGPA(Node *pRoot, double minGPA, double maxGPA)
{
    if (!pRoot)
        return;
    if (pRoot->s.gpa >= minGPA && pRoot->s.gpa <= maxGPA)
        cout << pRoot->s.studentName << ' ' << pRoot->s.gpa << endl;
    printStudentWithinGPA(pRoot->pLeft, minGPA, maxGPA);
    printStudentWithinGPA(pRoot->pRight, minGPA, maxGPA);
}

void removeStudent(Node *&pRoot, double gpa)
{
    if (!pRoot)
        return;
    else if (pRoot->s.gpa > gpa)
        removeStudent(pRoot->pLeft, gpa);
    else if (pRoot->s.gpa < gpa)
        removeStudent(pRoot->pRight, gpa);
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
            Node *dummy = pRoot->pLeft;
            while (dummy->pRight)
                dummy = dummy->pRight;
            pRoot->s.gpa = dummy->s.gpa;
            removeStudent(pRoot->pLeft, dummy->s.gpa);
        }
    }
    balancing(pRoot);
    updateHeight(pRoot);
}

void removeStudentLowerGPAHelper(Node *&pRoot, double gpa)
{
    if (!pRoot)
        return;
    removeStudentLowerGPAHelper(pRoot->pLeft, gpa);
    removeStudentLowerGPAHelper(pRoot->pRight, gpa);
    if (pRoot->s.gpa >= gpa) removeStudent(pRoot, pRoot->s.gpa);
}

void removeStudentLowerGPA(Node *&pRoot)
{
    removeStudentLowerGPAHelper(pRoot, 90);
}

void NLR(Node *pRoot)
{
    if (!pRoot)
        return;
    cout << pRoot->s.studentID << ' ' << pRoot->s.studentName << ' ' << pRoot->s.age << ' '
         << pRoot->s.math << ' ' << pRoot->s.physics << ' ' << pRoot->s.chemistry << ' '
         << pRoot->s.foreign_language << ' ' << pRoot->s.programming << ' ' << pRoot->s.gpa
         << ' ' << pRoot->s.bloodType << endl;

    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
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
    Node *studentList = NULL;
    studentList = readStudentList("student4.txt"); 
    NLR(studentList);
    
    findMaxMinGPA(studentList);

    printStudentWithinGPA(studentList, 80, 90);
    
    removeStudentLowerGPA(studentList);
    NLR(studentList);
    
    demolishTree(studentList);
    return 0;
}