#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>
#include <vector>
#include <string>

using namespace std;
#define ADJ_MATRIX vector<vector<int>>

vector<vector<int>> convertToAdjList(string fileName) {
	ifstream inFile(fileName);
	if (inFile.eof()) {
		cout << "File is not found.";
		return{};
	}
	int size = 0;
	inFile >> size;
	vector<vector<int>> adjList(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int value;
			inFile >> value;
			if (value == 1) adjList[i].push_back(j);
		}
	}
	cout << size << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < adjList[i].size(); j++) {
			cout << adjList[i][j] << " ";
		}
		cout << endl;
	}

	inFile.close();
	return adjList;
}

ADJ_MATRIX convertToAdjMatrix(string fileName) {
	ifstream inFile(fileName);
	if (!inFile) {
		cout << "File is not found.";
		return{};
	}

	string content;
	getline(inFile, content);
	int size = stoi(content);

	vector<vector<int>> adjMatrix(size, vector<int>(size, 0));

	for (int i = 0; i < size; i++) {
		getline(inFile, content);
		stringstream stream(content);
		int temp;
		while (stream >> temp) {
			adjMatrix[i][temp] = 1;
		}
	}
	inFile.close();

	cout << size << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
	return adjMatrix;
}

bool isUnDirectGraph(vector<vector<int>> adjMatrix) {
	int size = adjMatrix.size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i] && (adjMatrix[i][j] == 0 || adjMatrix[j][i] == 0))
				return false;
		}
	}
	return true;
}


pair<int, int>countEdgeVertex(vector<vector<int>> adjList) {
	int size = adjList.size();
	vector<bool>visit(size, false);
	int cnt = 0;
	for (int i = 0; i < size; i++) {
		for (int it : adjList[i]) {
			cnt++;
		}
	}
	return{ size,cnt };
}

void DFS(int u, vector<vector<int>>& adjList, vector<bool>& visit) {
	visit[u] = true;
	for (int it : adjList[u]) {
		if (!visit[it]) {
			DFS(it, adjList, visit);
		}
	}
}

int countConnectedComponent(vector<vector<int>>& adjList) {
	int size = adjList.size();
	vector<bool>visit(size, false);
	int cnt = 0;
	for (int i = 0; i < size; i++) {
		if (!visit[i]) {
			cnt++;
			DFS(i, adjList, visit);
		}
	}
	return cnt;
}

int main() {

	//convertToAdjList("graph1.txt");

	/*vector<vector<int>> adjMatrix = convertToAdjMatrix("graph2.txt");
	if (isUnDirectGraph(adjMatrix))
		cout << "Undirected Graph";
	else cout << "Directed Graph";*/

	vector<vector<int>>adjList= convertToAdjList("graph1.txt");
	pair<int, int>res = countEdgeVertex(adjList);
	cout << res.first << " " << res.second << endl;
	return 0;
}