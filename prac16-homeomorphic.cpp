#include <bits/stdc++.h>
using namespace std;

void reduce(vector<vector<int>>& g) {
    int n = g.size();
    vector<int> d(n, 0);
    for (int i = 0; i < n; i++) d[i] = g[i].size();

    while (true) {
        bool ch = false;
        for (int i = 0; i < n; i++) {
            if (d[i] == 2) {
                vector<int> nb;
                for (int v : g[i]) nb.push_back(v);
                int u = nb[0], v = nb[1];

                g[u].erase(remove(g[u].begin(), g[u].end(), i), g[u].end());
                g[v].erase(remove(g[v].begin(), g[v].end(), i), g[v].end());

                if (find(g[u].begin(), g[u].end(), v) == g[u].end()) g[u].push_back(v);
                if (find(g[v].begin(), g[v].end(), u) == g[v].end()) g[v].push_back(u);

                g[i].clear();
                d[i] = 0;
                ch = true;
            }
        }
        if (!ch) break;
    }
}

set<multiset<int>> sig(vector<vector<int>>& g) {
    set<multiset<int>> s;
    for (int i = 0; i < g.size(); i++) {
        if (!g[i].empty()) {
            multiset<int> tmp;
            for (int j : g[i]) tmp.insert(g[j].size());
            s.insert(tmp);
        }
    }
    return s;
}

int main() {
    int n1, m1;
    cin >> n1 >> m1;
    vector<vector<int>> g1(n1);
    for (int i = 0; i < m1; i++) {
        int a, b;
        cin >> a >> b;
        g1[a].push_back(b);
        g1[b].push_back(a);
    }

    int n2, m2;
    cin >> n2 >> m2;
    vector<vector<int>> g2(n2);
    for (int i = 0; i < m2; i++) {
        int a, b;
        cin >> a >> b;
        g2[a].push_back(b);
        g2[b].push_back(a);
    }

    reduce(g1);
    reduce(g2);

    set<multiset<int>> s1 = sig(g1);
    set<multiset<int>> s2 = sig(g2);

    if (s1 == s2) cout << "Graphs are homomorphic\n";
    else cout << "Graphs are not homomorphic\n";

    return 0;
}
