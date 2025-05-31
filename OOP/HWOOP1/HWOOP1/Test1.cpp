#include <iostream> 
#include <string> 
#include <algorithm> 
#include <vector> 
using namespace std;

class Fraction {
private:
    int num, den;
public:
    Fraction();
    Fraction(int num, int den);

    double valueOfFraction() const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;

    friend ostream& operator<<(ostream& os, const Fraction& frac);
    friend istream& operator>>(istream& is, Fraction& frac);
};

Fraction::Fraction() : num(1), den(1) {}

Fraction::Fraction(int num, int den) : num(num), den(den) {}

double Fraction::valueOfFraction() const {
    return static_cast<double>(num) / den;
}

bool Fraction::operator<(const Fraction& other) const {
    return this->valueOfFraction() < other.valueOfFraction();
}

bool Fraction::operator>(const Fraction& other) const {
    return this->valueOfFraction() > other.valueOfFraction();
}

ostream& operator<<(ostream& os, const Fraction& frac) {
    os << frac.num << " " << frac.den;
    return os;
}

istream& operator>>(istream& is, Fraction& frac) {
    is >> frac.num >> frac.den;
    return is;
}

template <typename T>
void input(vector<T>& vt) {
    T value;
    cin >> value;
    vt.push_back(value);
}

template <typename T>
void output(const vector<T>& vt) {
    for (const auto& val : vt) {
        cout << val << endl;
    }
}

template <typename T>
void sorting(const string& orderType, int n) {
    vector<T> arr;
    for (int i = 0; i < n; i++) {
        input(arr);
    }

    if (orderType == "increase") sort(arr.begin(), arr.end());
    else  sort(arr.begin(), arr.end(), greater<T>());

    output(arr);
}

int main() {
    string orderType, type;
    int n;
    cin >> orderType >> type >> n;

    if (type == "int") sorting<int>(orderType, n);
    else if (type == "char") sorting<char>(orderType, n);
    else if (type == "fraction") sorting<Fraction>(orderType, n);
    else if (type == "string") sorting<string>(orderType, n);

    return 0;
}