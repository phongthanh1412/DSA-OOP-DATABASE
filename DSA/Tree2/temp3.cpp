#include <iostream>
#include <string>
using namespace std;

bool hasDigit(const string& s, char digit) {
    for (char c : s) {
        if (c == digit) return true;
    }
    return false;
}

bool isEven(int n) {
    return (n % 2 == 0);
}

int main() {
    int count = 0;
    for (int i = 0; i < 10000; i++) {
        string s = to_string(i);
        if (hasDigit(s, '0') && hasDigit(s, '5') && isEven(i)) {
            count++;
        }
    }
    cout << "So luong so thoa man: " << count << endl;
    return 0;
}
