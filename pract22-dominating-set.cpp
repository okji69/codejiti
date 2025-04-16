#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int V, E;
vector<vector<int>> adj;

bool isDominatingSet(const vector<int> &set)
{
  vector<bool> covered(V, false);

  for (int u : set)
  {
    covered[u] = true;
    for (int v : adj[u])
      covered[v] = true;
  }

  for (bool cov : covered)
  {
    if (!cov)
      return false;
  }
  return true;
}

bool isMinimalDominatingSet(const vector<int> &set)
{
  if (!isDominatingSet(set))
    return false;

  for (int i = 0; i < set.size(); ++i)
  {
    vector<int> temp = set;
    temp.erase(temp.begin() + i);
    if (isDominatingSet(temp))
      return false;
  }
  return true;
}

void findDominatingSets()
{
  vector<vector<int>> dominatingSets;
  vector<vector<int>> minimalDominatingSets;
  int dominationNumber = V;

  int totalSets = 1 << V;

  for (int mask = 1; mask < totalSets; ++mask)
  {
    vector<int> subset;
    for (int i = 0; i < V; ++i)
    {
      if (mask & (1 << i))
        subset.push_back(i);
    }

    if (isDominatingSet(subset))
    {
      dominatingSets.push_back(subset);

      if (isMinimalDominatingSet(subset))
      {
        minimalDominatingSets.push_back(subset);
        dominationNumber = min(dominationNumber, (int)subset.size());
      }
    }
  }

  cout << "\nAll Dominating Sets:\n";
  for (auto &set : dominatingSets)
  {
    cout << "{ ";
    for (int v : set)
      cout << v << " ";
    cout << "}\n";
  }

  cout << "\nAll Minimal Dominating Sets:\n";
  for (auto &set : minimalDominatingSets)
  {
    cout << "{ ";
    for (int v : set)
      cout << v << " ";
    cout << "}\n";
  }

  cout << "\nDomination Number (smallest size of minimal dominating set): " << dominationNumber << endl;
}

int main()
{
  cout << "Enter number of vertices: ";
  cin >> V;
  cout << "Enter number of edges: ";
  cin >> E;

  adj.assign(V, vector<int>());

  cout << "Enter edges (u v):\n";
  for (int i = 0; i < E; ++i)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  findDominatingSets();

  return 0;
}
