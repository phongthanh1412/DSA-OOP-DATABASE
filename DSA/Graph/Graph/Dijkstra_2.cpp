#include <cassert>
#include <climits>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

#define ADJ_MATRIX vector<vector<int>>
#define INF 1e9
#define ii pair<int, int>

void printTrace(int end, const vector<int> &trace)
{
    stack<int> s;
    s.push(end);

    int current = end;
    while (trace[current] != -1)
    {
        s.push(trace[current]);
        current = trace[current];
    }

    while (s.size() > 1)
    {
        cout << s.top() << " -> ";
        s.pop();
    }

    cout << s.top();
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

int Dijkstra(const ADJ_MATRIX &matrix, int start, int end, vector<int> &trace)
{
    int size = matrix.size();
    vector<bool> visit(size, false);
    vector<int> dist(size, INF);
    trace.assign(size, -1);
    priority_queue<ii, vector<ii>, greater<ii>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (visit[u])
            continue;
        visit[u] = true;

        for (int v = 0; v < size; v++)
        {
            if (matrix[u][v] > 0 && !visit[v] && matrix[u][v] + dist[u] < dist[v])
            {
                dist[v] = matrix[u][v] + dist[u];
                trace[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[end];
}

int main()
{
    freopen("dijkstra.txt", "r+", stdin);
    freopen("output_dijkstra.txt", "w+", stdout);

    int n; // n = total vertices of the given graph.
    ADJ_MATRIX graph = readAdjacencyMatrix(n);

    // Starting vertex of the Prim's algorithm.
    int start, end;
    cin >> start >> end;

    vector<int> trace(n, -1);
    int minPathLength = Dijkstra(graph, start, end, trace);

    // Finding shortest path
    cout << "Shortest path's length: " << minPathLength << "\n";
    cout << "Trace: " << "\n";
    printTrace(end, trace);

    return 0;
}