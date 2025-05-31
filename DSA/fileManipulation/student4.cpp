#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

struct Student
{
    string name;
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
    newStudent->height = 1;
    newStudent->s = student;
    newStudent->pLeft = NULL;
    newStudent->pRight = NULL;
    return newStudent;
}

void InsertBST(Node *&pRoot, Node *newStudent)
{
    if (!pRoot)
        pRoot = newStudent;
    else if (pRoot->s.name > newStudent->s.name)
        InsertBST(pRoot->pLeft, newStudent);
    else if (pRoot->s.name < newStudent->s.name)
        InsertBST(pRoot->pRight, newStudent);
    else
        return;
}

void NLR(Node *pRoot)
{
    if (!pRoot)
        return;
    cout << pRoot->s.name << ' ' << pRoot->s.age << ' ' << pRoot->s.math << ' ' << pRoot->s.physics << ' ' << pRoot->s.chemistry << ' '
         << pRoot->s.foreign_language << ' ' << pRoot->s.programming << ' ' << pRoot->s.gpa << endl;
    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
}

Node *readStudent(string info)
{
    stringstream stream(info);
    string content;
    Student student;
    getline(stream, content, ';');
    student.name = content;
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
        InsertBST(studentList, newStudent);
    }

    inFile.close();
    return studentList;
}

bool searchStudent(Node *pRoot, string name)
{
    if (pRoot == NULL)
    {
        return false;
    }
    else
    {
        if (pRoot->s.name > name)
            return searchStudent(pRoot->pLeft, name);
        else if (pRoot->s.name < name)
            return searchStudent(pRoot->pRight, name);
        else if (pRoot->s.name == name)
            return true;
    }
}

void findMinMaxGPA(Node *pRoot, Node *&minNode, Node *&maxNode)
{
    if (!pRoot)
        return;
    if (!minNode || pRoot->s.gpa < minNode->s.gpa)
        minNode = pRoot;
    if (!maxNode || pRoot->s.gpa > maxNode->s.gpa)
        maxNode = pRoot;
    findMinMaxGPA(pRoot->pLeft, minNode, maxNode);
    findMinMaxGPA(pRoot->pRight, minNode, maxNode);
}

void printStudentWithGPA(Node *pRoot, double minGPA, double maxGPA)
{
    if (!pRoot)
        return;
    if (pRoot->s.gpa >= minGPA && pRoot->s.gpa <= maxGPA)
        cout << pRoot->s.name << ' ' << pRoot->s.gpa << endl;
    printStudentWithGPA(pRoot->pLeft, minGPA, maxGPA);
    printStudentWithGPA(pRoot->pRight, minGPA, maxGPA);
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

void convertToAVL(Node *&pRoot)
{
    if (!pRoot)
        return;
    balancing(pRoot);
    updateHeight(pRoot);
    convertToAVL(pRoot->pLeft);
    convertToAVL(pRoot->pRight);
}

void removeAVL(Node *&pRoot, string name)
{
    if (!pRoot)
        return;
    else if (pRoot->s.name > name)
        removeAVL(pRoot->pLeft, name);
    else if (pRoot->s.name < name)
        removeAVL(pRoot->pRight, name);
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
            pRoot->s.name = dummy->s.name;
            removeAVL(pRoot->pLeft, dummy->s.name);
        }
    }
    balancing(pRoot);
    updateHeight(pRoot);
}

Node *helperFindStudent(Node *pRoot, double targetGPA, Node *closestNode)
{
    if (!pRoot)
        return closestNode;

    if (!closestNode || abs(pRoot->s.gpa - targetGPA) < abs(closestNode->s.gpa - targetGPA))
        closestNode = pRoot;
    if (targetGPA < pRoot->s.gpa)
        return helperFindStudent(pRoot->pLeft, targetGPA, closestNode);
    else if (targetGPA > pRoot->s.gpa)
        return helperFindStudent(pRoot->pRight, targetGPA, closestNode);
    return closestNode;
}

void findStudent(Node *pRoot, double gpa)
{
    Node *closestStudent = helperFindStudent(pRoot, gpa, NULL);
    if (closestStudent)
    {
        cout << closestStudent->s.name << ' ' << closestStudent->s.gpa << endl;
    }
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
    Node *studentList = readStudentList("student4.txt");
    NLR(studentList);
    cout << searchStudent(studentList, "Davis") << endl;
    // ofstream ofile("output3.txt");
    // writeTotal(studentList, ofile);
    // Node *minNode = NULL, *maxNode = NULL;
    // findMinMaxGPA(studentList, minNode, maxNode);
    // cout << minNode->s.gpa << ' ' << maxNode->s.gpa << endl;
    // printStudentWithGPA(studentList, 80, 90);
    convertToAVL(studentList);
    NLR(studentList);
    cout << endl;
    removeAVL(studentList, "Sarah Miller");
    NLR(studentList);
    cout << endl;

    findStudent(studentList, 82);
    demolishTree(studentList);
    return 0;
}