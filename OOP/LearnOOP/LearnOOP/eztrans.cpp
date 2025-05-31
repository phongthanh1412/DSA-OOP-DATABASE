#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;
class Captain {
public:
    Captain();
    std::string encode(std::string time);
};

class Soldier {
private:
    int id;
public:
    Soldier();
    Soldier(int id);
    std::string decode(std::string s);
};

// Định nghĩa constructor và các hàm của lớp Captain

Captain::Captain() {}

std::string Captain::encode(std::string time) {
    // Tách các thành phần thời gian
    int hh, mm, ss;
    char colon;
    istringstream iss(time);
    iss >> hh >> colon >> mm >> colon >> ss;

    if (hh < 0 || hh > 23 || mm < 0 || mm > 59 || ss < 0 || ss > 59) {
        return "";
    }

    // Mã hóa thành nhị phân
    string binary = "";

    for (int i = 4; i >= 0; i--) {
        binary += (hh & (1 << i)) ? "1" : "0";
    }

    for (int i = 5; i >= 0; i--) {
        binary += (mm & (1 << i)) ? "1" : "0";
    }

    for (int i = 5; i >= 0; i--) {
        binary += (ss & (1 << i)) ? "1" : "0";
    }

    return binary;
}

// Định nghĩa constructor và các hàm của lớp Soldier

Soldier::Soldier() : id(0) {}

Soldier::Soldier(int id) : id(id) {}

std::string Soldier::decode(std::string s) {
    // Kiểm tra độ dài chuỗi nhị phân
    if (s.length() != 17) {
        return "00:00:00";
    }

    int hh = 0;
    for (int i = 0; i < 5; i++) {
        if (s[i] == '1') {
            hh += pow(2, 4 - i);
        }
    }

    int mm = 0;
    for (int i = 5; i < 11; i++) {
        if (s[i] == '1') {
            mm += pow(2, 10 - i);
        }
    }

    int ss = 0;
    for (int i = 11; i < 17; i++) {
        if (s[i] == '1') {
            ss += pow(2, 16 - i);
        }
    }

    if (hh > 23 || mm > 59 || ss > 59) {
        return "00:00:00";
    }

    // Định dạng lại thành chuỗi hh:mm:ss
    ostringstream oss;
    oss << setw(2) << setfill('0') << hh << ":"
        << setw(2) << setfill('0') << mm << ":"
        << setw(2) << setfill('0') << ss;

    return oss.str();
}

#include "main.h"

//int main() {
//    // Tạo đối tượng chỉ huy và binh lính
//    Captain captain;
//    Soldier soldier(2341);
//
//    string attackTime = "13:55:12";
//
//    string encoded = captain.encode(attackTime);
//
//    cout << "Thoi diem tan cong: " << attackTime << endl;
//    cout << "Ma hoa: " << encoded << endl;
//
//
//    string decoded = soldier.decode(encoded);
//    cout << "\nBinh linh 2341 nhan duoc: " << decoded << endl;
//
//    string invalidTime = "26:73:86";
//    string invalidEncoded = captain.encode(invalidTime);
//    cout << "\nThoi gian khong hop le: " << invalidTime << endl;
//    cout << "Ma hoa " << (invalidEncoded.empty() ? "khong hop le" : invalidEncoded) << endl;
//
//    string invalidBinary = "11111111111111111";
//    string decodedInvalid = soldier.decode(invalidBinary);
//    cout << "Giai ma khong hop le: " << decodedInvalid << endl;
//
//    return 0;
//}