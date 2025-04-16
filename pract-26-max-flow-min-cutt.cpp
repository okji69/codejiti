#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Perform BFS to find if there is a path from source to sink
bool bfs(vector<vector<int>> &residual, int s, int t, vector<int> &parent)
{
  int V = residual.size();
  vector<bool> visited(V, false);
  queue<int> q;

  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty())
  {
    int u = q.front();
    q.pop();

    for (int v = 0; v < V; ++v)
    {
      if (!visited[v] && residual[u][v] > 0)
      {
        parent[v] = u;
        visited[v] = true;
        q.push(v);
        if (v == t)
          return true;
      }
    }
  }
  return false;
}

// DFS for finding the reachable vertices in residual graph after max flow
void dfs(int u, vector<vector<int>> &residual, vector<bool> &visited)
{
  visited[u] = true;
  for (int v = 0; v < residual.size(); ++v)
  {
    if (residual[u][v] > 0 && !visited[v])
    {
      dfs(v, residual, visited);
    }
  }
}

int fordFulkerson(vector<vector<int>> &capacity, int s, int t)
{
  int V = capacity.size();
  vector<vector<int>> residual = capacity;
  vector<int> parent(V);
  int maxFlow = 0;

  while (bfs(residual, s, t, parent))
  {
    int pathFlow = INT_MAX;

    // Find minimum residual capacity in the path
    for (int v = t; v != s; v = parent[v])
    {
      int u = parent[v];
      pathFlow = min(pathFlow, residual[u][v]);
    }

    // Update residual capacities
    for (int v = t; v != s; v = parent[v])
    {
      int u = parent[v];
      residual[u][v] -= pathFlow;
      residual[v][u] += pathFlow;
    }

    maxFlow += pathFlow;
  }

  // Find vertices reachable from source in residual graph
  vector<bool> visited(V, false);
  dfs(s, residual, visited);

  cout << "\nMinimum Cut Edges (from reachable to non-reachable):\n";
  for (int u = 0; u < V; ++u)
  {
    for (int v = 0; v < V; ++v)
    {
      if (visited[u] && !visited[v] && capacity[u][v] > 0)
      {
        cout << u << " - " << v << endl;
      }
    }
  }

  return maxFlow;
}

int main()
{
  int V, E;
  cout << "Enter number of vertices and edges: ";
  cin >> V >> E;

  vector<vector<int>> capacity(V, vector<int>(V, 0));

  cout << "Enter edges in format (from to capacity):\n";
  for (int i = 0; i < E; ++i)
  {
    int u, v, cap;
    cin >> u >> v >> cap;
    capacity[u][v] = cap; // directed edge from u to v
  }

  int source, sink;
  cout << "Enter source and sink: ";
  cin >> source >> sink;

  int maxFlow = fordFulkerson(capacity, source, sink);
  cout << "\nMaximum Flow: " << maxFlow << endl;

  return 0;
}