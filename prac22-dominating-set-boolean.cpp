#include <iostream>
#include <vector>
using namespace std;

int V, E;
vector<int> adjMask;

void addEdge(int u, int v)
{
  adjMask[u] |= (1 << v);
  adjMask[v] |= (1 << u);
}

bool isDominatingSet(int mask)
{
  int covered = 0;
  for (int v = 0; v < V; ++v)
  {
    if (mask & (1 << v))
    {
      covered |= (1 << v);   // cover itself
      covered |= adjMask[v]; // cover neighbors
    }
  }
  return (covered == (1 << V) - 1); // all vertices are covered
}

bool isMinimalDominatingSet(int mask)
{
  if (!isDominatingSet(mask))
    return false;

  for (int v = 0; v < V; ++v)
  {
    if (mask & (1 << v))
    {
      int newMask = mask ^ (1 << v); // remove v
      if (isDominatingSet(newMask))
        return false;
    }
  }
  return true;
}

void findDominatingSets()
{
  vector<int> dominatingSets;
  vector<int> minimalDominatingSets;
  int dominationNumber = V;

  int totalMasks = 1 << V;

  for (int mask = 1; mask < totalMasks; ++mask)
  {
    if (isDominatingSet(mask))
    {
      dominatingSets.push_back(mask);

      if (isMinimalDominatingSet(mask))
      {
        minimalDominatingSets.push_back(mask);
        int setSize = __builtin_popcount(mask);
        if (setSize < dominationNumber)
          dominationNumber = setSize;
      }
    }
  }

  cout << "\nAll Dominating Sets:\n";
  for (int mask : dominatingSets)
  {
    cout << "{ ";
    for (int v = 0; v < V; ++v)
      if (mask & (1 << v))
        cout << v << " ";
    cout << "}\n";
  }

  cout << "\nAll Minimal Dominating Sets:\n";
  for (int mask : minimalDominatingSets)
  {
    cout << "{ ";
    for (int v = 0; v < V; ++v)
      if (mask & (1 << v))
        cout << v << " ";
    cout << "}\n";
  }

  cout << "\nDomination Number: " << dominationNumber << endl;
}

int main()
{
  cout << "Enter number of vertices: ";
  cin >> V;
  cout << "Enter number of edges: ";
  cin >> E;

  adjMask.assign(V, 0);

  cout << "Enter edges (u v):\n";
  for (int i = 0; i < E; ++i)
  {
    int u, v;
    cin >> u >> v;
    addEdge(u, v);
  }

  findDominatingSets();

  return 0;
}
