#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define min2 min(a, b)
#define max2 max(a, b)
#define eb emplace_back
#define f(i, x, n) for (int i = x; i < n; i++)
#define all(v) v.begin(), v.end()
#define aajav(v, n)           \
    for (int i = 0; i < n; i++) \
    {                           \
        int x;                    \
        cin >> x;                 \
        v.eb(x);                  \
    }
#define javadenev(v, n)       \
    for (int i = 0; i < n; i++) \
    {                           \
        cout << v[i] << " ";      \
    }
#define nodgt(n) (int)log10(n) + 1
#define lcm(a, b) ((a * b) / (__gcd(a, b)))

vector<int> t2pc(vector<vector<int>> &tree)
{
    int n = tree.size();
    vector<int> deg(n, 0);
    for (int i = 0; i < n; i++)
    {
        deg[i] = tree[i].size();
    }
    vector<int> code;
    for (int i = 0; i < n - 2; i++)
    {
        int leaf = -1;
        for (int j = 0; j < n; j++)
        {
            if (deg[j] == 1)
            {
                leaf = j;
                break;
            }
        }
        int p = -1;
        for (int j = 0; j < tree[leaf].size(); j++)
        {
            p = tree[leaf][j];
            if (deg[p] > 0)
            {
                break;
            }
        }
        code.push_back(p);
        for (int i = 0; i < code.size(); i++)
        {
            cout << code[i] + 1 << " ";
        }
        cout << "\n";
        deg[p]--;
        deg[leaf]--;
    }
    return code;
}

vector<vector<int>> pc2t(vector<int> &code)
{
    int n = code.size() + 2;
    vector<vector<int>> edges;
    vector<int> deg(n, 1);
    for (int i = 0; i < code.size(); i++)
    {
        deg[code[i]]++;
    }

    set<int> ls;
    deque<int> prufer_code(code.begin(), code.end());

    for (int i = 0; i < n; i++)
    {
        if (deg[i] == 1)
        {
            ls.insert(i);
        }
    }
    for (int i = 0; i < code.size(); i++)
    {
        int u = prufer_code.front();
        int v = *ls.begin();
        prufer_code.pop_front();
        ls.erase(ls.begin()); 
        prufer_code.push_back(v);
        edges.push_back({u, v});
        deg[u]--;
        deg[v]--;
        if (deg[u] == 1)
        {
            ls.insert(u);
        }
    }
    int u = *ls.begin();
    ls.erase(u);
    int v = *ls.begin();
    edges.push_back({u, v});

    return edges;
}

void dfs(int node, vector<vector<int>> &adj, vector<int> &vis, vector<int> &ans)
{
    vis[node] = 1;
    ans.push_back(node);
    for (auto it : adj[node])
    {
        if (vis[it] == 0)
        {
            dfs(it, adj, vis, ans);
        }
    }
}

int main()
{
    int n;
    cout << "Enter the number of vertices in the tree: ";
    cin >> n;
    vector<vector<int>> tree(n);
    cout << "Enter the edges of the tree (u, v):\n";
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<int> code = t2pc(tree);
    cout << "The Prufer code of the tree is: ";
    for (int i = 0; i < code.size(); i++)
    {
        cout << code[i] + 1 << " ";
    }
    cout << "\n";

    vector<vector<int>> new_tree = pc2t(code);
    cout << "The tree generated from the Prufer code is:\n";
    for (int i = 0; i < new_tree.size(); i++)
    {
        cout << new_tree[i][0] + 1 << " " << new_tree[i][1] + 1 << "\n";
    }

    vector<vector<int>> new_adj(n);
    for (auto it : new_tree)
    {
        new_adj[it[0]].push_back(it[1]);
        new_adj[it[1]].push_back(it[0]);
    }

    vector<int> preorder_traversal;
    vector<int> vis(n, 0);
    dfs(0, new_adj, vis, preorder_traversal);
    cout << "Traversal: ";
    for (auto node : preorder_traversal)
    {
        cout << node+1 << " ";
    }
    cout << "\n";
}
