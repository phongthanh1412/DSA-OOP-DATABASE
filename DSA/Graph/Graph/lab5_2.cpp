#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// Hàm đọc danh sách kề từ file và chuyển thành ma trận kề
void convertFileToAdjMatrix(const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cout << "Không thể mở file!" << endl;
        return;
    }

    vector<vector<int>> adjList; // Lưu danh sách kề
    string line;

    // Đọc từng dòng trong file và chuyển thành danh sách kề
    while (getline(inFile, line)) {
        istringstream iss(line); // Tạo istringstream để đọc số từ dòng
        vector<int> neighbors;
        int vertex;

        while (iss >> vertex) { // Đọc từng số trong dòng
            neighbors.push_back(vertex - 1); // Giảm chỉ số để bắt đầu từ 0
        }
        adjList.push_back(neighbors);
    }
    inFile.close();

    // Xác định số đỉnh
    int size = adjList.size();

    // Tạo và khởi tạo ma trận kề
    vector<vector<int>> adjMatrix(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j : adjList[i]) {
            adjMatrix[i][j] = 1;
        }
    }

    // In ra ma trận kề
    cout << "Ma trận kề tương ứng là:\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    string fileName = "graph2.txt"; // Tên file input
    convertFileToAdjMatrix(fileName);
    return 0;
}
