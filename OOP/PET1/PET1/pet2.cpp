#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class Pet {
protected:
	string name;
	int age;
	float price;
public:
	Pet();
	Pet(string name, int age, float price);
	virtual ~Pet();
	virtual void makeSound() const = 0;
	virtual void displayInfo() const = 0;
};

Pet::Pet() : name(""), age(0), price(0.0) {}
Pet::Pet(string name, int age, float price)
	: name(name), age(age), price(price) {}

Pet::~Pet() {}

class Dog : public Pet {
private:
	string breed;
public:

	Dog();
	Dog(string name, int age, float price, string breed);
	void makeSound() const override;
	void displayInfo() const override;
};

Dog::Dog() : Pet(), breed("") {}
Dog::Dog(string name, int age, float price, string breed)
	: Pet(name, age, price), breed(breed) {}

void Dog::makeSound() const {
	cout << "Woof!\n";
}
void Dog::displayInfo() const {
	std::cout << std::left << std::setw(10) << "Dog" << " | "
		<< std::setw(16) << name << " | "
		<< std::setw(6) << age << " | "
		<< fixed << setprecision(1)
		<< std::setw(12) << price << " | "
		<< std::setw(16) << breed << std::endl;
}

class Cat : public Pet {
private:
	string color;
public:
	Cat();
	Cat(string name, int age, float price, string color);
	void makeSound() const override;
	void displayInfo() const override;
};

Cat::Cat() : Pet(), color("") {}
Cat::Cat(string name, int age, float price, string color)
	: Pet(name, age, price), color(color) {}

void Cat::makeSound() const {
	cout << "Meow!\n";
}
void Cat::displayInfo() const {
	std::cout << std::left << std::setw(10) << "Cat" << " | "
		<< std::setw(16) << name << " | "
		<< std::setw(6) << age << " | "
		<< fixed << setprecision(1)
		<< std::setw(12) << price << " | "
		<< std::setw(16) << color << std::endl;
}
class Bird : public Pet {
private:
	float wingSpan;
public:
	Bird();
	Bird(string name, int age, float price, float wingSpan);
	void makeSound() const override;
	void displayInfo() const override;
};

Bird::Bird() : Pet(), wingSpan(0.0) {}
Bird::Bird(string name, int age, float price, float wingSpan)
	: Pet(name, age, price), wingSpan(wingSpan) {}

void Bird::makeSound() const {
	cout << "Chirp!\n";
}
void Bird::displayInfo() const {
	std::cout << std::left << std::setw(10) << "Bird" << " | "
		<< std::setw(16) << name << " | "
		<< std::setw(6) << age << " | "
		<< fixed << setprecision(1)
		<< std::setw(12) << price << " | "
		<< std::setw(16) << wingSpan << std::endl;
}
#include"main.h"

//int main() {
//	int testID;
//	std::cin >> testID;
//	std::cout << "Test " << testID << ":" << std::endl;
//
//	std::cout << std::left << std::setw(10) << "Type" << " | "
//		<< std::setw(16) << "Name" << " | "
//		<< std::setw(6) << "Age" << " | "
//		<< std::setw(12) << "Price" << " | "
//		<< std::setw(16) << "Special" << std::endl;
//	std::cout << std::string(70, '-') << std::endl;
//
//	Pet* pet = new Dog("Buddy", 3, 150.0, "Golden_Retriever");//name, age, price, breed
//	pet->displayInfo();
//
//	pet = new Cat("Whiskers", 2, 100.0, "Black");//name, age, price, color
//	pet->displayInfo();
//
//	pet = new Bird("Tweety", 1, 50.0, 25.0);//name, age, price, wingSpan
//	pet->displayInfo();
//
//	return 0;
//}