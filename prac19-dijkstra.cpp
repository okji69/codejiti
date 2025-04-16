#include <bits/stdc++.h>
using namespace std;

int networkTime(int n, vector<vector<int>> &t, int k) {
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < t.size(); i++) {
        int u = t[i][0], v = t[i][1], w = t[i][2];
        g[u].push_back({v, w});
    }

    vector<int> d(n + 1, 1e9);
    d[k] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k});

    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();
        int wt = p.first, u = p.second;

        if (wt > d[u]) continue;

        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first, w = g[u][i].second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                pq.push({d[v], v});
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (d[i] == 1e9) return -1;
        res = max(res, d[i]);
    }

    return res;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> t;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        t.push_back({u, v, w});
    }

    int ans = networkTime(n, t, k);
    cout << ans << endl;

    return 0;
}
