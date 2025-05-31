#include<iostream>
using namespace std;

class Fraction {
private:
	int num, den;
public:
	Fraction();
	Fraction(int num, int den);
	int getNum();
	int getDen();
	void setNum(int num);
	void setDen(int den);
	void input();
	void output();
	Fraction operator+(Fraction);
	Fraction operator-(Fraction);
	Fraction operator*(Fraction);
	Fraction operator/(Fraction);
};

Fraction::Fraction() {
	num = 1;
	den = 1;
}

Fraction::Fraction(int num, int den) {
	this->num = num;
	this->den = den;
}

int Fraction::getNum() {
	return num;
}

int Fraction::getDen() {
	return den;
}

void Fraction::setNum(int num) {
	this->num = num;
}

void Fraction::setDen(int den) {
	this->den = den;
}

void Fraction::input() {
	cin >> num >> den;
}

void Fraction::output() {
	cout << num << "/" << den << endl;
}

Fraction Fraction::operator+(Fraction other) {
	Fraction res;
	res.num = num * other.den + den * other.num;
	res.den = den * other.den;
	return res;
}

Fraction Fraction::operator-(Fraction other) {
	Fraction res;
	res.num = num * other.den - den * other.num;
	res.den = den * other.den;
	return res;
}

Fraction Fraction::operator*(Fraction other) {
	Fraction res;
	res.num = num * other.num;
	res.den = den * other.den;
	return res;
}

Fraction Fraction::operator/(Fraction other) {
	Fraction res;
	res.num = num * other.den;
	res.den = den * other.num;
	return res;
}


int main() {
	Fraction frac1;
	frac1.setNum(5);
	frac1.setDen(7);

	Fraction frac2(8, 9);

	Fraction frac = frac1 + frac2;
	frac.output();

	return 0;
}