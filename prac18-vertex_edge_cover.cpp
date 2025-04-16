#include <bits/stdc++.h>
using namespace std;

set<int> vcGreedy(int n, vector<pair<int, int>> &e) {
    set<int> s;
    vector<bool> v(n, 0);
    for (int i = 0; i < e.size(); i++) {
        int a = e[i].first, b = e[i].second;
        if (!v[a] && !v[b]) {
            s.insert(a);
            s.insert(b);
            v[a] = v[b] = 1;
        }
    }
    return s;
}

bool isVC(int n, vector<pair<int, int>> &e, set<int> &s) {
    for (int i = 0; i < e.size(); i++) {
        int a = e[i].first, b = e[i].second;
        if (s.count(a) == 0 && s.count(b) == 0) return 0;
    }
    return 1;
}

set<int> vcExact(int n, vector<pair<int, int>> &e) {
    int mn = n + 1;
    set<int> best;
    for (int m = 0; m < (1 << n); m++) {
        set<int> cur;
        for (int i = 0; i < n; i++) {
            if (m & (1 << i)) cur.insert(i);
        }
        if (isVC(n, e, cur)) {
            if (cur.size() < mn) {
                mn = cur.size();
                best = cur;
            }
        }
    }
    return best;
}

set<pair<int, int>> edgeCover(int n, vector<pair<int, int>> &e, vector<vector<int>> &adj) {
    vector<bool> vis(n, 0);
    set<pair<int, int>> ec;
    for (int i = 0; i < e.size(); i++) {
        int a = e[i].first, b = e[i].second;
        if (!vis[a] && !vis[b]) {
            ec.insert({a, b});
            vis[a] = vis[b] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i] && !adj[i].empty()) {
            int j = adj[i][0];
            ec.insert({i, j});
            vis[i] = vis[j] = 1;
        }
    }
    return ec;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> e;
    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        e.push_back({a, b});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    set<int> gvc = vcGreedy(n, e);
    cout << "Greedy Vertex Cover: ";
    for (int x : gvc) cout << x << " ";
    cout << endl;

    if (n <= 20) {
        set<int> evc = vcExact(n, e);
        cout << "Exact Vertex Cover: ";
        for (int x : evc) cout << x << " ";
        cout << endl;
    } else {
        cout << "Exact VC skipped (n too large)" << endl;
    }

    set<pair<int, int>> ec = edgeCover(n, e, adj);
    cout << "Edge Cover: ";
    for (pair<int, int> p : ec) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;

    return 0;
}
