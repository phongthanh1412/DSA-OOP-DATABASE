#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <conio.h>

using namespace std;

class ATM {
private:
    map<int, int> denominations; // Menh gia -> so to
    const vector<int> standardDenominations = { 500000, 200000, 100000, 50000 };
    string inputFile;
    int totalAmount;

    void loadInitialState() {
        ifstream file(inputFile);
        if (!file.is_open()) {
            throw runtime_error("Khong the mo file input!");
        }

        string line;
        while (getline(file, line)) {
            if (line.find(':') != string::npos) {
                size_t colonPos = line.find(':');
                string denomStr = line.substr(0, colonPos);
                string countStr = line.substr(colonPos + 1);

                // Xoa dau cham trong menh gia (500.000 -> 500000)
                denomStr.erase(remove(denomStr.begin(), denomStr.end(), '.'), denomStr.end());

                try {
                    int denomination = stoi(denomStr);
                    int count = stoi(countStr);
                    denominations[denomination] = count;
                }
                catch (const invalid_argument& e) {
                    cerr << "Loi dinh dang so: " << e.what() << endl;
                    continue;
                }
            }
        }
        file.close();
        calculateTotal();
    }

    void calculateTotal() {
        totalAmount = 0;
        for (const auto& entry : denominations) {
            totalAmount += entry.first * entry.second;
        }
    }

    void saveState() {
        ofstream file(inputFile);
        if (!file.is_open()) {
            throw runtime_error("Khong the ghi file input!");
        }

        for (const auto& entry : denominations) {
            file << entry.first << ": " << entry.second << endl;
        }
        file.close();
    }

    bool tryStandardDispense(int amount) {
        for (int denom : standardDenominations) {
            if (denominations[denom] < 1) {
                return false;
            }
        }

        int remaining = amount - (500000 + 200000 + 100000 + 50000);
        if (remaining < 0) {
            return false;
        }

        map<int, int> tempDenoms = denominations;
        tempDenoms[500000]--;
        tempDenoms[200000]--;
        tempDenoms[100000]--;
        tempDenoms[50000]--;

        for (auto it = tempDenoms.rbegin(); it != tempDenoms.rend(); ++it) {
            int denom = it->first;
            while (remaining >= denom && tempDenoms[denom] > 0) {
                remaining -= denom;
                tempDenoms[denom]--;
            }
        }

        if (remaining == 0) {
            denominations = tempDenoms;
            return true;
        }
        return false;
    }

    bool tryFallbackDispense(int amount) {
        map<int, int> tempDenoms = denominations;
        int remaining = amount;

        for (auto it = tempDenoms.rbegin(); it != tempDenoms.rend(); ++it) {
            int denom = it->first;
            while (remaining >= denom && tempDenoms[denom] > 0) {
                remaining -= denom;
                tempDenoms[denom]--;
            }
        }

        if (remaining == 0) {
            denominations = tempDenoms;
            return true;
        }
        return false;
    }

    bool canDispense(int amount) {
        if (tryStandardDispense(amount)) {
            return true;
        }

        if (tryFallbackDispense(amount)) {
            return true;
        }

        return false;
    }

public:
    ATM(const string& filename) : inputFile(filename), totalAmount(0) {
        try {
            loadInitialState();
            // In số tờ tiền hiện có ngay sau khi đọc file
            cout << "So to tien hien co trong may ATM:" << endl;
            for (const auto& denom : denominations) {
                cout << denom.first << " VND: " << denom.second << " to" << endl;
            }
            cout << "-------------------\n";
            cout << "So du hien co: " << totalAmount << " VND" << endl;
        }
        catch (const exception& e) {
            cerr << "Loi khi khoi tao ATM: " << e.what() << endl;
            throw;
        }
    }

    void withdraw() {
        while (true) {
            /*cout << "So du hien co: " << totalAmount << " VND" << endl;*/
            cout << "Nhap so tien muon rut (x de thoat): ";
            int amount;
            cin >> amount;

            if (amount == 0) {
                saveState();
                cout << "Da luu trang thai va thoat." << endl;
                return;
            }

            try {
                if (amount <= 0) {
                    throw invalid_argument("So tien phai lon hon 0");
                }

                if (amount > totalAmount) {
                    throw runtime_error("Khong du tien trong may");
                }

                if (!canDispense(amount)) {
                    throw runtime_error("Khong the rut tien theo yeu cau");
                }

                cout << "Rut tien thanh cong: " << amount << " VND" << endl;
                calculateTotal();

                // Hien thi tat ca menh gia, ke ca nhung menh gia da het
                cout << "So to tien con lai:" << endl;
                for (const auto& denom : denominations) {
                    cout << denom.first << " VND: " << denom.second << " to" << endl;
                }
                cout << "-------------------\n";
                cout << "So du hien co: " << totalAmount << " VND" << endl;
            }
            catch (const exception& e) {
                cerr << "Loi: " << e.what() << endl;
            }

            cout << "Nhan phim bat ky de tiep tuc rut tien hoac X de thoat...";
            char key = _getch();
            if (key == 'X' || key == 'x') {
                saveState();
                cout << "\nDa luu trang thai va thoat." << endl;
                return;
            }
            cout << endl << endl;
        }
    }
};

int main() {
    try {
        ATM atm("input.txt");
        atm.withdraw();
    }
    catch (const exception& e) {
        cerr << "Loi nghiem trong: " << e.what() << endl;
        return 1;
    }
    return 0;
}