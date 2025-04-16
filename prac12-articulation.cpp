#include <bits/stdc++.h>
#define erase(a) a.erase(unique(a.begin(), a.end()), a.end())
#define pb push_back
#define ll long long
#define int long long int
#define all(v) v.begin(), v.end()
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define lbv lower_bound(v.begin(), v.end(), x) - v.begin()
#define upv upper_bound(v.begin(), v.end(), x) - v.begin()
#define lba lower_bound(a, a + n, x) - a
#define upa upper_bound(a, a + n, x) - a
const int mod = 1e9 + 7;
using namespace std;
int helper(int x, long y)
{
  if (y == 0)
    return 1;
  int res = helper(x, y / 2);
  if (y & 1)
    return ((long)res * res * x) % mod;
  else
    return ((long)res * res) % mod;
  return 1;
}
class DisjointSet
{
public:
  vector<int> size, parent, rank;
  DisjointSet(int n)
  {
    size.resize(n + 1, 1);
    parent.resize(n + 1, 0);
    rank.resize(n + 1, 0);
    for (int i = 0; i <= n; i++)
    {
      parent[i] = i;
    }
  }
  int findUpar(int u)
  {
    if (u == parent[u])
    {
      return u;
    }
    return parent[u] = findUpar(parent[u]);
  }
  void unionBySize(int u, int v)
  {
    int ulp_u = findUpar(u);
    int ulp_v = findUpar(v);
    if (ulp_u == ulp_v)
    {
      return;
    }
    if (size[ulp_u] < size[ulp_v])
    {
      parent[ulp_u] = ulp_v;
      size[ulp_v] += size[ulp_u];
    }
    else
    {
      parent[ulp_v] = ulp_u;
      size[ulp_u] += size[ulp_v];
    }
  }
};
void solve()
{
  int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++)
    {
      int u, v;
      cin >> u >> v;
      u--;
      v--;
      edges.pb({u, v});
    }
    cout << "cut vertex is ";
    vector<int> min_cut_v;
  int mini = INT_MAX;
  for (int j = 0; j < n; j++)
  {
    int node = j;
    vector<pair<int, int>> v;
    vector<vector<int>> adj(n);
    for (auto it : edges)
    {
      if (it.first == node || it.second == node)
      {
        continue;
      }
      else
      {
        v.pb(it);
        adj[it.first].pb(it.second);
        adj[it.second].pb(it.first);
      }
    }
    DisjointSet ds(n);
    for (auto it : v)
    {
      if(ds.findUpar(it.first) != ds.findUpar(it.second))
          ds.unionBySize(it.first, it.second);
    }
    int cnt = 0;
    set<int> st;
    for (int i = 0; i < n; i++)
    {
      if (i == node)
      {
        continue;
      }
      else
      {
        st.insert(ds.findUpar(i));
      }
    }
    if (st.size() > 1)
    {
      if (mini > st.size())
      {
        mini = st.size();
        min_cut_v.clear();
        min_cut_v.pb(node);
      }
      else if (mini == st.size())
      {
        min_cut_v.pb(node);
      }
      cout << node + 1 << " ";
    }
  }
  cout << endl;
  cout << "Min cut vertex is ";
  for (auto it : min_cut_v)
  {
    cout << it + 1 << " ";
  }
  cout << endl;
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  t = 1;
  cin >> t;
  int tampi = 0;
  while (t--)
  {
    cout << "Testcase " << tampi + 1 << endl;
    tampi++;
    solve();
  }
}