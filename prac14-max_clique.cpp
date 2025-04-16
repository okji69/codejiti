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
int binaryExp(int x, long y)
{
  if (y == 0)
    return 1;
  int res = binaryExp(x, y / 2);
  if (y & 1)
    return ((long)res * res * x) % mod;
  else
    return ((long)res * res) % mod;
  return 1;
}
vector<int> generatePrimes(int n)
{
  vector<bool> isPrime(n + 1, true);
  vector<int> primes;
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i <= n; i++)
  {
    if (isPrime[i])
    {
      primes.push_back(i);
      for (int j = 2 * i; j <= n; j += i)
        isPrime[j] = false;
    }
  }
  return primes;
}
string decimalToBinary(int n) { return bitset<32>(n).to_string(); }
vector<vector<pair<int, int>>> subgraphs;
void allSubGraphs(int n, int m, vector<pair<int, int>> &v)
{
  subgraphs.clear();
  int k = (1 << m);
  for (int i = 0; i < k; i++)
  {
    vector<pair<int, int>> temp;
    for (int j = 0; j < m; j++)
    {
      if (i & ((1 << j)))
      {
        temp.push_back(v[j]);
      }
    }
    subgraphs.pb(temp);
  }
}

vector<vector<pair<int, int>>> clique;
bool checkclique(vector<pair<int, int>> temp, int n)
{
  int size = temp.size();
  if (size <= 1)
  {
    return false;
  }

  vector<int> deg(n);
  set<int> numv;
  for (auto it : temp)
  {
    numv.insert(it.first);
    numv.insert(it.second);
    deg[it.first - 1]++;
    deg[it.second - 1]++;
  }
  int cnt1 = 0, cnt = 0;
  for (int i = 0; i < n; i++)
  {
    if (deg[i] == numv.size() - 1)
    {
      cnt1++;
    }
  }
  if (numv.size() == cnt1)
  {
    return true;
  }
  return false;
}
void solve()
{
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> v(m);
  for (int i = 0; i < m; i++)
  {
    int k1, k2;
    cin >> k1 >> k2;
    v[i] = {k1, k2};
  }
  int j = 0;
  allSubGraphs(n, m, v);
  // for(auto it:subgraphs)
  // {
  //   cout<<"Graph no "<<j+1<<endl;
  //   j++;
  //   for(auto i:it)
  //   {
  //     cout<<i.first<<" "<<i.second<<endl;
  //   }
  //   cout<<endl;
  // }
  int cnt = 0;
  int maxi = 0;
  for (auto it : subgraphs)
  {
    if (checkclique(it, n))
    {
      int p = 0;
      set<int> d;
      for (auto z : it)
      {
        d.insert(z.first);
        d.insert(z.second);
      }
      p = d.size();
      cnt++;
      cout << "clique k" << p << endl;
      maxi = max(maxi, p);
      for (auto i : it)
      {
        cout << i.first << " " << i.second << endl;
      }
    }
  }
  cout << endl;
  cout << "total clique ";
  cout << cnt << endl;
  cout << "max clique is k" << maxi << endl;
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  t = 1;
  // cin >> t;
  while (t--)
  {
    solve();
  }
}