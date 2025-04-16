#include <bits/stdc++.h>
using namespace std;
set<multiset<int>> func(vector<vector<int>> g)

{
    set<multiset<int>> s;
    for (auto it : g)
    {
        multiset<int> temp;
        for (auto it1 : it)
        {
            temp.insert(int(g[it1].size()));
        }
        s.insert(temp);
    }
    return s;
}
int main()
{
    int n, m;
    cout << "Enter the number of nodes of edges of graph1";
    cin >> n >> m;
    vector<vector<int>> g1(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g1[a].push_back(b);
        g1[b].push_back(a);
    }
    set<multiset<int>> s1 = func(g1);
    vector<vector<int>> g2(n);
    cout << "Enter the number of nodes of edges of graph2";
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g2[a].push_back(b);
        g2[b].push_back(a);
    }
    set<multiset<int>> s2 = func(g2);
    if (s1 == s2)
    {
        cout << "The graphs are isomorphic";
    }
    else
    {
        cout << "The graphs are not isomorphic";
    }
}