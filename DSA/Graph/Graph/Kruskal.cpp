#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
	int source, target, weight;
};

struct disjointSet {

	int parent[1001];
	int rank[1001];

	void create_set(int size) {
		for (int i = 0; i < size; i++) {
			parent[i] = i;
			rank[i] = 1;
		}
	}

	int find(int vertice) {
		if (vertice == parent[vertice]) return vertice;
		return parent[vertice] = find(parent[vertice]);  
	}

	void unionByRank(int a, int b) {
		a = find(a);
		b = find(b);
		if (a != b) {
			if (rank[a] > rank[b]) parent[b] = a;
			else if (rank[a] < rank[b]) parent[a] = b;
			else {
				parent[a] = b;
				rank[b]++;  
			}
		}
	}
};

vector<edge> addEdges(int& vertices, int& edges) {
	vector<edge> myEdges;
	cin >> vertices >> edges;
	for (int i = 0; i < edges; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		myEdges.push_back({ a, b, w });
	}
	return myEdges;
}

bool compare(edge edge1, edge edge2) {
	return edge1.weight < edge2.weight;
}

void KruskalMST(disjointSet& mySet, vector<edge>& myEdges, int vertices, int edges) {
	vector<edge> MST;
	int mst_wt = 0;
	sort(myEdges.begin(), myEdges.end(), compare);

	for (int i = 0; i < edges; i++) {
		if (MST.size() == vertices - 1) break;
		edge e = myEdges[i];
		int setU = mySet.find(e.source);
		int setV = mySet.find(e.target);
		if (setU != setV) {
			mySet.unionByRank(setU, setV);
			MST.push_back(e);
			mst_wt += e.weight;
		}
	}
	if (MST.size() != vertices - 1)
		cout << "No connected graph exists!";
	else {
		cout << "Minimum Spanning Tree weight: " << mst_wt << endl;
		for (int i = 0; i < MST.size(); i++)
			cout << MST[i].source << "-" << MST[i].target << endl;
	}
}

int main() {
	disjointSet mySet;
	int vertices = 0, edges = 0;
	vector<edge> myEdges = addEdges(vertices, edges);
	mySet.create_set(vertices);  
	KruskalMST(mySet, myEdges, vertices, edges);
	return 0;
}
