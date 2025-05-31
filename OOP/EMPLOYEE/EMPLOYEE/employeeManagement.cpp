#include<iostream>
#include<iomanip>
#include<vector>
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

};

class EmployeeManager {
private:
	std::vector<Employee> employees;
public:
	void addEmployee(const Employee& employee);
	void removeEmployee(const std::string& employeeID);
	void displayAllEmployees();
	Employee findEmployeeByID(const std::string& employeeID);
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

void EmployeeManager::addEmployee(const Employee& employee) {
	employees.push_back(employee);
}
void EmployeeManager::removeEmployee(const std::string& employeeID) {
	for (auto it = employees.begin(); it != employees.end();) {
		if (it->getEmployeeID() == employeeID) {
			it = employees.erase(it);
		}
		else it++;
	}
}
void EmployeeManager::displayAllEmployees() {
	for (int i = 0; i < employees.size() && i != employees.size(); i++) {
		employees[i].displayInfo();
		if (i != employees.size() - 1)
			cout << "==============================\n";
	}
}
Employee EmployeeManager::findEmployeeByID(const std::string& employeeID) {
	for (auto& it : employees) {
		if (it.getEmployeeID() == employeeID)
			return it;
	}
	return Employee();
}

#include"main.h"

//int main() {
//	Employee emp1("EmmaStone", "E016", 32, "Acting", 920000);
//	Employee emp2("JenniferLawrence ", "E017 ", 30, "Acting", 930000);
//	EmployeeManager emps;
//	emps.addEmployee(emp1);
//	emps.addEmployee(emp2);
//	emps.displayAllEmployees();
//	return 0;
//}