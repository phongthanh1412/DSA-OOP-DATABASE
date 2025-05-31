#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
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

class Library {
private:
	vector<Book>books;
public:
	Library();
	void addBook(const Book& book);
	void removeBook(const std::string& ISBN);
	void displayAllBooks();
	std::vector<Book> searchBooksByAuthor(const std::string& author);
	std::vector<Book> searchBooksByTitle(const std::string& title);
	void borrowBook(const std::string& ISBN);
	void returnBook(const std::string& ISBN);
	void readBooksFromFile(const std::string& filename);
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
	cout << "Availability: " << (available ? "Available" : "Unavailable") << endl;
}

Library::Library() {}
void Library::addBook(const Book& book) {
	books.push_back(book);
}
void Library::removeBook(const std::string& ISBN) {
	for (auto it = books.begin(); it != books.end(); it++) {
		if (it->getISBN() == ISBN) {
			books.erase(it);
			return;
		}
	}
}
void Library::displayAllBooks() {
	if (books.empty()) return;
	cout << "There are " << books.size() << " books in the library:\n";
	for (int i = 0; i < books.size(); i++) {
		books[i].displayBook();
		if (i != books.size() - 1)
			cout << "======================\n";
	}
	cout << "****************************************\n";
}
std::vector<Book> Library::searchBooksByAuthor(const std::string& author) {
	vector<Book>myBooks;
	for (int i = 0; i < books.size(); i++) {
		if (books[i].getAuthor() == author) {
			myBooks.push_back(books[i]);
		}
	}
	return myBooks;
}
std::vector<Book> Library::searchBooksByTitle(const std::string& title) {
	vector<Book>myBooks;
	for (int i = 0; i < books.size(); i++) {
		if (books[i].getTitle() == title) {
			myBooks.push_back(books[i]);
		}
	}
	return myBooks;
}
void Library::borrowBook(const std::string& ISBN) {
	for (int i = 0; i < books.size(); i++) {
		if (books[i].getISBN() == ISBN) {
			books[i].borrowBook();
		}
	}
}
void Library::returnBook(const std::string& ISBN) {
	for (int i = 0; i < books.size(); i++) {
		if (books[i].getISBN() == ISBN) {
			books[i].returnBook();
		}
	}
}
void Library::readBooksFromFile(const std::string& filename) {
	fstream inFile;
	inFile.open(filename, ios::in);
	if (!inFile.is_open()) {
		cout << "File is not found.";
		return;
	}
	int numBooks;
	inFile >> numBooks;
	inFile.ignore();
	int i = 0;
	string title, author, ISBN;
	while (i < numBooks) {
		getline(inFile, title);
		getline(inFile, author);
		getline(inFile, ISBN);

		books.push_back(Book(title, author, ISBN));
		i++;
	}

	inFile.close();
}

#include"main.h"
//int main() {
//	Library library;
//	library.readBooksFromFile("library.txt");
//	library.addBook(Book("Thien ac va smartphone", "Dang Hoang Giang", "456abc"));
//	library.displayAllBooks();
//
//	library.addBook(Book("Buc xuc khong lam ta vo can", "Dang Hoang Giang", "123xyz"));
//	std::vector<Book> books = library.searchBooksByAuthor("Dang Hoang Giang");
//	for (Book book : books) library.borrowBook(book.getISBN());
//	books = library.searchBooksByTitle("Thien ac va smartphone");
//	for (Book book : books) library.removeBook(book.getISBN());
//	library.removeBook("978-3-16-148413-1");
//	library.displayAllBooks();
//
//	return 0;
//}