#include <bits/stdc++.h>
using namespace std;

bool isSafe(int u, vector<int> &c, vector<vector<int>> &g, int clr) {
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (c[v] == clr) return false;
    }
    return true;
}

bool colorGraph(int u, vector<vector<int>> &g, vector<int> &c, int n, int m) 
{
    if (u == n) return true;

    for (int clr = 1; clr <= m; clr++) 
    {
        if (isSafe(u, c, g, clr)) 
        {
            c[u] = clr;
            if (colorGraph(u + 1, g, c, n, m)) return true;
            c[u] = 0;
        }
    }

    return false;
}

int main() {
    int n, e;
    cin >> n >> e;
    vector<vector<int>> g(n);
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> c(n, 0);
    int m = 4; // Four colors

    bool ok = colorGraph(0, g, c, n, m);

    if (!ok) {
        cout << "Cannot color with 4 colors" << endl;
    } else {
        for (int i = 0; i < n; i++) {
            cout << "Node " << i << " -> Color " << c[i] << endl;
        }
    }
    return 0;
}
