#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

class WordAnalyser {
private:
    map<string, int> wordCount;
public:
    pair<string, int> getMostWord() const;

    // Khai báo toán tử nhập/xuất
    friend ifstream& operator>>(ifstream& ifile, WordAnalyser& wa);
    friend ofstream& operator<<(ofstream& ofile, const WordAnalyser& wa);
};

// Định nghĩa toán tử nhập (đọc từ file)
ifstream& operator>>(ifstream& ifile, WordAnalyser& wa) {
    if (!ifile.is_open()) {
        cerr << "Error: Cannot open input file.\n";
        return ifile;
    }

    string word;
    while (ifile >> word) {
        wa.wordCount[word]++;
    }

    return ifile;
}

// Định nghĩa toán tử xuất (ghi ra file)
ofstream& operator<<(ofstream& ofile, const WordAnalyser& wa) {
    if (!ofile.is_open()) {
        cerr << "Error: Cannot open output file.\n";
        return ofile;
    }

    pair<string, int> result = wa.getMostWord();
    ofile << result.first << " " << result.second;

    return ofile;
}

// Định nghĩa hàm tìm từ xuất hiện nhiều nhất
pair<string, int> WordAnalyser::getMostWord() const {
    int maxi = 0;
    string mostWord;
    for (const auto& pair : wordCount) {
        if (pair.second > maxi) {
            mostWord = pair.first;
            maxi = pair.second;
        }
    }
    return { mostWord, maxi };
}

int main() {
    ifstream ifile("INPUT.TXT");
    ofstream ofile("OUTPUT.TXT");

    if (!ifile) {
        cerr << "Error opening INPUT.TXT!\n";
        return 1;
    }
    if (!ofile) {
        cerr << "Error opening OUTPUT.TXT!\n";
        return 1;
    }

    WordAnalyser wa;
    ifile >> wa;
    ofile << wa;

    return 0;
}