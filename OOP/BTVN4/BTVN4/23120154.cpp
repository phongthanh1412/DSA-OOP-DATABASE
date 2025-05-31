//
// Template for Homework 4 - Single-Source Shortest Path.
//
// Description:
// In this homework, you're asked to implement Dijkstra's Algorithm to find the
// Shortest Path between a pair of vertices in an directed/undirected graph.
//
// Grading:
// We'll test your code on several testcases, all would be load from input files
// (of course, we've implemented the pipeline for you).
//
// Input:
// The input file would follow this format:
//
// 3
// 0 2 1
// 2 0 1
// 1 1 0
// 0 1
//
// where
// - 1st line: an integer n -- total vertices in the graph.
// - Next n lines, each line consists of n integers.
//   (Please have a look at the definition of adjacency matrix in
//   undirected graphs.)
// - Last line: a pair of integers u and v -- the starting and ending vertices
// of the path.
//
//
// Example: input_sample.txt
//
// Instructions:
// 1. Fill your code inside <// TODO: YOUR CODE HERE> zone.
// 2. You should NOT modify code inside <// DO NOT MODIFY CODE INSIDE THIS ZONE>
//    to prevent your code getting wrong answer from grader.
// 3. You can add additional functions to support your implementation,
//    but don't modify given prototypes.
// 4. You can modify the main() function to test your code,
//    but remember to restore it to the original version after finished.
//    We test your code with the original main() function, any modification
//    can results in your code getting wrong answer.
//
// Have fun!
// Last updated: Dec 19, 2024.
//

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

// Predefined prototypes

/**
 * @brief Read a given graph's adjacency matrix from stdin (i.e. using cin).
 *
 * @param n total vertices of the graph.
 * @return vector<vector<int>> The adjacency matrix of the given graph.
 */
ADJ_MATRIX readAdjacencyMatrix(int&);

/**
 * @brief Dijkstra's algorithm to find the Shortest Path between a pair of
 * vertices.
 *
 * @param matrix the adjacency matrix of the graph.
 * @param start the starting vertex.
 * @param end the target vertex.
 * @param trace saving traveled vertices.
 * @return int minimum length of the path.
 */
int Dijkstra(const ADJ_MATRIX&, int, int, vector<int>&);

// ------------------------------------------------
// DO NOT MODIFY CODE INSIDE THIS ZONE

/**
 * @brief Print a given trace vector.
 *
 * @param end the ending vertex of the path.
 * @param trace Given trace vector.
 */
void printTrace(int end, const vector<int>& trace) {
    stack<int> s;
    s.push(end);

    int current = end;
    while (trace[current] != -1) {
        s.push(trace[current]);
        current = trace[current];
    }

    while (s.size() > 1) {
        cout << s.top() << " -> ";
        s.pop();
    }

    cout << s.top();
}

// ------------------------------------------------

ADJ_MATRIX readAdjacencyMatrix(int& n) {
    // TODO: YOUR CODE HERE.
    cin >> n;
    ADJ_MATRIX matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

// This function returns
//      int - the shortest path's lenght between start and end.
//      trace - the shortest path i.e. vertices in the shortest path in their
//      correct orders.
//
// How-to-use vector<int> trace:
// If an edge v is traveled from u, then trace[v] = u.
int Dijkstra(const ADJ_MATRIX& matrix, int start, int end, vector<int>& trace) {
    // TODO: YOUR CODE HERE
    int n = matrix.size();
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    trace.assign(n, -1);

    dist[start] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (matrix[u][v] > 0 && !visited[v] && dist[v] > dist[u] + matrix[u][v]) {
                dist[v] = dist[u] + matrix[u][v];
                trace[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    return dist[end];
}

// ------------------------------------------------

int main() {
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);

    int n;  // n = total vertices of the given graph.
    ADJ_MATRIX graph = readAdjacencyMatrix(n);

    // Starting vertex of the Prim's algorithm.
    int start, end;
    cin >> start >> end;

    // Make sure that you've read the matrix successfully.
    assert(graph.size() == n);
    assert(graph[0].size() == n);

    vector<int> trace(n, -1);
    int minPathLength = Dijkstra(graph, start, end, trace);

    // Finding shortest path
    cout << "Shortest path's length: " << minPathLength << "\n";
    cout << "Trace: " << "\n";
    printTrace(end, trace);

    return 0;
}