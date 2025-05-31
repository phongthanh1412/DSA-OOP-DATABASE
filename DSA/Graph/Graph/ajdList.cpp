#include<iostream>
#include<vector>
using namespace std;

void createAjdList(int vertices, int edges) {
	vector<int>list[101];
	for (int i = 0; i < edges; i++) {
		int u, v;
		cin >> u >> v;
		list[u].push_back(v);
		list[v].push_back(u);
	}

	for (int i = 1; i <= vertices; i++) {
		cout << i << " --> ";
		for (int j = 0; j < list[i].size(); j++)
			cout << list[i][j] << " ";
		cout << endl;
	}

}

int main() {
	int vertices = 0, edges = 0;
	cin >> vertices >> edges;
	createAjdList(vertices, edges);

	return 0;
}