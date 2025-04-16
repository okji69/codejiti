#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int V, E;
vector<vector<int>> graph;

// ---------- For Eulerian Check ----------
bool isConnectedUtil(int v, vector<bool> &visited) {
    visited[v] = true;
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && !visited[i])
            isConnectedUtil(i, visited);
    }
    return true;
}

bool isConnected() {
    vector<bool> visited(V, false);

    // Find a vertex with a non-zero degree
    int start = -1;
    for (int i = 0; i < V; i++) {
        int degree = 0;
        for (int j = 0; j < V; j++)
            degree += graph[i][j];
        if (degree > 0) {
            start = i;
            break;
        }
    }

    if (start == -1)
        return true; // No edges

    isConnectedUtil(start, visited);

    for (int i = 0; i < V; i++) {
        int degree = 0;
        for (int j = 0; j < V; j++)
            degree += graph[i][j];
        if (degree > 0 && !visited[i])
            return false;
    }

    return true;
}

bool isEulerian() 
{
    if (!isConnected())
        return false;

    int odd = 0;
    for (int i = 0; i < V; i++) {
        int degree = 0;
        for (int j = 0; j < V; j++)
            degree += graph[i][j];
        if (degree % 2 != 0)
            odd++;
    }
    return (odd == 0); 
}

bool isHamiltonianUtil(vector<bool> &visited, vector<int> &path, int pos) 
{
    if (pos == V) {
        return graph[path[pos - 1]][path[0]] == 1; 
    }

    for (int v = 1; v < V; v++) {
        if (graph[path[pos - 1]][v] && !visited[v]) 
        {
            visited[v] = true;
            path[pos] = v;

            if (isHamiltonianUtil(visited, path, pos + 1))
                return true;

            visited[v] = false;
        }
    }

    return false;
}

bool isHamiltonian() {
    vector<int> path(V, -1);
    vector<bool> visited(V, false);

    path[0] = 0;
    visited[0] = true;

    return isHamiltonianUtil(visited, path, 1);
}

// ---------- Main ----------
int main() {
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    graph.assign(V, vector<int>(V, 0));

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1; // Undirected graph
    }

    if (isEulerian())
        cout << "Graph is Eulerian." << endl;
    else
        cout << "Graph is NOT Eulerian." << endl;

    if (isHamiltonian())
        cout << "Graph is Hamiltonian." << endl;
    else
        cout << "Graph is NOT Hamiltonian." << endl;

    return 0;
}