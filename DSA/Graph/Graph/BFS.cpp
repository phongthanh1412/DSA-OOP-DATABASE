#include <iostream>
#include <vector>
#include <queue>
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

void BFS_visit(vector<vector<int>>& adj, vector<bool>& visited, int vertice) {
    queue<int>q;
    visited[vertice] = true;
    q.push(vertice);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << cur << " ";
        for (int i = 0; i < adj[cur].size(); i++) {
            int next_vertice = adj[cur][i];
            if (!visited[next_vertice]) {
                visited[next_vertice] = true;
                q.push(next_vertice);
            }
        }
    }
}

void BFS(vector<vector<int>>& adj, int vertice) {
    int size = adj.size();
    vector<bool> visited(size, false);
    BFS_visit(adj, visited, vertice);
}

int main() {
    int vertices = 0, edges = 0;
    cin >> vertices >> edges;
    vector<vector<int>> adj(101);
    addEdge(adj, vertices, edges);
    BFS(adj, 1);

    return 0;
}

