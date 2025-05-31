#include <iostream>
#include <string>
#include <cmath> 

using namespace std;

class Fraction {
private:
    int num, den;

public:
    Fraction();
    Fraction(int num, int den);
    std::string to_string();
    Fraction add(Fraction other);
    Fraction subtract(Fraction other);
    Fraction multiply(Fraction other);
    Fraction divide(Fraction other);
    void simplify();
    int getNumerator();
    int getDenominator();
    void setNumerator(int num);
    void setDenominator(int den);
    int gcd(int a, int b);
};

Fraction::Fraction() {
    num = 0;
    den = 1;
}

Fraction::Fraction(int num, int den) {
    this->num = num;
    this->den = den;
}

std::string Fraction::to_string() {
    return std::to_string(num) + "/" + std::to_string(den);
}

Fraction Fraction::add(Fraction other) {
    Fraction res;
    res.num = this->num * other.den + other.num * this->den;
    res.den = this->den * other.den;
    res.simplify();
    return res;
}

Fraction Fraction::subtract(Fraction other) {
    Fraction res;
    res.num = this->num * other.den - other.num * this->den;
    res.den = this->den * other.den;
    res.simplify();
    return res;
}

Fraction Fraction::multiply(Fraction other) {
    Fraction res;
    res.num = this->num * other.num;
    res.den = this->den * other.den;
    res.simplify();
    return res;
}

Fraction Fraction::divide(Fraction other) {
    Fraction res;
    res.num = this->num * other.den;
    res.den = this->den * other.num;
    res.simplify();
    return res;
}

void Fraction::simplify() {
    int greatesCom = gcd(abs(num), abs(den));
    num /= greatesCom;
    den /= greatesCom;
    if (den < 0) {
        num = -num;
        den = abs(den);
    }
}

int Fraction::getNumerator() {
    return num;
}

int Fraction::getDenominator() {
    return den;
}

void Fraction::setNumerator(int num) {
    this->num = num;
}

void Fraction::setDenominator(int den) {
    this->den = den;
}

int Fraction::gcd(int a, int b) {
    if (a == 0 || b == 0) {
        return a + b;
    }
    while (a != b) {
        if (a > b) a -= b;
        else b -= a;
    }
    return a;
}

#include "main.h"
//int main() {
//    Fraction fr1(12, 4);
//    Fraction fr2(5, 7);
//
//    string str = fr1.to_string();
//    cout << str << endl;
//
//    // Test add
//    Fraction sum = fr1.add(fr2);
//    cout << "Sum: " << sum.to_string() << endl;
//
//    // Test subtract
//    Fraction difference = fr1.subtract(fr2);
//    cout << "Difference: " << difference.to_string() << endl;
//
//    // Test multiply
//    Fraction product = fr1.multiply(fr2);
//    cout << "Product: " << product.to_string() << endl;
//
//    // Test divide
//    Fraction quotient = fr1.divide(fr2);
//    cout << "Quotient: " << quotient.to_string() << endl;
//
//    return 0;
//}