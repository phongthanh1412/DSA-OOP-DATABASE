#include <iostream>
#include <string>
#include <cmath> 
#include <iomanip> 
#include <vector> 

using namespace std;

class Student {
private:
    std::string fullName;
    std::string studentID;
    int age;
    std::string address;
    float gpa;

public:
    Student();
    Student(std::string name, std::string id, int age, std::string address, float gpa);
    void displayInfo();
    std::string getFullName();
    void setFullName(std::string name);
    std::string getStudentID();
    void setStudentID(std::string id);
    int getAge();
    void setAge(int age);
    std::string getAddress();
    void setAddress(std::string address);
    float getGPA();
    void setGPA(float gpa);
};

class StudentManager {
private:
    std::vector<Student> students;

public:
    void addStudent(const Student& student);
    void removeStudent(const std::string& studentID);
    void displayAllStudents();
    Student findStudentByID(const std::string& studentID);
};


Student::Student() :fullName(""), studentID(""), age(0), address(""), gpa(0.0) {}
Student::Student(std::string name, std::string id, int age, std::string address, float gpa)
    :fullName(name), studentID(id), age(age), address(address), gpa(gpa) {}


void Student::displayInfo() {
    cout << "Name: " << fullName << endl;
    cout << "Student ID: " << studentID << endl;
    cout << "Age: " << age << endl;
    cout << "Address: " << address << endl;
    cout << "GPA: " << fixed << setprecision(1) << gpa << endl;
}

std::string Student::getFullName() {
    return fullName;
}

void Student::setFullName(std::string name) {
    this->fullName = name;
}

std::string Student::getStudentID() {
    return studentID;
}

void Student::setStudentID(std::string id) {
    this->studentID = id;
}

int Student::getAge() {
    return age;
}

void Student::setAge(int age) {
    this->age = age;
}

std::string Student::getAddress() {
    return address;
}

void Student::setAddress(std::string address) {
    this->address = address;
}

float Student::getGPA() {
    return gpa;
}

void Student::setGPA(float gpa) {
    this->gpa = gpa;
}

void StudentManager::addStudent(const Student& student) {
    students.push_back(student);
}

void StudentManager::removeStudent(const std::string& studentID) {
    for (auto it = students.begin(); it != students.end(); ) {
        if (it->getStudentID() == studentID) {
            it = students.erase(it);
        }
        else {
            ++it;
        }
    }
}

void StudentManager::displayAllStudents() {
    for (int i = 0; i < students.size(); ++i) {
        students[i].displayInfo();
        if (i != students.size() - 1) {
            cout << "--------------------\n";
        }
    }
}

Student StudentManager::findStudentByID(const std::string& studentID) {
    for (auto& st : students) {
        if (st.getStudentID() == studentID)
            return st;
    }
    return Student();
}

#include "main.h"

//int main() {
//    Student st1("John Doe", "S001", 20, "123 Main St", 3.5);
//    Student st2("Alice Smith", "S002", 22, "456 Oak Ave", 3.8);
//    Student st3("Bob Johnson", "S003", 21, "789 Elm St", 3.2);
//    
//    StudentManager students;
//    students.addStudent(st1);
//    students.addStudent(st2);
//    students.addStudent(st3);
//    students.displayAllStudents();
//
//    students.removeStudent("S002");
//    cout << endl;
//    students.displayAllStudents();
//
//    return 0;
//}