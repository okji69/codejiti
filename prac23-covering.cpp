#include <iostream>
#include <vector>
using namespace std;

int V, E;
vector<pair<int, int>> edges;

bool isCoveringSet(int mask)
{
  for (auto it : edges)
  {
    int u = it.first;
    int v = it.second;
    if (!(mask & (1 << u)) && !(mask & (1 << v)))
    {
      return false;
    }
  }
  return true;
}

bool isMinimalCoveringSet(int mask)
{
  if (!isCoveringSet(mask))
    return false;

  for (int v = 0; v < V; ++v)
  {
    if (mask & (1 << v))
    {
      int newMask = mask ^ (1 << v);
      if (isCoveringSet(newMask))
        return false;
    }
  }
  return true;
}

void findCoveringSets()
{
  vector<int> coveringSets;
  vector<int> minimalCoveringSets;
  int coveringNumber = V;

  int totalMasks = 1 << V;

  for (int mask = 1; mask < totalMasks; ++mask)
  {
    if (isCoveringSet(mask))
    {
      coveringSets.push_back(mask);

      if (isMinimalCoveringSet(mask))
      {
        minimalCoveringSets.push_back(mask);
        int setSize = __builtin_popcount(mask);
        if (setSize < coveringNumber)
          coveringNumber = setSize;
      }
    }
  }

  cout << "\nAll Covering Sets:\n";
  for (int mask : coveringSets)
  {
    cout << "{ ";
    for (int i = 0; i < V; ++i)
      if (mask & (1 << i))
        cout << i << " ";
    cout << "}\n";
  }

  cout << "\nAll Minimal Covering Sets:\n";
  for (int mask : minimalCoveringSets)
  {
    cout << "{ ";
    for (int i = 0; i < V; ++i)
      if (mask & (1 << i))
        cout << i << " ";
    cout << "}\n";
  }

  cout << "\nCovering Number (minimum size of minimal covering set): " << coveringNumber << endl;
}

int main()
{
  cout << "Enter number of vertices: ";
  cin >> V;
  cout << "Enter number of edges: ";
  cin >> E;

  edges.resize(E);
  cout << "Enter edges (u v):\n";
  for (int i = 0; i < E; ++i)
  {
    int u, v;
    cin >> u >> v;
    edges[i] = {u, v};
  }

  findCoveringSets();

  return 0;
}
