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
