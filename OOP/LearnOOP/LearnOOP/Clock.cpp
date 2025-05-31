#include<iostream>
using namespace std;

class Clock {
private:
	int hours, minutes, seconds;
public:
	Clock();
	Clock(int hours, int minutes, int seconds);
	void input();
	void output();
	void normalize();
	bool operator>=(Clock);
	Clock operator+(Clock);
	Clock& operator++();
};

Clock::Clock() {
	hours = 0;
	minutes = 0;
	seconds = 0;
}

Clock::Clock(int hours, int minutes, int seconds) {
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}

void Clock::input() {
	cin >> hours >> minutes >> seconds;
}

void Clock::output() {
	cout << hours << ":" << minutes << ":" << seconds << endl;
}

void Clock::normalize() {
	if (seconds >= 60) {
		minutes += seconds / 60;
		seconds %= 60;
	}

	if (minutes >= 60) {
		hours += minutes / 60;
		minutes %= 60;
	}

	if (hours >= 24) {
		hours %= 24;
	}
}

bool Clock::operator>=(Clock other) {
	return (hours > other.hours) || (hours == other.hours && minutes > other.minutes) ||
		(hours == other.hours && minutes == other.minutes && seconds > other.seconds);
}

Clock Clock::operator+(Clock other) {
	Clock myClock;
	myClock.hours = hours + other.hours;
	myClock.minutes = minutes + other.minutes;
	myClock.seconds = seconds + other.seconds;
	myClock.normalize();
	return myClock;
}

Clock& Clock::operator++() {
	minutes++;
	normalize();
	return *this;
}

int main() {
	Clock clk1(10, 45, 30);
	Clock clk2(2, 30, 45);

	Clock clk = clk1 + clk2;
	cout << "Time after calculate sum: ";
	clk.output();

	cout << "Time after increase 1 minutes: ";
	++clk;
	clk.output();

	if (clk1 >= clk2) cout << "Time of clock1 is greater than or equal to time of clock2\n";
	else cout << "Time of clock1 is less than time of clock2\n";

	return 0;
}