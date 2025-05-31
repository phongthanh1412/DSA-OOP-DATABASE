//
// Template for Homework 3 - MST.
//
// Description:
// In this homework, you're asked to implement Prim's Algorithm to find the Minimum Spanning Tree (MST)
// of an undirected graph.
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
// 1
//
// where
// - 1st line: an integer n -- total vertices in the graph.
// - Next n lines, each line consists of n integers.
//   (Please have a look at the definition of adjacency matrix in
//   undirected graphs.)
// - Last line: an integer k -- starting vertex of the Prim's algorithm
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
// Last updated: Jul 24, 2024.
//

#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;
#define INF INT_MAX
#define ii pair<int, int>
#define ADJ_MATRIX vector<vector<int>>

// Note that we're using map<pair<int, int>, int> to represent an edges list,
// yet it's still somehow inefficient with O(log) for insertion & lookup.
#define EDGES_LIST map<pair<int, int>, int>

// Predefined prototypes

/**
 * @brief Read a given graph's adjacency matrix from stdin (i.e. using cin).
 *
 * @param n total vertices of the graph.
 * @return vector<vector<int>> The adjacency matrix of the given graph.
 */
ADJ_MATRIX readAdjacencyMatrix(int&);

/**
 * @brief Minimum Spanning Tree with Prim's Algorithm
 *
 * @param graph Given adjacency matrix of a graph.
 * @param startVertex Starting vertex.
 *
 * @return List of edges.
 */
EDGES_LIST Prim(const ADJ_MATRIX&, int);

// ------------------------------------------------
// DO NOT MODIFY CODE INSIDE THIS ZONE

/**
 * @brief Print a given Edges List.
 *
 * @param l Given edges list.
 */
void printEdgesList(const EDGES_LIST& l) {
    for (const auto& i : l) {
        pair<int, int> edge = i.first;
        cout << "( " << edge.first << ", " << edge.second << ") = " << i.second
            << "\n";
    }
}

// ------------------------------------------------

ADJ_MATRIX readAdjacencyMatrix(int& n) {
    // TODO: YOUR CODE HERE.
    cin >> n;
    ADJ_MATRIX matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

// Note: to insert an edge of (u, v) = w where
// - u = first vertex
// - v = second vertex
// - w = the edge's weight
// - EDGES_LIST l
// Therefore l[{u, v}] = w;
EDGES_LIST Prim(const ADJ_MATRIX& graph, int startVertex) {
    // TODO: YOUR CODE HERE.
    int n = graph.size();
    vector<int> dist(n, INF);
    vector<bool> visit(n, false);
    vector<int> parent(n, -1);

    priority_queue<ii, vector<ii>, greater<ii>> pq;
    dist[startVertex] = 0;
    pq.push({ 0, startVertex });

    EDGES_LIST edges;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visit[u]) continue;
        visit[u] = true;

        if (parent[u] != -1) {
            edges[{parent[u], u}] = dist[u];
        }

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] && !visit[v] && graph[u][v] < dist[v]) {
                dist[v] = graph[u][v];
                parent[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    return edges;
}

// ------------------------------------------------

int main() {
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);

    int n;  // n = total vertices of the given graph.
    ADJ_MATRIX graph = readAdjacencyMatrix(n);

    // Starting vertex of the Prim's algorithm.
    int k;
    cin >> k;

    // Make sure that you've read the matrix successfully.
    assert(graph.size() == n);
    assert(graph[0].size() == n);

    EDGES_LIST el = Prim(graph, k);

    // Total edges in MST = n - 1;
    assert(el.size() == n - 1);
    cout << "MST found with Prim's algorithm:\n";
    printEdgesList(el);

    return 0;
}