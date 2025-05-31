#include <cassert>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

#define ii pair<int, int>
#define ADJ_MATRIX vector<vector<int>>
#define EDGES_LIST map<pair<int, int>, int>
#define ii pair<int, int>

void printEdgesList(const vector<ii> &spanningTree)
{
    for (const auto &edge : spanningTree)
    {
        cout << edge.first << " - " << edge.second << "\n";
    }
}

ADJ_MATRIX readAdjacencyMatrix(int &n)
{
    cin >> n;
    ADJ_MATRIX matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> matrix[i][j];
    return matrix;
}

void BFS(const ADJ_MATRIX &graph, vector<ii> &spanningTree, vector<bool> &visit, int startVertex)
{
    visit[startVertex] = true;
    queue<int> q;
    q.push(startVertex);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < graph[u].size(); v++)
        {
            if (graph[u][v] > 0 && !visit[v])
            {
                spanningTree.push_back({u, v});
                visit[v]=true;
                q.push(v);
            }
        }
    }
}

vector<ii> findSpanningTree(const ADJ_MATRIX &graph, int startVertex)
{
    int size = graph.size();
    vector<bool> visit(size, false);
    vector<ii> spanningTree;
    BFS(graph, spanningTree, visit, startVertex);
    return spanningTree;
}
int main()
{
    freopen("BFS.txt", "r+", stdin);
    // freopen("output_BFS.txt", "w+", stdout);

    int n; // n = total vertices of the given graph.
    ADJ_MATRIX graph = readAdjacencyMatrix(n);

    // Starting vertex of the Prim's algorithm.
    int k;
    cin >> k;

    vector<ii> el = findSpanningTree(graph, k);

    cout << "ST found with BFS's algorithm:\n";
    printEdgesList(el);

    return 0;
}