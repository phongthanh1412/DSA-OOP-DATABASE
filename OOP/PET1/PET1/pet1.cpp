#include<iostream>
#include<string>
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
};

Pet::Pet(): name(""), age(0), price(0.0) {}
Pet::Pet(string name, int age, float price)
	: name(name), age(age), price(price) {}

Pet::~Pet(){}

class Dog : public Pet {
private:
	string breed;
public:

	Dog();
	Dog(string name, int age, float price, string breed);
	void makeSound() const override;
};

Dog::Dog() : Pet(), breed("") {}
Dog::Dog(string name, int age, float price, string breed) 
	: Pet(name, age, price), breed(breed) {}

void Dog::makeSound() const {
	cout << "Woof!\n";
}

class Cat : public Pet {
private:
	string color;
public:
	Cat();
	Cat(string name, int age, float price, string color);
	void makeSound() const override;
};

Cat::Cat() : Pet(), color("") {}
Cat::Cat(string name, int age, float price, string color) 
	: Pet(name, age, price), color(color) {}

void Cat::makeSound() const {
	cout << "Meow!\n";
}

class Bird : public Pet {
private:
	float wingSpan;
public:
	Bird();
	Bird(string name, int age, float price, float wingSpan);
	void makeSound() const override;
};

Bird::Bird() : Pet(), wingSpan(0.0) {}
Bird::Bird(string name, int age, float price, float wingSpan)
	: Pet(name, age, price), wingSpan(wingSpan) {}

void Bird::makeSound() const {
	cout << "Chirp!\n";
}

#include"main.h"

//int main() {
//	int testID;
//	std::cin >> testID;
//	std::cout << "Test " << testID << ":" << std::endl;
//
//	Pet* pet = new Dog("Buddy", 3, 150.0, "Golden_Retriever");//name, age, price, breed
//	pet->makeSound();
//
//	pet = new Cat("Whiskers", 2, 100.0, "Black");//name, age, price, color
//	pet->makeSound();
//
//	pet = new Bird("Tweety", 1, 50.0, 25.0);//name, age, price, wingSpan
//	pet->makeSound();
//
//	delete pet;
//
//	return 0;
//}