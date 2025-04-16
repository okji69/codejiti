#include <iostream>
#include <vector>
#include <set>
using namespace std;

int n, m;
vector<vector<int>> adj;

bool isIndependent(const vector<int> &subset)
{
    for (int i = 0; i < subset.size(); ++i)
    {
        for (int j = i + 1; j < subset.size(); ++j)
        {
            if (adj[subset[i]][subset[j]])
                return false;
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
        vector<int> subset;
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
                subset.push_back(i);
        }
        if (isIndependent(subset))
        {
            cout << "{ ";
            for (int v : subset)
                cout << v << " ";
            cout << "}\n";
        }
    }
}

bool isMaximal(const vector<int> &subset)
{
    set<int> inSet(subset.begin(), subset.end());
    for (int v = 0; v < n; ++v)
    {
        if (inSet.count(v)) continue;
        bool canAdd = true;
        for (int u : subset)
        {
            if (adj[u][v])
            {
                canAdd = false;
                break;
            }
        }
        if (canAdd)
            return false;
    }
    return true;
}

void findMaximalIndependentSets()
{
    cout << "\nMaximal Independent Sets:\n";
    int total = 1 << n;
    for (int mask = 0; mask < total; ++mask)
    {
        vector<int> subset;
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
                subset.push_back(i);
        }
        if (isIndependent(subset) && isMaximal(subset))
        {
            cout << "{ ";
            for (int v : subset)
                cout << v << " ";
            cout << "}\n";
        }
    }
}

// ------------------------ Chromatic Partitioning ------------------------
bool isSafeColor(int vertex, int c, const vector<int> &color)
{
    for (int i = 0; i < n; ++i)
    {
        if (adj[vertex][i] && color[i] == c)
            return false;
    }
    return true;
}

bool colorGraph(int vertex, int maxColor, vector<int> &color)
{
    if (vertex == n)
        return true;

    for (int c = 1; c <= maxColor; ++c)
    {
        if (isSafeColor(vertex, c, color))
        {
            color[vertex] = c;
            if (colorGraph(vertex + 1, maxColor, color))
                return true;
            color[vertex] = 0;
        }
    }
    return false;
}

void chromaticPartition()
{
    int chromaticNumber = n;
    vector<int> color(n, 0);

    for (int k = 1; k <= n; ++k)
    {
        fill(color.begin(), color.end(), 0);
        if (colorGraph(0, k, color))
        {
            chromaticNumber = k;
            cout << "\nChromatic Number: " << chromaticNumber << endl;
            vector<vector<int>> colorClasses(k + 1);
            for (int v = 0; v < n; ++v)
                colorClasses[color[v]].push_back(v);

            cout << "Color Classes (Partitions):\n";
            for (int i = 1; i <= k; ++i)
            {
                cout << "Color " << i << ": { ";
                for (int v : colorClasses[i])
                    cout << v << " ";
                cout << "}\n";
            }
            break;
        }
    }
}

// ------------------------ MAIN ------------------------

int main()
{
    cout << "Enter number of vertices and edges:\n";
    cin >> n >> m;
    adj.assign(n, vector<int>(n, 0));

    cout << "Enter " << m << " edges (u v):\n";
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = 1;
    }

    findAllIndependentSets();
    findMaximalIndependentSets();
    chromaticPartition();

    return 0;
}
