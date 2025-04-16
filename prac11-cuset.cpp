#include <bits/stdc++.h>
using namespace std;

class DSU
{
public:
    vector<int> parent;
    vector<int> sz;
    int components;
    DSU(int n)
    {
        components = n + 1;
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int findulp(int node)
    {
        if (parent[node] != node)
        {
            return parent[node] = findulp(parent[node]);
        }
        return parent[node];
    }

    void merge(int u, int v)
    {
        int up = findulp(u);
        int vp = findulp(v);

        if (sz[up] > sz[vp])
            swap(up, vp);
        if (up != vp)
        {
            components--;
            parent[up] = vp;
            sz[vp] += sz[up];
        }
    }
};

set<vector<pair<int, int>>> allcutset;
vector<pair<int, int>> mincutset;

void karger(vector<pair<int, int>> &edges, int n)
{
    int m = edges.size();
    vector<pair<int, int>> inital = edges;
    mincutset = edges;
    while (true)
    {
        DSU ds(n);
        vector<pair<int, int>> curr;
        for (int i = 0; i < m; i++)
        {
            int u = edges[i].first;
            int v = edges[i].second;
            ds.merge(u, v);
            if (ds.components == 2)
            {
                for (int j = i; j < m; j++)
                {
                    curr.push_back(edges[j]);
                }
                sort(curr.begin(), curr.end());
                allcutset.insert(curr);
                if (mincutset.size() > curr.size())
                {
                    mincutset = curr;
                    break;
                }
            }
        }
        next_permutation(edges.begin(), edges.end());
        if (edges == inital)
        {
            break;
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    allcutset.clear();
    mincutset.clear();
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }
    karger(edges, n);
    cout << "Mincutset size is: " << mincutset.size() << endl;
    cout << "Our Mincutset is below one" << endl;
    for (auto it : mincutset)
    {
        int u = it.first;
        int v = it.second;
        cout << u << "<-->" << v << endl;
    }
    int i = 1;
    cout << endl;
    for (auto vec : allcutset)
    {
        cout << "cutset " << i << endl;
        for (auto it : vec)
        {
            int u = it.first;
            int v = it.second;
            cout << u << "<-->" << v << endl;
        }
        cout << endl;
        i++;
    }
}