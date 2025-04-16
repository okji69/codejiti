#include <bits/stdc++.h>
using namespace std;

class DSU 
{
    vector<int> p, r;
public:
    DSU(int n) 
    {
        p.resize(n);
        r.resize(n);
        for (int i = 0; i < n; i++) 
        {
            p[i] = i;
            r[i] = 1;
        }
    }
    int find(int i) 
    {
        return (p[i] == i) ? i : (p[i] = find(p[i]));
    }
    void unite(int x, int y) 
    {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (r[s1] < r[s2]) p[s1] = s2;
            else if (r[s1] > r[s2]) p[s2] = s1;
            else p[s2] = s1, r[s1]++;
        }
    }
};

bool cmp(vector<int>& a, vector<int>& b) 
{
    return a[2] <= b[2];
}
int kruskal(int v, vector<vector<int>>& e) 
{
    sort(e.begin(), e.end(), cmp);
    DSU d(v);
    int c = 0, cnt = 0;
    for (auto& i : e) {
        int x = i[0], y = i[1], w = i[2];
        if (d.find(x) != d.find(y)) {
            d.unite(x, y);
            c += w;
            if (++cnt == v - 1) break;
        }
    }
    return c;
}
int main() 
{
    int v, m;
    cin >> v >> m;
    vector<vector<int>> e(m, vector<int>(3));
    for (int i = 0; i < m; i++) {
        cin >> e[i][0] >> e[i][1] >> e[i][2];
    }
    cout << kruskal(v, e);
    return 0;
}
//<------------------------prims--------------------------------->//
// #include <bits/stdc++.h>
// using namespace std;

// int mst(int v, int e, vector<vector<int>>& ed) {
//     vector<vector<int>> adj[v];
//     for (int i = 0; i < e; i++) {
//         int a = ed[i][0], b = ed[i][1], w = ed[i][2];
//         adj[a].push_back({b, w});
//         adj[b].push_back({a, w});
//     }

//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
//     vector<bool> vis(v, false);
//     int sum = 0;
//     pq.push({0, 0});

//     while (!pq.empty()) {
//         auto p = pq.top(); pq.pop();
//         int w = p.first, u = p.second;
//         if (vis[u]) continue;
//         sum += w;
//         vis[u] = true;
//         for (auto x : adj[u])
//             if (!vis[x[0]])
//                 pq.push({x[1], x[0]});
//     }

//     return sum;
// }

// int main() {
//     int v, e;
//     cin >> v >> e;
//     vector<vector<int>> ed(e, vector<int>(3));
//     for (int i = 0; i < e; i++)
//         cin >> ed[i][0] >> ed[i][1] >> ed[i][2];
//     cout << mst(v, e, ed) << endl;
//     return 0;
// }
