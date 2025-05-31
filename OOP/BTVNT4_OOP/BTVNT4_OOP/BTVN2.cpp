#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

#define CURRENT_YEAR 2025
#define MALE 'M'
#define FEMALE 'F'

class NgayThang {
private:
    int day, month, year;
public:
    NgayThang() : day(0), month(0), year(0) {}
    NgayThang(int d, int m, int y) : day(d), month(m), year(y) {}

    bool operator>(const NgayThang& other) const {
        if (year != other.year) return year > other.year;
        if (month != other.month) return month > other.month;
        return day > other.day;
    }

    int getYear() const { return year; }
};

class Player {
private:
    string name;
    char gender;
    NgayThang dob;
public:
    Player() : name(""), gender('M'), dob() {}
    Player(string n, char g, NgayThang d) : name(n), gender(g), dob(d) {}

    int getAge() const {
        return CURRENT_YEAR - dob.getYear();
    }

    string getName() const { return name; }
    char getGender() const { return gender; }
    NgayThang getDob() const { return dob; }

    friend ostream& operator<<(ostream& os, const Player& p);
};

class ManagePlayers {
private:
    vector<Player> players;
public:
    void addPlayer(const Player& p) {
        players.push_back(p);
    }

    Player findYoungestMale() const;

    // Khai báo hàm nhập/xuất
    friend ifstream& operator>>(ifstream& ifile, ManagePlayers& m);
    friend ofstream& operator<<(ofstream& ofile, const ManagePlayers& m);
};

// Định nghĩa toán tử nhập (đọc từ file)
ifstream& operator>>(ifstream& ifile, ManagePlayers& m) {
    string line;
    while (getline(ifile, line)) {
        stringstream ss(line);
        string temp, name;
        int day, month, year;
        char gender, c;

        ss >> temp; // Bỏ số thứ tự
        name = "";
        while (ss >> temp) {
            if (isdigit(temp[0])) break; // Gặp số thì dừng lấy tên
            if (!name.empty()) name += " ";
            name += temp;
        }

        stringstream dateStream(temp);
        dateStream >> day >> c >> month >> c >> year; // Đọc ngày sinh bỏ qua '/'

        ss >> gender;
        m.addPlayer(Player(name, gender, NgayThang(day, month, year)));
    }
    return ifile;
}

// Định nghĩa toán tử xuất (ghi ra file)
ofstream& operator<<(ofstream& ofile, const ManagePlayers& m) {
    Player youngestMale = m.findYoungestMale();
    if (youngestMale.getName() != "")
        ofile << youngestMale.getName() << " " << youngestMale.getAge() << "\n";
    else
        ofile << "No male player found.\n";

    return ofile;
}

// Định nghĩa hàm tìm cầu thủ nam trẻ nhất
Player ManagePlayers::findYoungestMale() const {
    Player youngestMale;
    bool foundMale = false;

    for (const auto& player : players) {
        if (player.getGender() == MALE) {
            if (!foundMale || player.getDob() > youngestMale.getDob()) {
                youngestMale = player;
            }
            foundMale = true;
        }
    }

    return youngestMale;
}

// Định nghĩa toán tử xuất cho Player
ostream& operator<<(ostream& os, const Player& p) {
    os << p.getName() << " (" << p.getAge() << " tuoi, " << (p.getGender() == MALE ? "Nam" : "Nu") << ")";
    return os;
}

int main() {
    ifstream ifile("INPUT.txt");
    ofstream ofile("OUTPUT.txt");

    if (!ifile.is_open()) {
        cerr << "Error opening INPUT file!\n";
        return 1;
    }
    if (!ofile.is_open()) {
        cerr << "Error opening OUTPUT file!\n";
        return 1;
    }

    ManagePlayers manager;
    ifile >> manager;
    ofile << manager;

    return 0;
}
