#include <cassert>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>

using namespace std;
#define ADJ_MATRIX vector<vector<int>>
#define EDGES_LIST map<pair<int, int>, int>
#define ii pair<int, int>
#define INF 1e9

void printEdgesList(const EDGES_LIST &l)
{
    for (const auto &i : l)
    {
        pair<int, int> edge = i.first;
        cout << "( " << edge.first << ", " << edge.second << ") = " << i.second
             << "\n";
    }
}

ADJ_MATRIX readAdjacencyMatrix(int &n)
{
    cin >> n;
    ADJ_MATRIX graph(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }
    return graph;
}

EDGES_LIST Prim(const ADJ_MATRIX &graph, int startVertex)
{
    int size = graph.size();
    vector<bool> visit(size, false);
    vector<int> dist(size, INF);
    vector<int> trace(size, -1);
    EDGES_LIST edges;
    priority_queue<ii, vector<ii>, greater<ii>> pq;

    dist[startVertex] = 0;
    pq.push({0, startVertex});
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (visit[u])
            continue;
        visit[u] = true;
        if (trace[u] != -1)
            edges[{trace[u], u}] = dist[u];

        for (int v = 0; v < size; v++)
        {
            if (graph[u][v] > 0 && !visit[v] && graph[u][v] < dist[v])
            {
                dist[v] = graph[u][v];
                trace[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return edges;
}
int main()
{
    freopen("prim.txt", "r+", stdin);
    freopen("output_prim.txt", "w+", stdout);
    int n;  // n = total vertices of the given graph.
    ADJ_MATRIX graph = readAdjacencyMatrix(n);

    // Starting vertex of the Prim's algorithm.
    int k;
    cin >> k;

    EDGES_LIST el = Prim(graph, k);

    cout << "MST found with Prim's algorithm:\n";
    printEdgesList(el);

    return 0;
}
