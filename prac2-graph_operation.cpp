#include<bits/stdc++.h>
using namespace std;

void add_edge(map<int, set<int>> &g, int u, int v) {
    g[u].insert(v);
    g[v].insert(u);
}

void del_edge(map<int, set<int>> &g, int u, int v) {
    g[u].erase(v);
    g[v].erase(u);
}

void del_vertex(map<int, set<int>> &g, int v) {
    for (int n : g[v])
        g[n].erase(v);
    g.erase(v);
}

void fuse(map<int, set<int>> &g, int u, int v) {
    for (int n : g[v]) {
        if (n != u) {
            g[u].insert(n);
            g[n].insert(u);
        }
        g[n].erase(v);
    }
    g.erase(v);
}

void print_graph(map<int, set<int>> &g) {
    for (auto &p : g) {
        cout << p.first << " -> ";
        for (int n : p.second) cout << n << " ";
        cout << endl;
    }
}

map<int, set<int>> graph_union(map<int, set<int>> &g1, map<int, set<int>> &g2) {
    map<int, set<int>> g;
    for (auto &p : g1)
        for (int n : p.second) add_edge(g, p.first, n);
    for (auto &p : g2)
        for (int n : p.second) add_edge(g, p.first, n);
    return g;
}

map<int, set<int>> graph_inter(map<int, set<int>> &g1, map<int, set<int>> &g2) {
    map<int, set<int>> g;
    for (auto &p : g1) {
        for (int n : p.second) {
            if (g2.count(p.first) && g2.at(p.first).count(n))
                add_edge(g, p.first, n);
        }
    }
    return g;
}

map<int, set<int>> graph_diff(map<int, set<int>> &g1, map<int, set<int>> &g2) {
    map<int, set<int>> g;
    for (auto &p : g1) {
        for (int n : p.second) {
            if (!g2.count(p.first) || !g2.at(p.first).count(n))
                add_edge(g, p.first, n);
        }
    }
    return g;
}

map<int, set<int>> graph_ring(map<int, set<int>> &g1, map<int, set<int>> &g2) {
    map<int, set<int>> u = graph_union(g1, g2);
    map<int, set<int>> i = graph_inter(g1, g2);
    return graph_diff(u, i);
}

map<int, set<int>> graph_compl(map<int, set<int>> &g, int vtx) {
    map<int, set<int>> c;
    for (int i = 0; i < vtx; i++) {
        for (int j = i + 1; j < vtx; j++) {
            if (!g[i].count(j)) add_edge(c, i, j);
        }
    }
    return c;
}

void dfs(int v, map<int, set<int>> &g, set<int> &vis) {
    vis.insert(v);
    cout << v << " ";
    for (int n : g[v]) {
        if (!vis.count(n)) dfs(n, g, vis);
    }
}

void decompose(map<int, set<int>> &g, int vtx) {
    set<int> vis;
    int comp = 1;
    for (int i = 0; i < vtx; i++) {
        if (!vis.count(i) && g.count(i)) {
            cout << "Component " << comp++ << ": ";
            dfs(i, g, vis);
            cout << endl;
        }
    }
}

int main() {
    int v1, e1, v2, e2;
    cout << "Enter vertices and edges for Graph 1: ";
    cin >> v1 >> e1;
    map<int, set<int>> g1;
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e1; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(g1, u, v);
    }

    cout << "Enter vertices and edges for Graph 2: ";
    cin >> v2 >> e2;
    map<int, set<int>> g2;
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e2; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(g2, u, v);
    }

    cout << "\nUnion:\n";
    auto gu = graph_union(g1, g2);
    print_graph(gu);

    cout << "\nIntersection:\n";
    auto gi = graph_inter(g1, g2);
    print_graph(gi);

    cout << "\nComplement of Graph 1:\n";
    auto gc = graph_compl(g1, v1);
    print_graph(gc);

    cout << "\nDifference (G1 - G2):\n";
    auto gd = graph_diff(g1, g2);
    print_graph(gd);

    cout << "\nRing Sum:\n";
    auto gr = graph_ring(g1, g2);
    print_graph(gr);

    cout << "\nDecomposition of Graph 1:\n";
    decompose(g1, v1);

    return 0;
}


#include <bits/stdc++.h>
using namespace std;

void addEdge(vector<vector<int>> &adjList, int u, int v)
{
    if (u < adjList.size() && v < adjList.size())
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}

void printGraph(const vector<vector<int>> &adjList)
{
    for (int i = 0; i < adjList.size(); i++)
    {
        cout << i << ": ";
        for (int v : adjList[i])
        {
            cout << v << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> graphUnion(const vector<vector<int>> &g1, const vector<vector<int>> &g2)
{
    vector<vector<int>> result = g1;
    for (int i = 0; i < g2.size(); i++)
    {
        for (int j : g2[i])
        {
            if (find(result[i].begin(), result[i].end(), j) == result[i].end())
            {
                result[i].push_back(j);
            }
        }
    }
    return result;
}

vector<vector<int>> graphIntersection(const vector<vector<int>> &g1, const vector<vector<int>> &g2)
{
    vector<vector<int>> result(g1.size());
    for (int i = 0; i < g1.size(); i++)
    {
        for (int j : g1[i])
        {
            if (find(g2[i].begin(), g2[i].end(), j) != g2[i].end())
            {
                result[i].push_back(j);
            }
        }
    }
    return result;
}

vector<vector<int>> graphDifference(const vector<vector<int>> &g1, const vector<vector<int>> &g2)
{
    vector<vector<int>> result(g2.size());
    for (int i = 0; i < g2.size(); i++)
    {
        for (int j : g2[i])
        {
            if (find(g1[i].begin(), g1[i].end(), j) == g1[i].end())
            {
                result[i].push_back(j);
            }
        }
    }
    return result;
}

vector<vector<int>> graphRingSum(const vector<vector<int>> &g1, const vector<vector<int>> &g2)
{
    vector<vector<int>> diff1 = graphDifference(g1, g2);
    vector<vector<int>> diff2 = graphDifference(g2, g1);
    return graphUnion(diff1, diff2);
}

vector<vector<int>> graphDecomposition(const vector<vector<int>> &graph)
{
    vector<vector<int>> result = graph;
    if (find(result[0].begin(), result[0].end(), 1) != result[0].end())
    {
        result[0].erase(remove(result[0].begin(), result[0].end(), 1), result[0].end());
        result[1].erase(remove(result[1].begin(), result[1].end(), 0), result[1].end());
    }
    return result;
}

void fusionOfVertices(vector<vector<int>> &graph, int u, int v)
{
    for (int neighbor : graph[v])
    {
        if (neighbor != u)
        {
            if (find(graph[u].begin(), graph[u].end(), neighbor) == graph[u].end())
            {
                graph[u].push_back(neighbor);
            }
            for (int &vertex : graph[neighbor])
            {
                if (vertex == v)
                {
                    vertex = u;
                }
            }
        }
    }
    graph[v].clear();
}

int main()
{
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> primaryGraph(n);
    cout << "Enter edges for primary graph (-1 -1 to stop):\n";
    while (true)
    {
        int u, v;
        cin >> u >> v;
        if (u == -1)
            break;
        addEdge(primaryGraph, u, v);
    }

    vector<vector<int>> secondaryGraph(n);
    cout << "Enter edges for secondary graph (-1 -1 to stop):\n";
    while (true)
    {
        int u, v;
        cin >> u >> v;
        if (u == -1)
            break;
        addEdge(secondaryGraph, u, v);
    }

    while (true)
    {
        cout << "1. Print primary graph\n";
        cout << "2. Print secondary graph\n";
        cout << "3. Union of graphs\n";
        cout << "4. Intersection of graphs\n";
        cout << "5. Difference (Primary - Secondary)\n";
        cout << "6. Ring sum of graphs\n";
        cout << "7. Decomposition of primary graph\n";
        cout << "8. Fuse vertices\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Primary Graph:\n";
            printGraph(primaryGraph);
            break;
        case 2:
            cout << "Secondary Graph:\n";
            printGraph(secondaryGraph);
            break;
        case 3:
            cout << "Union Result:\n";
            printGraph(graphUnion(primaryGraph, secondaryGraph));
            break;
        case 4:
            cout << "Intersection Result:\n";
            printGraph(graphIntersection(primaryGraph, secondaryGraph));
            break;
        case 5:
            cout << "Difference Result:\n";
            printGraph(graphDifference(primaryGraph, secondaryGraph));
            break;
        case 6:
            cout << "Ring Sum Result:\n";
            printGraph(graphRingSum(primaryGraph, secondaryGraph));
            break;
        case 7:
            cout << "Decomposition Result (splitting at vertices 0 and 1):\n";
            printGraph(graphDecomposition(primaryGraph));
            break;
        case 8:
            cout << "Enter vertices to fuse (u v): ";
            int fu, fv;
            cin >> fu >> fv;
            fusionOfVertices(primaryGraph, fu, fv);
            cout << "After fusion:\n";
            printGraph(primaryGraph);
            break;
        case 9:
            return 0;
        default:
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
