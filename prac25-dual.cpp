#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class PlanarGraph
{
private:
  struct Edge
  {
    int src, dest;
    int face1, face2;

    Edge(int s, int d) : src(s), dest(d), face1(-1), face2(-1) {}
  };

  int V;
  vector<Edge> edges;
  vector<vector<int>> faces;
  map<pair<int, int>, int> edgeMap;

public:
  PlanarGraph(int vertices) : V(vertices) {}

  void addEdge(int src, int dest)
  {

    if (src < 0 || src >= V || dest < 0 || dest >= V)
    {
      cout << "Invalid vertex indices!" << endl;
      return;
    }

    pair<int, int> edgePair = {min(src, dest), max(src, dest)};
    if (edgeMap.find(edgePair) != edgeMap.end())
    {
      cout << "Edge already exists!" << endl;
      return;
    }

    edges.push_back(Edge(src, dest));
    int edgeIndex = edges.size() - 1;
    edgeMap[edgePair] = edgeIndex;
    cout << "Edge added: " << src << " -- " << dest << endl;
  }

  void addFace(const vector<int> &cycle)
  {

    if (cycle.size() < 3)
    {
      cout << "Invalid face! A face must have at least 3 vertices." << endl;
      return;
    }
    for (size_t i = 0; i < cycle.size(); i++)
    {
      int u = cycle[i];
      int v = cycle[(i + 1) % cycle.size()];

      pair<int, int> edgePair = {min(u, v), max(u, v)};
      if (edgeMap.find(edgePair) == edgeMap.end())
      {
        cout << "Edge (" << u << ", " << v << ") does not exist in the graph!" << endl;
        return;
      }
    }

    faces.push_back(cycle);
    int faceIndex = faces.size() - 1;
    for (size_t i = 0; i < cycle.size(); i++)
    {
      int u = cycle[i];
      int v = cycle[(i + 1) % cycle.size()];

      pair<int, int> edgePair = {min(u, v), max(u, v)};
      int edgeIndex = edgeMap[edgePair];
      if (edges[edgeIndex].face1 == -1)
      {
        edges[edgeIndex].face1 = faceIndex;
      }
      else if (edges[edgeIndex].face2 == -1)
      {
        edges[edgeIndex].face2 = faceIndex;
      }
      else
      {
        cout << "Warning: Edge (" << u << ", " << v << ") already has two faces!" << endl;
      }
    }

    cout << "Face added: ";
    for (int v : cycle)
    {
      cout << v << " ";
    }
    cout << endl;
  }

  PlanarGraph computeDual()
  {
    int dualVertices = faces.size();
    PlanarGraph dual(dualVertices);

    for (const Edge &edge : edges)
    {

      if (edge.face1 != -1 && edge.face2 != -1)
      {
        dual.addEdge(edge.face1, edge.face2);
      }
    }

    return dual;
  }
  bool isValidForDual()
  {
    if (faces.empty())
    {
      cout << "No faces defined! Cannot compute dual." << endl;
      return false;
    }

    for (const Edge &edge : edges)
    {
      if (edge.face1 == -1)
      {
        cout << "Warning: Edge (" << edge.src << ", " << edge.dest << ") has no faces assigned." << endl;
      }
    }

    return true;
  }

  void printGraph()
  {
    cout << "Graph with " << V << " vertices and " << edges.size() << " edges:" << endl;
    for (size_t i = 0; i < edges.size(); i++)
    {
      cout << "Edge " << i << ": " << edges[i].src << " -- " << edges[i].dest;
      cout << " (Faces: " << edges[i].face1 << ", " << edges[i].face2 << ")" << endl;
    }

    cout << "\nFaces:" << endl;
    for (size_t i = 0; i < faces.size(); i++)
    {
      cout << "Face " << i << ": ";
      for (int v : faces[i])
      {
        cout << v << " ";
      }
      cout << endl;
    }
  }

  int getVertexCount() const
  {
    return V;
  }

  int getEdgeCount() const
  {
    return edges.size();
  }

  int getFaceCount() const
  {
    return faces.size();
  }
};

vector<int> readIntegerSequence(const string &prompt)
{
  vector<int> sequence;
  string input;

  cout << prompt;
  getline(cin, input);

  // Parse space-separated integers
  stringstream ss(input);
  int num;
  while (ss >> num)
  {
    sequence.push_back(num);
  }

  return sequence;
}

int main()
{
  int V;
  cout << "Enter the number of vertices in the graph: ";
  cin >> V;
  cin.ignore();

  PlanarGraph graph(V);

  cout << "\n--- Edge Input ---" << endl;
  cout << "Enter edges (pairs of vertices). Enter -1 -1 to finish." << endl;

  while (true)
  {
    int src, dest;
    cout << "Enter edge (src dest): ";
    cin >> src >> dest;

    if (src == -1 && dest == -1)
    {
      break;
    }

    graph.addEdge(src, dest);
  }
  cin.ignore();

  cout << "\n--- Face Input ---" << endl;
  cout << "Enter faces (cycles of vertices). Enter an empty line to finish." << endl;
  cout << "Format: List of vertices in order around the face, separated by spaces." << endl;

  while (true)
  {
    vector<int> face = readIntegerSequence("Enter face vertices: ");
    if (face.empty())
    {
      break;
    }

    graph.addFace(face);
  }
  cout << "\nOriginal Graph:" << endl;
  graph.printGraph();

  if (graph.isValidForDual())
  {

    PlanarGraph dual = graph.computeDual();

    cout << "\nDual Graph:" << endl;
    dual.printGraph();

    cout << "\nSummary:" << endl;
    cout << "Original Graph: " << graph.getVertexCount() << " vertices, "
         << graph.getEdgeCount() << " edges, " << graph.getFaceCount() << " faces" << endl;
    cout << "Dual Graph: " << dual.getVertexCount() << " vertices, "
         << dual.getEdgeCount() << " edges, " << dual.getFaceCount() << " faces" << endl;
  }
  return 0;
}