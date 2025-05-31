#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Hàm đọc dữ liệu từ file và tạo danh sách kề
void readDataAndCreateAdjList(const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cout << "Không thể mở file!" << endl;
        return;
    }

    int size = 0;
    inFile >> size; // Đọc kích thước ma trận kề

    vector<vector<int>> adjList(size); // Danh sách kề

    // Đọc ma trận kề và chuyển đổi thành danh sách kề
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int value;
            inFile >> value;
            if (value == 1) {
                adjList[i].push_back(j); // Không cộng thêm 1 vào chỉ số
            }
        }
    }
    inFile.close();

    // In danh sách kề theo định dạng yêu cầu
    for (int i = 0; i < size; i++) {
        cout << i + 1 << " --> ";
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    string fileName = "graph1.txt"; // Tên tệp dữ liệu
    readDataAndCreateAdjList(fileName);
    return 0;
}
