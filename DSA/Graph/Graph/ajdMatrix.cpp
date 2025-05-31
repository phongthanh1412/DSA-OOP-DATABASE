#include<iostream>
using namespace std;

void createAjdMatrix(int**& mat, int vertices, int edges) {
	//initialize matrix
	mat = new int* [vertices + 1];
	for (int i = 0; i < vertices + 1; i++) {
		mat[i] = new int[vertices + 1];
		for (int j = 0; j < vertices + 1; j++)
			mat[i][j] = 0;
	}
	// add edges
	for (int i = 0; i < edges; i++) {
		int u, v;
		cin >> u >> v;
		mat[u][v] = 1;
		mat[v][u] = 1;
	}
	// show matrix
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++)
			cout << mat[i][j] << " ";
		cout << endl;
	}
}

void Free(int** mat, int matSize) {
	for (int i = 0; i < matSize + 1; i++)
		delete[]mat[i];
	delete[]mat;
}
int main() {
	int vertices = 0, edges = 0;
	cin >> vertices >> edges;
	int** mat = NULL;
	createAjdMatrix(mat, vertices, edges);

	Free(mat, vertices);
	return 0;
}