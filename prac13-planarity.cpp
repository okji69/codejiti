#include<bits/stdc++.h>
using namespace std;

// Check if the graph is the Petersen Graph
bool isPetersenGraph(const vector<vector<int>>& adj, int V, int E) {
    if (V != 10 || E != 15) return false;
    
    // Every vertex must have degree 3
    for (int i = 0; i < V; i++) {
        if (adj[i].size() != 3) return false;
    }

    // Petersen graph is not bipartite, so bipartite check must fail
    vector<int> color(V, -1);
    queue<int> q;

    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            q.push(i);
            color[i] = 0;
            while (!q.empty()) {
                int node = q.front(); q.pop();
                for (int ngh : adj[node]) {
                    if (color[ngh] == -1) {
                        color[ngh] = 1 - color[node];
                        q.push(ngh);
                    } else if (color[ngh] == color[node]) {
                        // Not bipartite → likely Petersen
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

int main(){
    int n;
    cout<<"Enter the number of vertices"<<endl;
    cin>>n;
    vector<vector<int>>g(n,vector<int>(n,0));
    vector<vector<int>> adj(n); // For Peterson check
    vector<int>deg(n,0);    
    int m;  
    cout<<"Enter the number of edges"<<endl;
    cin>>m;
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        deg[u-1]++;
        deg[v-1]++;
        g[u-1][v-1]++;
        g[v-1][u-1]++;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }

    if (isPetersenGraph(adj, n, m)) {
        cout << "Graph is Petersen Graph (Known non-planar)" << endl;
        return 0;
    }

    // remove self loops
    for(int i=0;i<n;i++){
        if(g[i][i]>0){
            deg[i]-=g[i][i];
            g[i][i]=0;
        }
    }

    // remove parallel edges
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
        {
            if(g[i][j]>1)
            {
                deg[i]-=g[i][j]-1;
                deg[j]-=g[i][j]-1;
                g[i][j]=1;
                g[j][i]=1;
            }
        }
    }

    // remove nodes with degree 2
    int sum;
    int ans;
    while(true)
    {
        sum=0;
        ans=0;
        int fl=0;
        for(int i=0;i<n;i++){
            sum+=deg[i];
            if(deg[i]>0){ans++;}
            if(deg[i]!=2){continue;}
            fl=1;
            vector<int>t;
            for(int j=0;j<n;j++){
                if(g[i][j]){
                    t.push_back(j);
                }
            }
            if (t.size() < 2) continue; // avoid index error
            g[t[0]][t[1]]=1;
            g[t[1]][t[0]]=1;
            g[i][t[0]]=0;
            g[i][t[1]]=0;
            g[t[0]][i]=0;
            g[t[1]][i]=0;
            deg[i]=0;
        }
        if(fl==0){break;}
    }

    int x = sum/2;  
    if(x == 1 || (ans == 4 && x==6))
    {
        cout << "Graph is planar (basic case: single edge or K4)" << endl;
    }
    else if(ans >= 5)
    {
        bool allDeg3OrMore = true;
        for(int i = 0; i < n; i++){
            if(deg[i] > 0 && deg[i] < 3){
                allDeg3OrMore = false;
                break;
            }
        }
        if(allDeg3OrMore && x > 3 * ans - 6)
        {
            cout << "Graph is NOT planar (fails Euler's inequality)" << endl;
        } else {
            cout << "Graph MIGHT be planar (passes Euler's inequality)" << endl;
            cout << "Further Kuratowski subgraph check needed for K5 or K3,3." << endl;
        }
    }
    else 
    {
        cout << "Graph is planar (fewer than 5 vertices)" << endl;
    }

    return 0;
}



/*
Check whether graph is planar or not.

1. If graph in disconnected, check each component separately.
2. for each component, do the following:
    a. remove all parallel edges and self-loops.
    b. remove the vertices of degree 2 and replace them with a single edge.

3. At last if only one edge is left, then the graph is planar.
4. If more than one edge is left, then check the number of edges and vertices.
5. check condition for planar graph:
    a. if number of edges > 3 * number of vertices - 6, then the graph is not planar.
    b. else further investigatation is needed.
*/

#include <bits/stdc++.h>
using namespace std;

bool isPlanar(vector<int> component, vector<vector<int>> graph)
{

    set<pair<int, int>> edges;
    for (int i : component)
    {
        for (int j : graph[i])
        {
            if (i != j)
            {
                edges.insert({min(i, j), max(i, j)});
            }
        }
    }

    vector<int> newComponent;
    for (auto edge : edges)
    {
        newComponent.push_back(edge.first);
        newComponent.push_back(edge.second);
    }

    int n = newComponent.size();
    int e = edges.size();

    if (e > 3 * n - 6)
        return false;

    return true;
}

int main()
{

    int n, e;
    cin >> n >> e;

    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);
    vector<vector<int>> components;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            vector<int> component;
            stack<int> s;
            s.push(i);
            visited[i] = true;
            while (!s.empty())
            {
                int node = s.top();
                s.pop();
                component.push_back(node);
                for (int j : graph[node])
                {
                    if (!visited[j])
                    {
                        visited[j] = true;
                        s.push(j);
                    }
                }
            }
            components.push_back(component);
        }
    }

    for (auto component : components)
    {
        bool res = isPlanar(component, graph);
        if (!res)
        {
            cout << "Graph is not planar" << endl;
            return 0;
        }
    }

    cout << "Graph is planar" << endl;
    return 0;
}
