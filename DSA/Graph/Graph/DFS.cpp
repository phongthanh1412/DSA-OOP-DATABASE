#include <iostream>
#include <vector>
using namespace std;

void addEdge(vector<vector<int>>& adj, int vertices, int edges) {
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    for (int i = 1; i <= vertices; i++) {
        cout << i << " --> ";
        for (int j = 0; j < adj[i].size(); j++)
            cout << adj[i][j] << " ";
        cout << endl;
    }
}

void DFS_visit(vector<vector<int>>& adj, vector<bool>& visited, int vertice) {
    visited[vertice] = true;
    cout << vertice << " ";
    for (int i = 0; i < adj[vertice].size(); i++) {
        int next_vertice = adj[vertice][i];
        if (!visited[next_vertice]) {
            DFS_visit(adj, visited, next_vertice);
        }
    }
}

void DFS(vector<vector<int>>& adj, int vertice) {
    int size = adj.size();
    vector<bool> visited(size, false);
    DFS_visit(adj, visited, vertice);
}

int main() {
    int vertices = 0, edges = 0;
    cin >> vertices >> edges;
    vector<vector<int>> adj(101);
    addEdge(adj, vertices, edges);
    DFS(adj, 1);

    return 0;
}
