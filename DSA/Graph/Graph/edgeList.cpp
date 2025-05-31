#include<iostream>
#include<vector>
#include<utility>
using namespace std;

void createEdgeList(int mat[][10], int size) {

	vector<pair<int, int>>edges;
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
			cin >> mat[i][j];

	for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
			if (mat[i][j] == 1 && i < j)
				edges.push_back({ i, j });
		}
	}

	for (auto it : edges)
		cout << it.first << " " << it.second << endl;

}

int main() {
	int size = 0;
	cin >> size;
	int mat[10][10];
	createEdgeList(mat, size);

	return 0;
}