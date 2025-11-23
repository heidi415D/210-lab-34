#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 11;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // DFS helper
    void dfsUtil(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto &edge : adjList[v]) {
            int neighbor = edge.first;
            if (!visited[neighbor])
                dfsUtil(neighbor, visited);
        }
    }

    // Public DFS
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        cout << "DFS starting from vertex " << start << ":\n";
        dfsUtil(start, visited);
        cout << endl;
    }

    // BFS
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":\n";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto &edge : adjList[v]) {
                int neighbor = edge.first;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    vector<Edge> edges = {
    {0,1,8}, {0,2,21},
    {1,2,6}, {1,3,5}, {1,4,4},
    {2,7,11}, {2,8,8},
    {3,4,9},
    {5,6,10}, {5,7,15}, {5,8,5},
    {6,7,3}, {6,8,7},
    {9,10,4}
    };

    Graph g(edges);

    g.printGraph();
    cout << endl;

    g.DFS(0);
    g.BFS(0);
    return 0;
}