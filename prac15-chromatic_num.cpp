#include <bits/stdc++.h>
#define pb push_back
#define ll long long
#define int long long int
#define all(v) v.begin(), v.end()
using namespace std;

vector<vector<int>> adj;
vector<int> color;

bool isSafe(int node, int c)
{
    for (int neighbor : adj[node])
    {
        if (color[neighbor] == c)
            return false;
    }
    return true;
}

bool coloring(int node, int m, int n)
{
    if (node == n)
        return true;
    for (int c = 1; c <= m; c++)
    {
        if (isSafe(node, c))
        {
            color[node] = c;
            if (coloring(node + 1, m, n))
                return true;
            color[node] = 0;
        }
    }
    return false;
}

bool GraphColor(int m, vector<pair<int, int>> &edges, int n)
{
    adj.assign(n, vector<int>());
    color.assign(n, 0);

    for (auto it : edges)
    {
        int u = it.first, v = it.second;
        adj[u - 1].pb(v - 1);
        adj[v - 1].pb(u - 1);
    }
    return coloring(0, m, n);
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].first >> edges[i].second;
    }

    int lo = 1, hi = n, ans = n;
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        if (GraphColor(mid, edges, n))
        {
            ans = mid;
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }
    cout << ans << endl;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}
