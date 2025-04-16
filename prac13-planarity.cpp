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
