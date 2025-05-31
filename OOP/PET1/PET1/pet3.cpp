#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
#include<sstream>
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

class Parser {
public:
	static Pet* parsePet(const string& input);
};

Pet* Parser::parsePet(const string& input) {
	stringstream stream(input);
	string type;
	stream >> type;
	if (type == "Dog") {
		string name, breed;
		int age;
		float price;
		stream >> name >> age >> price >> breed;
		return new Dog(name, age, price, breed);
	}
	else if (type == "Cat") {
		string name, color;
		int age;
		float price;
		stream >> name >> age >> price >> color;
		return new Cat(name, age, price, color);
	}
	else if (type == "Bird") {
		string name;
		int age;
		float price, wingSpan;
		stream >> name >> age >> price >> wingSpan;
		return new Bird(name, age, price, wingSpan);
	}
	return nullptr;
}
class PetStore {
private:
	vector<Pet*> store;

public:
	PetStore();
	~PetStore();
	void addPet(Pet* pet);
	void display();
};

PetStore::PetStore(){}
PetStore::~PetStore() {
	for (Pet* pet : store) {
		delete pet;
	}
}

void PetStore::addPet(Pet* pet) {
	store.push_back(pet);
}
void PetStore::display() {
	cout << left << setw(10) << "Type" << " | "
		<< setw(16) << "Name" << " | "
		<< setw(6) << "Age" << " | "
		<< setw(12) << "Price" << " | "
		<< setw(16) << "Special" << endl;
	cout << string(70, '-') << endl;
	for (int i = 0; i < store.size(); i++) {
		store[i]->displayInfo();
	}
}
#include"main.h"

//int main() {
//	int testID;
//	std::cin >> testID;
//	std::cout << "Test " << testID << ":" << std::endl;
//
//	PetStore store;
//	store.addPet(new Bird("Rio", 1, 150.0, 12.5));
//	store.addPet(new Dog("Lucky", 2, 120.0, "Vietnam"));
//	store.addPet(new Cat("Milu", 1, 100.0, "Gray"));
//
//	std::vector<std::string> inputs = {
//		"Dog Buddy 3 150.0 Golden_Retriever",
//		"Cat Whiskers 2 100.0 Black",
//		"Bird Tweety 1 50.0 25.0"
//	};
//
//	for (const auto& input : inputs) {
//		Pet* pet = Parser::parsePet(input);
//		store.addPet(pet);
//	}
//
//	store.display();
//
//	return 0;
//}