#include<bits/stdc++.h>
using namespace std;

// Function to perform BFS and color the graph
bool check(int start, int V, vector<int> adj[], int color[]) {
    queue<int> q;
    q.push(start); 
    color[start] = 0; 
    while(!q.empty()) {
        int node = q.front();
        q.pop(); 
        
        for(auto it : adj[node]) {
            if(color[it] == -1) {
                color[it] = !color[node]; 
                q.push(it); 
            }
            else if(color[it] == color[node]) {
                return false; 
            }
        }
    }
    return true; 
}

// Function to check if the graph is bipartite
bool isBipartite(int V, vector<int> adj[]) {
    int color[V]; 
    for(int i = 0; i < V; i++) color[i] = -1; 
    
    for(int i = 0; i < V; i++) {
        if(color[i] == -1) {
            if(!check(i, V, adj, color)) {
                return false; 
            }
        }
    }
    return true; 
}

// Adds undirected edge to the graph
void addEdge(vector<int> adj[], int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main(){
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<int> adj[V];

    cout << "Enter " << E << " edges (u v):" << endl;
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(adj, u, v);
    }

    if(isBipartite(V, adj)) cout << "1\n";
    else cout << "0\n";
    
    return 0;
}
