#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define INF 1e9

void createAdj(vector<pair<int, int>> adj[], int vertices, int edges) {
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }
}

void dijkstra(vector<pair<int, int>> adj[], int vertices, int src) {
    vector<int> dis(vertices, INF);
    dis[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, src });

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();
        int u = top.second;
        for (auto i : adj[u]) {
            int v = i.first;
            int w = i.second;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push({ dis[v], v });
            }
        }
    }

    for (int i = 0; i < vertices; i++) {
        cout << dis[i] << " ";
    }
    cout << endl;
}

int main() {
    int vertices, edges, src;
    cin >> vertices >> edges >> src;

    vector<pair<int, int>> adj[101];
    createAdj(adj, vertices, edges);
    dijkstra(adj, vertices, src);

    return 0;
}
