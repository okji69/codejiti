#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    // 1. Adjacency Matrix
    vector<vector<int>> am(n, vector<int>(n, 0));
    cout << "Enter edges (u v) for adjacency matrix: ";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        am[u][v] = 1;
        am[v][u] = 1;
    }

    // Add edge example
    am[0][1] = 1;
    am[1][0] = 1;

    // Remove edge example
    am[0][1] = 0;
    am[1][0] = 0;

    // 2. Adjacency List
    vector<vector<int>> al(n);
    cout << "Enter edges (u v) for adjacency list: ";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        al[u].push_back(v);
        al[v].push_back(u);
    }

    // Add edge
    al[0].push_back(1);
    al[1].push_back(0);

    // Remove edge
    for (int i = 0; i < al[0].size(); i++) {
        if (al[0][i] == 1) {
            al[0].erase(al[0].begin() + i);
            break;
        }
    }
    for (int i = 0; i < al[1].size(); i++) {
        if (al[1][i] == 0) {
            al[1].erase(al[1].begin() + i);
            break;
        }
    }

    // 3. Incidence Matrix
    vector<vector<int>> im(n, vector<int>(m, 0));
    vector<pair<int, int>> edg;
    cout << "Enter edges (u v) for incidence matrix: ";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edg.push_back({u, v});
        im[u][i] = 1;
        im[v][i] = 1;
    }

    // Add edge (new column)
    int u = 0, v = 1;
    edg.push_back({u, v});
    for (int i = 0; i < n; i++) {
        im[i].push_back(0);
    }
    im[u][m] = 1;
    im[v][m] = 1;

    // Remove edge
    for (int i = 0; i < edg.size(); i++) {
        if ((edg[i].first == u && edg[i].second == v) || (edg[i].first == v && edg[i].second == u)) {
            for (int j = 0; j < n; j++) {
                im[j].erase(im[j].begin() + i);
            }
            edg.erase(edg.begin() + i);
            break;
        }
    }

    // Memory usage estimates
    int am_mem = n * n * sizeof(int);
    int al_mem = 0;
    for (int i = 0; i < al.size(); i++) {
        al_mem += al[i].size() * sizeof(int);
    }
    int im_mem = n * edg.size() * sizeof(int);

    cout << "Memory (Adjacency Matrix): " << am_mem << " bytes" << endl;
    cout << "Memory (Adjacency List):   " << al_mem << " bytes (approx)" << endl;
    cout << "Memory (Incidence Matrix): " << im_mem << " bytes" << endl;

    return 0;
}
