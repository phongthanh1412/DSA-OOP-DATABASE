#include<iostream>
#include<string>
using namespace std;

class Book {
private:
	std::string title;
	std::string author;
	std::string ISBN;
	bool available;
public:
	Book();
	Book(std::string title, std::string author, std::string ISBN);
	std::string getTitle();
	void setTitle(std::string title);
	std::string getAuthor();
	void setAuthor(std::string author);
	std::string getISBN();
	void setISBN(std::string ISBN);
	bool isAvailable();
	void borrowBook();
	void returnBook();
	void displayBook();
};

Book::Book() : title(""), author(""), ISBN(""), available(1) {}
Book::Book(std::string title, std::string author, std::string ISBN) 
	: title(title), author(author), ISBN(ISBN), available(1) {}
std::string Book::getTitle() {
	return title;
}
void Book::setTitle(std::string title) {
	this->title = title;
}
std::string Book::getAuthor() {
	return author;
}
void Book::setAuthor(std::string author) {
	this->author = author;
}
std::string Book::getISBN() {
	return ISBN;
}
void Book::setISBN(std::string ISBN) {
	this->ISBN = ISBN;
}
bool Book::isAvailable() {
	return available;
}
void Book::borrowBook() {
	available = 0;
}
void Book::returnBook() {
	available = 1;
}
void Book::displayBook() {
	cout << "Title: " << title << endl;
	cout << "Author: " << author << endl;
	cout << "ISBN: " << ISBN << endl;
	cout << "Availability: " << (available ? "Available" : "Unavailable") << endl << endl;
}
#include"main.h"
//int main() {
//	Book bk1("The Great Gatsby", "F.Scott Fitzgerald", "978-3-16-148410-0");
//	Book bk2("To Kill a Mockingbird", "Harper Lee", "978-3-16-148411-7");
//	Book bk3("1984", "George Orwell", "978-3-16-148412-4");
//	bk1.displayBook();
//	bk2.displayBook();
//	bk3.displayBook();
//}