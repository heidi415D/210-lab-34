#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

const int SIZE = 11;

vector<string> airportNames = {
    "San Francisco International (SFO)",
    "Seattle-Tacoma Airport (SEA)",
    "Denver International (DEN)",
    "Phoenix Sky Harbor (PHX)",
    "Salt Lake City Airport (SLC)",
    "Dallas Fort-Worth (DFW)",
    "Chicago O'Hare (ORD)",
    "Atlanta Hartsfield-Jackson (ATL)",
    "Miami International (MIA)",
    "Honolulu International (HNL)",
    "Anchorage Airport (ANC)"
};


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
    cout << "Airline Route Network:\n";
    cout << "=======================\n";

    for (int i = 0; i < adjList.size(); i++) {
        cout << airportNames[i] << " has direct flights to:\n";
        for (Pair v : adjList[i]) {
            cout << "  → " << airportNames[v.first]
                 << " (Flight Time: " << v.second << " mins)\n";
        }
        cout << endl;
    }
}

    

    void dfsUtil(int v, vector<bool> &visited) {
    visited[v] = true;

    cout << "Inspecting " << airportNames[v] << endl;

    for (auto &edge : adjList[v]) {
        int neighbor = edge.first;
        if (!visited[neighbor]) {
            cout << "  → Traveling to " << airportNames[neighbor]
                 << " (" << edge.second << " mins)\n";
            dfsUtil(neighbor, visited);
        }
    }
}

void DFS(int start) {
    vector<bool> visited(SIZE, false);
    cout << "Airline Maintenance Inspection Route (DFS)\n";
    cout << "Starting at: " << airportNames[start] << "\n";
    cout << "-------------------------------------------\n";
    dfsUtil(start, visited);
    cout << endl;
}


   void BFS(int start) {
    vector<bool> visited(SIZE, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Checking reachable airports (BFS)\n";
    cout << "Starting at: " << airportNames[start] << "\n";
    cout << "-------------------------------------------\n";

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        cout << "Now checking: " << airportNames[v] << endl;

        for (auto &edge : adjList[v]) {
            int neighbor = edge.first;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                cout << "  → Adding connecting flight to "
                     << airportNames[neighbor]
                     << " (" << edge.second << " mins)\n";
                q.push(neighbor);
            }
        }
        cout << endl;
    }
}
void shortestPathsFrom(int start) {
    vector<int> dist(SIZE, INT_MAX);
    dist[start] = 0;

    // min-heap storing (distance, node)
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        if (currentDist > dist[u]) continue;

        for (auto &edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nShortest Flight Times from "
         << airportNames[start] << ":\n";
    cout << "--------------------------------------\n";

    for (int i = 0; i < SIZE; i++) {
        cout << airportNames[start] << " → "
             << airportNames[i] << " : ";

        if (dist[i] == INT_MAX)
            cout << "unreachable\n";
        else
            cout << dist[i] << " mins\n";
    }
}

void minimumSpanningTree() {
    vector<bool> inMST(SIZE, false);
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

    // (weight, node, parent)
    vector<int> parent(SIZE, -1);
    vector<int> key(SIZE, INT_MAX);

    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        // Look at all neighbors of u
        for (auto &edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "\nMinimum Spanning Tree (MST):\n";
    cout << "--------------------------------------\n";

    for (int i = 1; i < SIZE; i++) {
        if (parent[i] != -1) {
            cout << airportNames[parent[i]] << " → "
                 << airportNames[i] << "  ("
                 << key[i] << " mins)\n";
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
    
    g.shortestPathsFrom(0);
    g.minimumSpanningTree();


}