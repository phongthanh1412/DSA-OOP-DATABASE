#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==========================
// Bài 1
// ==========================

class Book {
private:
	string* bookID;
	string status;
public:
	Book(string bookID, string status);
	~Book();
	string getBookID();
	string getBookStatus();
	void setBookStatus(string status);
};

Book::Book(string bookID, string status) {
	this->bookID = new string(bookID);
	this->status = status;
}

Book::~Book() {
	delete bookID;
}

string Book::getBookID() {
	return *bookID;
}

string Book::getBookStatus() {
	return status;
}

void Book::setBookStatus(string status) {
	this->status = status;
}


class Member {
private:
	string memID;
	int bookCount;
public:
	Member(string memID);
	string getMemID();
	int getBookCount();
	bool borrowBook(Book& book);
};

Member::Member(string memID) {
	this->memID = memID;
	this->bookCount = 0;
}

string Member::getMemID() {
	return memID;
}

int Member::getBookCount() {
	return bookCount;
}

bool Member::borrowBook(Book& book) {
	bool maxBook = (bookCount >= 3);
	bool isCheckedOut = (book.getBookStatus() == "NO");

	if (maxBook) {
		cout << "Thanh vien " << memID << " da muon 3 quyen sach (khong the muon them)!\n";
		return false;
	}
	if (isCheckedOut) {
		cout << "Sach " << book.getBookID() << " da co nguoi muon!\n";
		return false;
	}

	// Mượn sách
	book.setBookStatus("NO");
	bookCount++;
	cout << "Thanh vien " << memID << " da muon sach " << book.getBookID() << " thanh cong!\n";
	return true;
}

// ==========================
// Bài 2
// ==========================

// Lớp Thời gian
class Time {
private:
	int hours, minutes, seconds;

public:
	Time(int hours, int minutes, int seconds);
	int getHours();
	int getMinutes();
	int getSeconds();
	int convertToSeconds();
	void display();
};

// Lớp Đồng hồ
class Clock {
private:
	string name;
	Time myTime;

public:
	Clock(string name, int hours, int minutes, int seconds);
	int getTime();
	void showClockInfo();
};

// Phương thức cho lớp Time
Time::Time(int hours, int minutes, int seconds) {
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}

int Time::getHours() {
	return hours;
}

int Time::getMinutes() {
	return minutes;
}

int Time::getSeconds() {
	return seconds;
}

int Time::convertToSeconds() {
	return hours * 3600 + minutes * 60 + seconds;
}

void Time::display() {
	cout << (hours < 10 ? "0" : "") << hours << ":"
		<< (minutes < 10 ? "0" : "") << minutes << ":"
		<< (seconds < 10 ? "0" : "") << seconds;
}

// Phương thức cho lớp Clock
Clock::Clock(string name, int hours, int minutes, int seconds)
	: name(name), myTime(hours, minutes, seconds) {}


int Clock::getTime() {
	return myTime.convertToSeconds();
}

void Clock::showClockInfo() {
	cout << "Dong ho " << name << " hien thi ";
	myTime.display();
	cout << "\nLuc nay da qua: " << getTime() << " giay.\n";
}

int main() {
	// Bai 1
	// Khởi tạo sách
	cout << "Bai 1\n";
	Book book1("B1", "NO");
	Book book2("B2", "YES");
	Book book3("B3", "NO"); 
	Book book4("B4", "YES");
	Book book5("B5", "YES");
	Book book6("B6", "YES");
	Book book7("B7", "YES");

	// Khởi tạo thành viên
	Member member1("23120154");
	Member member2("23120160");

	// Danh sách sách muốn mượn
	vector<Book*> bookInLibrary = { &book1, &book2, &book3, &book4, &book5, &book6, &book7 };

	cout << "Thanh vien " << member1.getMemID() << " dang muon sach thu vien...\n";

	// Thành viên mượn các sách trong thư viện
	for (Book* book : bookInLibrary) {
		member1.borrowBook(*book);
	}
	cout << "--------------------------------------" << endl;
	cout << "Thanh vien " << member2.getMemID() << " dang muon sach thu vien...\n";

	// Thành viên mượn các sách trong thư viện
	for (Book* book : bookInLibrary) {
		member2.borrowBook(*book);
	}
	cout << "Bai 2\n";
	// Bai 2
	string clockName;
	int hours, minutes, seconds;

	// Nhập thông tin đồng hồ
	cout << "Nhap ten dong ho: ";
	getline(cin, clockName);

	cout << "Nhap gio phut giay (hh mm ss): ";
	cin >> hours >> minutes >> seconds;

	// Tạo đối tượng đồng hồ
	Clock myClock(clockName, hours, minutes, seconds);

	// Hiển thị kết quả
	myClock.showClockInfo();
	return 0;
}