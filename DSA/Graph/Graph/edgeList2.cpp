#include<iostream>
#include<vector>
#include<utility>
using namespace std;

void createEdgeList(int mat[][10], int size) {

	vector<int>adj[101];
	vector<pair<int, int>>edges;
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
			cin >> mat[i][j];

	for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
			if (mat[i][j])
				adj[i].push_back(j);
		}
	}

	for (int i = 1; i <= size; i++) {
		cout << i << " --> ";
		for (int j = 0; j < adj[i].size(); j++)
			cout << adj[i][j] << " ";
		cout << endl;
	}

}

int main() {
	int size = 0;
	cin >> size;
	int mat[10][10];
	createEdgeList(mat, size);

	return 0;
}