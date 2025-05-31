#include<iostream>
#include<string>
using namespace std;

class Book	 {
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

Book::Book():title(""), author(""), ISBN(""), available(true) {}
Book::Book(std::string title, std::string author, std::string ISBN) 
	:title(title), author(author), ISBN(ISBN), available(true) {}

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
	available = false;
}
void Book::returnBook() {
	available = true;
}
void Book::displayBook() {
	cout << "Title: " << title << endl;
	cout << "Author: " << author << endl;
	cout << "ISBN: " << ISBN << endl;
	cout << "Availability: " << available ? 1 : 0; << endl;
}

int main() {

}