#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> adjMask;

bool isIndependentSet(int mask)
{
  for (int i = 0; i < n; ++i)
  {
    if (mask & (1 << i))
    {
      if (adjMask[i] & mask)
        return false; // Adjacent vertex also in set
    }
  }
  return true;
}

void findAllIndependentSets()
{
  cout << "All Independent Sets:\n";
  int total = 1 << n;
  for (int mask = 0; mask < total; ++mask)
  {
    if (isIndependentSet(mask))
    {
      cout << "{ ";
      for (int i = 0; i < n; ++i)
      {
        if (mask & (1 << i))
          cout << i << " ";
      }
      cout << "}\n";
    }
  }
}

bool isMaximalSet(int mask)
{
  for (int i = 0; i < n; ++i)
  {
    if (!(mask & (1 << i)))
    { 
      if ((adjMask[i] & mask) == 0)
        return false; // can add i without conflict
    }
  }
  return true;
}

void findMaximalIndependentSets()
{
  cout << "\nMaximal Independent Sets:\n";
  int total = 1 << n;
  for (int mask = 0; mask < total; ++mask)
  {
    if (isIndependentSet(mask) && isMaximalSet(mask))
    {
      cout << "{ ";
      for (int i = 0; i < n; ++i)
      {
        if (mask & (1 << i))
          cout << i << " ";
      }
      cout << "}\n";
    }
  }
}

int main()
{
  cout << "Enter number of vertices and edges:\n";
  cin >> n >> m;
  adjMask.assign(n, 0);

  cout << "Enter " << m << " edges (u v):\n";
  for (int i = 0; i < m; ++i)
  {
    int u, v;
    cin >> u >> v;
    adjMask[u] |= (1 << v);
    adjMask[v] |= (1 << u);
  }

  findAllIndependentSets();
  findMaximalIndependentSets();
  return 0;
}
