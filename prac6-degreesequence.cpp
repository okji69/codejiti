#include <bits/stdc++.h>
#define pb push_back
#define ll long long
#define int long long int
#define all(v) v.begin(), v.end()
using namespace std;

bool f(vector<pair<int, int>> &v, vector<vector<int>> &adj)
{
  int n = v.size();
  int flag = 0;
  for (int i = 0; i < n; i++)
  {
    if (v[i].first < 0)
    {
      return false;
    }
    if (v[i].first == 0)
    {
      continue;
    }
    else
    {
      flag = 1;
      break;
    }
  }
  if (flag == 0)
  {
    return true;
  }
  sort(all(v));
  reverse(all(v));
  int k = v[0].first;
  if (k >= n)
  {
    return false;
  }
  for (int i = 1; i <= k; i++)
  {
    v[i].first--;
    adj[v[0].second][v[i].second] = 1;
    adj[v[i].second][v[0].second] = 1;
  }
  v.erase(v.begin());
  return f(v, adj);
}

signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector<pair<int, int>> v;
  int cnt = 0;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    v.pb({x, i + 1});
    cnt += x;
  }
  vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
  if (cnt % 2 == 1)
  {
    cout << "NO" << endl;
    return 0;
  }
  if (f(v, adj))
  {
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        cout << adj[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
  else
  {
    cout << "NO" << endl;
  }
}
