#include<iostream>
#include<iomanip>
using namespace std;

class Employee {
private:
	std::string fullName;
	std::string employeeID;
	int age;
	std::string department;
	float salary;
public:
	Employee();
	Employee(std::string name, std::string id, int age, std::string department, float salary);
	void displayInfo();
	std::string getFullName();
	void setFullName(std::string name);
	std::string getEmployeeID();
	void setEmployeeID(std::string id);
	int getAge();
	void setAge(int age);
	std::string getDepartment();
	void setDepartment(std::string department);
	float getSalary();
	void setSalary(float salary);

	void print();
};

Employee::Employee() : fullName(""), employeeID(""), age(0), department(""), salary(0.0) {}
Employee::Employee(std::string name, std::string id, int age, std::string department, float salary) 
	: fullName(name), employeeID(id), age(age), department(department), salary(salary) {}
void Employee::displayInfo() {
	cout << "Name: " << fullName << endl;
	cout << "Employee ID: " << employeeID << endl;
	cout << "Age: " << age << endl;
	cout << "Department: " << department << endl;
	cout << "Salary: " << fixed << setprecision(2) << salary << endl;
}
std::string Employee::getFullName() {
	return fullName;
}
void Employee::setFullName(std::string name) {
	this->fullName = name;
}
std::string Employee::getEmployeeID() {
	return employeeID;
}
void Employee::setEmployeeID(std::string id) {
	this->employeeID = id;
}
int Employee::getAge() {
	return age;
}
void Employee::setAge(int age) {
	this->age = age;
}
std::string Employee::getDepartment() {
	return department;
}
void Employee::setDepartment(std::string department) {
	this->department = department;
}
float Employee::getSalary() {
	return salary;
}
void Employee::setSalary(float salary) {
	this->salary = salary;
}

#include"main.h"

//int main() {
//	Employee emp1("EmmaStone", "E016", 32, "Acting", 920000);
//	Employee emp2("JenniferLawrence ", "E017 ", 30, "Acting", 930000);
//	emp1.displayInfo();
//	emp2.displayInfo();
//	return 0;
//}