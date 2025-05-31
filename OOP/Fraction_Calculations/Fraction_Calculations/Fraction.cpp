#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

class Fraction {
private:
	int num, denom;
public:
	Fraction(int num = 0, int denom = 1);
	void simplify();
	Fraction operator+(const Fraction& other) const;
	bool operator<(const Fraction& other) const;
	void output() const;
	friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);

	int gcd(int a, int b);
};

class FractionArray {
private:
	vector<Fraction>fractions;
public:
	void loadFromFile(const std::string& filename);
	Fraction sum() const;
	Fraction max() const;
	Fraction min() const;
	void sortArray();
	void output() const;
};

Fraction::Fraction(int num, int denom) {
	this->num = num;
	this->denom = denom;
}
int Fraction::gcd(int a, int b) {
	if (a == 0 || b == 0) return a + b;
	while (a != b) {
		if (a > b) a -= b;
		else b -= a;
	}
	return a;
}
void Fraction::simplify() {
	int greatestCom = gcd(abs(num), abs(denom));
	num /= greatestCom;
	denom /= greatestCom;

	if (denom < 0) {
		num = -num;
		denom = abs(denom);
	}
}
Fraction Fraction::operator+(const Fraction& other) const {
	Fraction frc;
	frc.num = num * other.denom + denom * other.num;
	frc.denom = denom * other.denom;
	frc.simplify();
	return frc;
}
bool Fraction::operator<(const Fraction& other) const {
	return num * other.denom < denom * other.num;
}
void Fraction::output() const {
	Fraction temp = *this;
	temp.simplify();
	cout << temp.num << '/' << temp.denom << endl;
}


std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
	Fraction temp = frac;
	temp.simplify();
	os << temp.num << '/' << temp.denom << endl;
	return os;
}

void FractionArray::loadFromFile(const std::string& filename) {
	fstream inFile;
	inFile.open(filename, ios::in);
	if (!inFile.is_open()) {
		cout << "File is not found.";
		return;
	}
	int num, denom;
	while (inFile >> num >> denom) {
		fractions.emplace_back(num, denom);
	}
	inFile.close();
}
Fraction FractionArray::sum() const {
	Fraction frc_sum;
	for (auto& it : fractions) {
		frc_sum = frc_sum + it;
	}
	return frc_sum;
}
Fraction FractionArray::max() const {
	return *max_element(fractions.begin(), fractions.end());

}
Fraction FractionArray::min() const {
	return *min_element(fractions.begin(), fractions.end());
}
void FractionArray::sortArray() {
	
	sort(fractions.begin(), fractions.end());
}
void FractionArray::output() const {
	for (auto& it : fractions) {
		cout << it;
	}
}
#include"main.h"
//int main() {
//	//Fraction frc1(-4, 6);
//	//Fraction frc2(2, 8);
//	//Fraction frc = frc1 + frc2;
//	////frc.output();
//	//cout << frc;
//
//	FractionArray fractions;
//	fractions.loadFromFile("input.txt");
//	cout << fractions.sum();
//	cout << fractions.max();
//	cout << fractions.min();
//	fractions.sortArray();
//	fractions.output();
//	
//	return 0;
//}