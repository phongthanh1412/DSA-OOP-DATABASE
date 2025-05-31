#include<iostream>
#include<sstream>
#include<string>
#include<iomanip>
#include<vector>
using namespace std;

class Book {
protected:
	string type, name, author;
	int year;
	float price;
public:
	Book();
	Book(string name, string author, int year, float price);
	virtual ~Book();
	virtual string getType() const = 0;
	virtual string getName() const = 0;
	virtual string getAuthor() const = 0;
	virtual int getYear() const = 0;
	virtual float getPrice() const = 0;
	virtual string getSpecial() const = 0;
	virtual void display() const = 0;
};
Book::Book() :type(""), name(""), author(""), year(0), price(0.0) {}
Book::Book(string name, string author, int year, float price)
	:name(name), author(author), year(year), price(price) {}
Book::~Book() {}

class Fiction : public Book {
private:
	string award;
public:
	Fiction();
	Fiction(string name, string author, int year, float price, string award);
	string getType() const override;
	string getName() const override;
	string getAuthor() const override;
	int getYear() const override;
	float getPrice() const override;
	string getSpecial() const override;
	string getAward() const;
	void display() const override;
};

Fiction::Fiction() :Book(), award("") {}
Fiction::Fiction(string name, string author, int year, float price, string award)
	:Book(name, author, year, price), award(award) {
	type = "Fiction";
}

string Fiction::getType() const {
	return type;
}
string Fiction::getName() const {
	return name;
}
string Fiction::getAuthor() const {
	return author;
}
int Fiction::getYear() const {
	return year;
}
float Fiction::getPrice() const {
	return price;
}
string Fiction::getAward() const {
	return award;
}
string Fiction::getSpecial() const {
	return award;
}
void Fiction::display() const {
	cout << left << setw(10) << getType() << " | "
		<< setw(24) << getName() << " | "
		<< setw(18) << getAuthor() << " | "
		<< setw(6) << getYear() << " | "
		<< setw(10) << fixed << setprecision(2) << getPrice() << " | "
		<< getSpecial() << endl;
}

class NonFiction : public Book {
private:
	string genre;
public:
	NonFiction();
	NonFiction(string name, string author, int year, float price, string genre);
	string getType() const override;
	string getName() const override;
	string getAuthor() const override;
	int getYear() const override;
	float getPrice() const override;
	string getSpecial() const override;
	string getGenre() const;
	void display() const override;
};

NonFiction::NonFiction() :Book(), genre("") {}
NonFiction::NonFiction(string name, string author, int year, float price, string genre)
	:Book(name, author, year, price), genre(genre) {
	type = "NonFiction";
}

string NonFiction::getType() const {
	return type;
}
string NonFiction::getName() const {
	return name;
}
string NonFiction::getAuthor() const {
	return author;
}
int NonFiction::getYear() const {
	return year;
}
float NonFiction::getPrice() const {
	return price;
}
string NonFiction::getGenre() const {
	return genre;
}
string NonFiction::getSpecial() const {
	return genre;
}
void NonFiction::display() const {
	cout << left << setw(10) << getType() << " | "
		<< setw(24) << getName() << " | "
		<< setw(18) << getAuthor() << " | "
		<< setw(6) << getYear() << " | "
		<< setw(10) << fixed << setprecision(2) << getPrice() << " | "
		<< getSpecial() << endl;
}

class Comic : public Book {
private:
	string series;
public:
	Comic();
	Comic(string name, string author, int year, float price, string series);
	string getType() const override;
	string getName() const override;
	string getAuthor() const override;
	int getYear() const override;
	float getPrice() const override;
	string getSpecial() const override;
	string getSeries() const;
	void display() const override;
};

Comic::Comic() :Book(), series("") {}
Comic::Comic(string name, string author, int year, float price, string series)
	:Book(name, author, year, price), series(series) {
	type = "Comic";
}

string Comic::getType() const {
	return type;
}
string Comic::getName() const {
	return name;
}
string Comic::getAuthor() const {
	return author;
}
int Comic::getYear() const {
	return year;
}
float Comic::getPrice() const {
	return price;
}
string Comic::getSeries() const {
	return series;
}
string Comic::getSpecial() const {
	return series;
}
void Comic::display() const {
	cout << left << setw(10) << getType() << " | "
		<< setw(24) << getName() << " | "
		<< setw(18) << getAuthor() << " | "
		<< setw(6) << getYear() << " | "
		<< setw(10) << fixed << setprecision(2) << getPrice() << " | "
		<< getSpecial() << endl;
}

class Library {
private:
	vector<Book*> library;
public:
	Library();
	~Library();
	void addBook(Book* book);
	void display();
};
Library::Library() {}
Library::~Library() {
	for (Book* book : library)
		delete book;
}
void Library::addBook(Book* book) {
	library.push_back(book);
}
void Library::display() {
		cout << left << setw(10) << "Type" << " | "
		<< setw(24) << "Name" << " | "
		<< setw(18) << "Author" << " | "
		<< setw(6) << "Year" << " | "
		<< setw(10) << "Price" << " | "
		<< "Special" << endl;
	cout << string(100, '-') << endl;
	for (Book* book : library) {
		book->display();
	}
}

class Parser {
public:
	static Book* parseBook(const string& input);
};

Book* Parser::parseBook(const string& input) {
	stringstream stream(input);
	string type, name, author, specialty;
	int year;
	float price;
	char comma;

	getline(stream, type, ',');
	getline(stream, name, ',');
	getline(stream, author, ',');
	stream >> year >> comma >> price >> comma;
	getline(stream, specialty);

	if (type == "Fiction") {
		return new Fiction(name, author, year, price, specialty);
	}
	else if (type == "NonFiction") {
		return new NonFiction(name, author, year, price, specialty);
	}
	else if (type == "Comic") {
		return new Comic(name, author, year, price, specialty);
	}
	return nullptr;
}
#include"main.h"
//int main() {
//	int testID;
//	std::cin >> testID;
//	std::cout << "Test " << testID << ":" << std::endl;
//
//	Library library;
//	library.addBook(new Fiction("To Kill a Mockingbird", "Harper Lee", 1960, 18.99, "Pulitzer Prize"));
//	library.addBook(new NonFiction("Sapiens", "Yuval Noah Harari", 2011, 22.50, "History"));
//	library.addBook(new Comic("Spider-Man", "Stan Lee", 1962, 12.75, "Superhero"));
//
//	std::vector<std::string> inputs = {
//		"Fiction,1984,George Orwell,1949,15.00,Dystopian",
//		"NonFiction,Educated,Tara Westover,2018,20.00,Memoir",
//		"Comic,Batman,Bob Kane,1939,13.99,Detective"
//	};
//
//	for (const auto& input : inputs) {
//		Book* book = Parser::parseBook(input);
//		library.addBook(book);
//	}
//
//	library.display();
//
//	return 0;
//}
