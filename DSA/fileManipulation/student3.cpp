#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

struct Student
{
    string id;
    float math, literature, physics, chemistry, biology, history, geography,
        civic_education, natural_science, social_science, foreign_language;
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
    else if (pRoot->s.id > newStudent->s.id)
        Insert(pRoot->pLeft, newStudent);
    else if (pRoot->s.id < newStudent->s.id)
        Insert(pRoot->pRight, newStudent);
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
    vector<float *> subjectScore{
        &student.math,
        &student.literature,
        &student.physics,
        &student.chemistry,
        &student.biology,
        &student.history,
        &student.geography,
        &student.civic_education,
        &student.natural_science,
        &student.social_science,
        &student.foreign_language,
    };
    getline(stream, content, ',');
    student.id = content;
    getline(stream, content, ',');
    for (int i = 0; i < subjectScore.size(); i++)
    {
        getline(stream, content, ',');
        if (!content.empty())
            *subjectScore[i] = stof(content);
        else
            *subjectScore[i] = 0;
    }
    student.natural_science = student.physics + student.chemistry + student.biology;
    student.social_science = student.history + student.geography + student.civic_education;

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

void NLR(Node *pRoot)
{
    if (!pRoot)
        return;
    cout << pRoot->s.math << ' ' << pRoot->s.literature << ' ' << pRoot->s.physics << ' ' << pRoot->s.chemistry
         << ' ' << pRoot->s.biology << ' ' << pRoot->s.history << ' ' << pRoot->s.geography << ' ' << pRoot->s.civic_education << ' '
         << pRoot->s.natural_science << ' ' << pRoot->s.social_science << ' ' << pRoot->s.foreign_language << endl;

    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
}
void writeTotal(Node *studentList, ofstream &outFile)
{
    if (!studentList)
        return;

    outFile << studentList->s.id << ','
          << studentList->s.math << ','
          << studentList->s.literature << ','
          << studentList->s.physics << ','
          << studentList->s.chemistry << ','
          << studentList->s.biology << ','
          << studentList->s.history << ','
          << studentList->s.geography << ','
          << studentList->s.civic_education << ','
          << studentList->s.natural_science << ','
          << studentList->s.social_science << ','
          << studentList->s.foreign_language << '\n';

    writeTotal(studentList->pLeft, outFile);
    writeTotal(studentList->pRight, outFile);
}

int main()
{
    Node *studentList = readStudentList("data.txt");
    NLR(studentList);
    ofstream outFile("output3.txt");
    writeTotal(studentList, outFile);
    demolishTree(studentList);
    return 0;
}