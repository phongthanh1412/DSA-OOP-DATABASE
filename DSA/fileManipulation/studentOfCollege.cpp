#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

struct Student
{
    string stuID;
    string name;
    int date = 0;
    int month = 0;
    int year = 0;
    int mathScore = 0;
    int literatureScore = 0;
    int englishScore = 0;
};

struct Node
{
    Student s;
    Node *next;
};

Node *createNode(Student student)
{
    Node *newStudent = new Node;
    newStudent->s = student;
    newStudent->next = NULL;
    return newStudent;
}

void addStudent(Node *&studentList, Student student)
{
    if (!studentList)
    {
        studentList = createNode(student);
    }
    else
    {
        Node *temp = studentList;
        Node *newStudent = createNode(student);
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
}

Node *readStudent(string info)
{
    stringstream stream(info);
    string content;
    Student student;
    getline(stream, content, '-');
    student.stuID = content;
    getline(stream, content, '-');
    student.name = content;
    stream >> student.date;
    stream.ignore(1);
    stream >> student.month;
    stream.ignore(1);
    stream >> student.year;
    stream.ignore(1);
    stream >> student.mathScore;
    stream.ignore(1);
    stream >> student.literatureScore;
    stream.ignore(1);
    stream >> student.englishScore;

    return createNode(student);
}

Node *readStudentList(string fileName)
{
    ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        cout << "File is not found." << endl;
        return NULL;
    }
    string line;
    Node *studentList = NULL;
    while (getline(inFile, line))
    {
        Node *newStudent = readStudent(line);
        addStudent(studentList, newStudent->s);
    }
    inFile.close();
    return studentList;
}

void printStudentList(Node *studentList)
{
    Node *temp = studentList;
    while (temp)
    {
        cout << temp->s.stuID << "-" << temp->s.name
             << "-" << temp->s.date << "/" << temp->s.month << "/" << temp->s.year
             << "-" << temp->s.mathScore
             << "-" << temp->s.literatureScore
             << "-" << temp->s.englishScore << endl;
        temp = temp->next;
    }
}

void release(Node *&studentList)
{
    Node *temp = studentList;
    while (temp)
    {
        Node *cur = temp;
        temp = temp->next;
        delete cur;
    }
    studentList = NULL;
}

int main()
{
    Node *studentList;
    studentList = readStudentList("studentOfCollege.txt");
    printStudentList(studentList);
    release(studentList);
    return 0;
}