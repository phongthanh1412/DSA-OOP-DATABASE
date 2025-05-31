#include <iostream>
#include <string>
#include <cmath> 
#include <iomanip> 

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

Student::Student() :fullName(""), studentID(""), age(0), address(""), gpa(0.0) {}
Student::Student(std::string name, std::string id, int age, std::string address, float gpa) 
    :fullName(name), studentID(id), age(age), address(address), gpa(gpa) {}


void Student::displayInfo() {
    cout << "Name: " << fullName << endl;
    cout << "Student ID: " << studentID << endl;
    cout << "Age: " << age << endl;
    cout << "Address: " << address << endl;
    cout << "GPA: " << fixed << setprecision(3) << gpa << endl;
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

#include "main.h"

//int main() {
//    Student st1("SophiaLee", "S006", 25, "987MapleSt", 3.4);
//    st1.displayInfo();
//
//    Student st2;
//    st2.setFullName("Emma Brown rsk");
//    st2.setStudentID("S004rsk");
//    st2.setAge(24);
//    st2.setAddress("321 Pine St rsk");
//    st2.setGPA(3.9f);
//
//    cout << st2.getFullName() << "; "
//        << st2.getStudentID() << "; "
//        << st2.getAge() << "; "
//        << st2.getAddress() << "; "
//        << fixed << setprecision(3) << st2.getGPA() << endl;
//
//    return 0;
//}