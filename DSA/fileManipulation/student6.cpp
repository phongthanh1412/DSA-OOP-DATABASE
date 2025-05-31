#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

struct Student
{
    string studentName, studentID, bloodType;
    int studentAge, math_score, physics_score, chemistry_score, english_score, programming_score;
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
    newStudent->pLeft = NULL;
    newStudent->pRight = NULL;
    newStudent->s = student;
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
    stream >> student.studentAge;
    stream.ignore(1);
    stream >> student.math_score;
    stream.ignore(1);
    stream >> student.physics_score;
    stream.ignore(1);
    stream >> student.chemistry_score;
    stream.ignore(1);
    stream >> student.english_score;
    stream.ignore(1);
    stream >> student.programming_score;
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
        cout << "File is not found.";
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

void NLR(Node *pRoot)
{
    if (!pRoot)
        return;
    double total = pRoot->s.math_score + pRoot->s.physics_score + pRoot->s.chemistry_score + pRoot->s.english_score + pRoot->s.programming_score;
    cout << pRoot->s.studentID << ' ' << pRoot->s.studentName << ' ' << pRoot->s.studentAge << ' ' << pRoot->s.math_score << ' '
         << pRoot->s.physics_score << ' ' << pRoot->s.chemistry_score << ' ' << pRoot->s.english_score << ' ' << pRoot->s.programming_score << ' '
         << pRoot->s.gpa << ' ' << pRoot->s.bloodType << ' ' << total << endl;
    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
}

void removeStudent(Node *&pRoot, double GPA)
{
    if (!pRoot)
        return;
    else if (pRoot->s.gpa > GPA)
        removeStudent(pRoot->pLeft, GPA);
    else if (pRoot->s.gpa < GPA)
        removeStudent(pRoot->pRight, GPA);
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
void removeHelper(Node *&pRoot, double GPA)
{
    if (!pRoot)
        return;
    removeHelper(pRoot->pLeft, GPA);
    removeHelper(pRoot->pRight, GPA);
    if (pRoot->s.gpa < GPA)
        removeStudent(pRoot, pRoot->s.gpa);
}
void removeStudentLowerGPA(Node *&pRoot)
{
    removeHelper(pRoot, 90);
}

double findSumWithGPA(Node *pRoot, double minGPA, double maxGPA)
{
    if (!pRoot)
        return 0;
    double sum = 0;
    if (pRoot->s.gpa >= minGPA && pRoot->s.gpa <= maxGPA)
        sum += pRoot->s.gpa;
    sum += findSumWithGPA(pRoot->pLeft, minGPA, maxGPA);
    sum += findSumWithGPA(pRoot->pRight, minGPA, maxGPA);
    return sum;
}

void classify(Node *pRoot)
{
    if (!pRoot)
        return;
    if (pRoot->s.gpa >= 50 && pRoot->s.gpa < 65)
        cout << pRoot->s.studentID << ' ' << pRoot->s.studentName << " Normal" << endl;
    else if (pRoot->s.gpa >= 65 && pRoot->s.gpa < 80)
        cout << pRoot->s.studentID << ' ' << pRoot->s.studentName << " Good" << endl;
    else if (pRoot->s.gpa >= 80 && pRoot->s.gpa <= 100)
        cout << pRoot->s.studentID << ' ' << pRoot->s.studentName << " Excellent" << endl;

    classify(pRoot->pLeft);
    classify(pRoot->pRight);
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
    classify(studentList);
    // cout << endl;
    // cout << findSumWithGPA(studentList, 80, 90);

    // cout << endl;
    // removeStudentLowerGPA(studentList);
    // NLR(studentList);

    demolishTree(studentList);
    return 0;
}