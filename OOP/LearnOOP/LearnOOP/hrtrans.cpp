#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Captain {
public:
    Captain();
    std::string encode(std::string time);
    std::string addHammingCode(std::string data);
};

class Soldier {
private:
    int id;
public:
    Soldier();
    Soldier(int id);
    std::string decode(std::string s);
    std::string correctHammingCode(std::string s);
};

Captain::Captain() {}

std::string Captain::addHammingCode(std::string data) {

    vector<char> bits(data.begin(), data.end());
    vector<char> hammingCode;

    int totalBits = 22;
    hammingCode.resize(totalBits + 1, '0'); 

    int dataPos = 0;
    for (int i = 1; i <= totalBits; i++) {
        if ((i & (i - 1)) != 0) { 
            if (dataPos < bits.size()) {
                hammingCode[i] = bits[dataPos++];
            }
            else {
                hammingCode[i] = '0'; 
            }
        }
    }

    for (int i = 1; i <= totalBits; i *= 2) {
        int parity = 0;
        for (int j = i; j <= totalBits; j++) {
            if ((j & i) == i) {
                parity ^= (hammingCode[j] - '0');
            }
        }
        hammingCode[i] = parity + '0';
    }

    string result;
    for (int i = 1; i <= totalBits; i++) {
        result += hammingCode[i];
    }

    return result;
}

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

    // Add Hamming code
    return addHammingCode(binary);
}

Soldier::Soldier() : id(0) {}

Soldier::Soldier(int id) : id(id) {}

std::string Soldier::correctHammingCode(std::string s) {
    if (s.length() != 22) {
        return s; 
    }

    vector<char> bits(s.begin(), s.end());
    int totalBits = 22;
    int errorPos = 0;

    for (int i = 1; i <= totalBits; i *= 2) {
        int parity = 0;
        for (int j = i; j <= totalBits; j++) {
            if ((j & i) == i) {
                parity ^= (bits[j - 1] - '0');
            }
        }
        if (parity != 0) {
            errorPos += i;
        }
    }

    if (errorPos != 0 && errorPos <= totalBits) {
        bits[errorPos - 1] = (bits[errorPos - 1] == '0') ? '1' : '0';
    }

    string corrected;
    for (int i = 1; i <= totalBits; i++) {
        if ((i & (i - 1)) != 0) { 
            corrected += bits[i - 1];
        }
    }

    return corrected;
}

std::string Soldier::decode(std::string s) {
    string corrected = correctHammingCode(s);

    if (corrected.length() != 17) {
        return "00:00:00";
    }

    int hh = 0;
    for (int i = 0; i < 5; i++) {
        if (corrected[i] == '1') {
            hh += pow(2, 4 - i);
        }
    }

    int mm = 0;
    for (int i = 5; i < 11; i++) {
        if (corrected[i] == '1') {
            mm += pow(2, 10 - i);
        }
    }

    int ss = 0;
    for (int i = 11; i < 17; i++) {
        if (corrected[i] == '1') {
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
//    string corrupted = encoded;
//    if (!corrupted.empty()) {
//        corrupted[5] = (corrupted[5] == '0') ? '1' : '0';
//    }
//
//    string decoded = soldier.decode(corrupted);
//    cout << "\nBinh linh 2341 nhan duoc (voi 1 bit loi): " << decoded << endl;
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